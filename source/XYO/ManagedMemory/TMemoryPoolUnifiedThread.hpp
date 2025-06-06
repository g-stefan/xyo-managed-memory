// Managed Memory
// Copyright (c) 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLUNIFIEDTHREAD_HPP
#define XYO_MANAGEDMEMORY_TMEMORYPOOLUNIFIEDTHREAD_HPP

#if defined(XYO_MANAGEDMEMORY_TMEMORYPOOL_SYSTEM) | defined(XYO_MANAGEDMEMORY_TMEMORYPOOL_UNIFIED_AS_SYSTEM)

#	ifndef XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP
#		include <XYO/ManagedMemory/TMemorySystem.hpp>
#	endif

namespace XYO::ManagedMemory {

	template <typename T>
	struct TMemoryPoolUnifiedThread : TMemorySystem<T> {};

};

#elif defined(XYO_PLATFORM_SINGLE_THREAD)

#	ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLUNIFIEDPROCESS_HPP
#		include <XYO/ManagedMemory/TMemoryPoolUnifiedProcess.hpp>
#	endif

namespace XYO::ManagedMemory {

	template <typename T>
	struct TMemoryPoolUnifiedThread : TMemoryPoolUnifiedProcess<T> {};

};

#else

#	ifndef XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP
#		include <XYO/ManagedMemory/TMemorySystem.hpp>
#	endif

#	ifndef XYO_MANAGEDMEMORY_REGISTRYTHREAD_HPP
#		include <XYO/ManagedMemory/RegistryThread.hpp>
#	endif

#	ifndef XYO_MANAGEDMEMORY_TXLIST1_HPP
#		include <XYO/ManagedMemory/TXList1.hpp>
#	endif

namespace XYO::ManagedMemory {

	template <size_t sizeOfT>
	class TMemoryPoolUnifiedThreadImplement {
		public:
			enum {
				NewElementCount = 8,
				FreeElementCountThreshold = 24,
				FreeElementCount = 16
			};

			struct Link { // POD
					Link *next;

					uint8_t value[sizeOfT];
#	ifdef XYO_MANAGEDMEMORY_TMEMORYPOOL_CHECK
					bool isDeleted;
#	endif
			};

			typedef TXList1<Link, TMemorySystem> ListLink;

			Link *rootFreeLink;
			size_t rootFreeLinkCount;

#	ifdef XYO_MANAGEDMEMORY_TMEMORYPOOL_CHECK_COUNT
			size_t checkCount;
#	endif

			inline TMemoryPoolUnifiedThreadImplement() {
				ListLink::constructor(rootFreeLink);
				rootFreeLinkCount = 0;
#	ifdef XYO_MANAGEDMEMORY_TMEMORYPOOL_CHECK_COUNT
				checkCount = 0;
#	endif
			};

#	ifdef XYO_MANAGEDMEMORY_TMEMORYPOOL_CHECK_COUNT
			static inline const std::string checkCountNotZero_() {
				std::string retV("check count not zero ");
				retV += registryKey();
				return retV;
			};
#	endif

			inline ~TMemoryPoolUnifiedThreadImplement() {

#	ifdef XYO_MANAGEDMEMORY_TMEMORYPOOL_CHECK
				if (checkCount != 0) {
					throw std::runtime_error(checkCountNotZero_());
				};
#	endif
				ListLink::destructor(rootFreeLink);
			};

			inline void grow() {
				size_t k;
				Link *newItem;
				for (k = 0; k < NewElementCount; ++k) {
					newItem = ListLink::newNode();
#	ifdef XYO_MANAGEDMEMORY_TMEMORYPOOL_CHECK
					newItem->isDeleted = true;
#	endif
					++rootFreeLinkCount;
					ListLink::push(rootFreeLink, newItem);
				};
			};

			inline void *newMemory() {
				void *this_;
				if (!rootFreeLink) {
					grow();
				};
				this_ = (void *)(rootFreeLink->value);
#	ifdef XYO_MANAGEDMEMORY_TMEMORYPOOL_CHECK
				rootFreeLink->isDeleted = false;
#	endif
#	ifdef XYO_MANAGEDMEMORY_TMEMORYPOOL_CHECK_COUNT
				checkCount++;
#	endif
				--rootFreeLinkCount;
				ListLink::popUnsafeX(rootFreeLink);
				return this_;
			};

#	ifdef XYO_MANAGEDMEMORY_TMEMORYPOOL_CHECK
			static inline const std::string deleteMemoryOnAlreadyDeletedObject_() {
				std::string retV("deleteMemory on already deleted object ");
				retV += registryKey();
				return retV;
			};
#	endif

			inline void deleteMemory(void *this_) {
#	ifdef XYO_MANAGEDMEMORY_TMEMORYPOOL_CHECK
				if ((reinterpret_cast<Link *>((reinterpret_cast<uint8_t *>(this_)) - offsetof(Link, value)))->isDeleted) {
					throw std::runtime_error(deleteMemoryOnAlreadyDeletedObject_());
				};
				(reinterpret_cast<Link *>((reinterpret_cast<uint8_t *>(this_)) - offsetof(Link, value)))->isDeleted = true;
#	endif
#	ifdef XYO_MANAGEDMEMORY_TMEMORYPOOL_CHECK_COUNT
				checkCount--;
#	endif

				++rootFreeLinkCount;
				this_ = (void *)((reinterpret_cast<uint8_t *>(this_)) - offsetof(Link, value));
				ListLink::push(rootFreeLink, reinterpret_cast<Link *>(this_));

				Link *itemListToFree = nullptr;
				if (rootFreeLinkCount == FreeElementCountThreshold) {
					Link *item;
					size_t k;
					for (k = 0; k < FreeElementCount; ++k) {
						if (rootFreeLink) {
							--rootFreeLinkCount;
							item = rootFreeLink;
							ListLink::popUnsafeX(rootFreeLink);
							ListLink::push(itemListToFree, item);
							continue;
						};
						rootFreeLinkCount = 0;
						break;
					};
				};

				if (itemListToFree) {
					ListLink::destructor(itemListToFree);
				};
			};

			static size_t registryLink;
			static const char *registryKey();
			static void resourceDelete(void *);
	};

	template <size_t sizeOfT>
	const char *TMemoryPoolUnifiedThreadImplement<sizeOfT>::registryKey() {
		return typeid(TMemoryPoolUnifiedThreadImplement<sizeOfT>).name();
	};

	template <size_t sizeOfT>
	size_t TMemoryPoolUnifiedThreadImplement<sizeOfT>::registryLink = 0;

	template <size_t sizeOfT>
	void TMemoryPoolUnifiedThreadImplement<sizeOfT>::resourceDelete(void *this_) {
		delete (TMemoryPoolUnifiedThreadImplement<sizeOfT> *)this_;
	};

	//

	template <typename T>
	class TMemoryPoolUnifiedThreadRecursiveGuard {
		public:
			static size_t registryLink;
			static const char *registryKey();
			static void resourceDelete(void *);
	};

	template <typename T>
	const char *TMemoryPoolUnifiedThreadRecursiveGuard<T>::registryKey() {
		return typeid(TMemoryPoolUnifiedThreadRecursiveGuard<T>).name();
	};

	template <typename T>
	size_t TMemoryPoolUnifiedThreadRecursiveGuard<T>::registryLink = 0;

	template <typename T>
	void TMemoryPoolUnifiedThreadRecursiveGuard<T>::resourceDelete(void *this_) {
		delete (TMemoryPoolUnifiedThreadRecursiveGuard<T> *)this_;
	};

	//

	template <typename T, bool hasInitMemory>
	struct TIfHasInitMemoryRecursiveGuardThreadBase {
			static inline void initMemory(){};
	};

	template <typename T>
	struct TIfHasInitMemoryRecursiveGuardThreadBase<T, true> {
			static inline void initMemory() {

				if (RegistryThread::registerKey(
				        TMemoryPoolUnifiedThreadRecursiveGuard<T>::registryKey(),
				        TMemoryPoolUnifiedThreadRecursiveGuard<T>::registryLink)) {

					TIfHasInitMemory<T>::initMemory();

					RegistryThread::setValue(
					    TMemoryPoolUnifiedThreadRecursiveGuard<T>::registryLink,
					    RegistryLevel::Static,
					    new TMemoryPoolUnifiedThreadRecursiveGuard<T>(),
					    TMemoryPoolUnifiedThreadRecursiveGuard<T>::resourceDelete,
					    nullptr);
				};
			};
	};

	template <typename T>
	struct TIfHasInitMemoryRecursiveGuardThread : TIfHasInitMemoryRecursiveGuardThreadBase<T, THasInitMemory<T>::value> {
	};

	//

	template <typename T>
	class TMemoryPoolUnifiedThread {
		protected:
			static inline const std::string deleteMemoryWithoutInitialization_() {
				std::string retV("deleteMemory without initialization ");
				retV += TMemoryPoolUnifiedThreadImplement<sizeof(T)>::registryKey();
				return retV;
			};

			static inline void deleteMemory_(T *this_) {
				TIfHasActiveDestructor<T>::activeDestructor(this_);
				TIfHasActiveFinalizer<T>::activeFinalizer(this_);
				TIfHasSetDeleteMemory<T>::setDeleteMemory(this_, nullptr, nullptr);
				this_->~T();

				//
				// dynamic link guard, can be multiple instances in different libraries
				// this will recover the original instance
				//
				if (!TMemoryPoolUnifiedThreadImplement<sizeof(T)>::registryLink) {
					TMemoryPoolUnifiedThreadImplement<sizeof(T)>::registryLink = RegistryThread::getKey(TMemoryPoolUnifiedThreadImplement<sizeof(T)>::registryKey());
					if (!TMemoryPoolUnifiedThreadImplement<sizeof(T)>::registryLink) {
						throw std::runtime_error(deleteMemoryWithoutInitialization_());
					};
				};
				//
				//
				//

				((TMemoryPoolUnifiedThreadImplement<sizeof(T)> *)
				     RegistryThread::getValue(TMemoryPoolUnifiedThreadImplement<sizeof(T)>::registryLink))
				    ->deleteMemory(this_);
			};

			template <typename U, bool hasDecReferenceCount>
			struct TDeleteMemory {

					static inline void deleteMemory(U *this_) {
						deleteMemory_(this_);
					};
			};

			template <typename U>
			struct TDeleteMemory<U, true> {

					static inline void deleteMemory(U *this_) {
						this_->decReferenceCount();
					};
			};

		public:
			template <typename... Args>
			static inline T *newMemory(Args &&...args) {
				T *this_ = reinterpret_cast<T *>(RegistryThread::getValue(TMemoryPoolUnifiedThreadImplement<sizeof(T)>::registryLink));
				if (!this_) {
					initMemory();
					this_ = reinterpret_cast<T *>(RegistryThread::getValue(TMemoryPoolUnifiedThreadImplement<sizeof(T)>::registryLink));
				};
				this_ = new ((reinterpret_cast<TMemoryPoolUnifiedThreadImplement<sizeof(T)> *>(this_))->newMemory()) T(std::forward<Args>(args)...);
				TIfHasSetDeleteMemory<T>::setDeleteMemory(this_, (DeleteMemory)deleteMemory_, this_);
				TIfHasActiveConstructor<T>::activeConstructor(this_);
				return this_;
			};

			static inline void deleteMemory(T *this_) {
				TDeleteMemory<T, THasDecReferenceCount<T>::value>::deleteMemory(this_);
			};

			static inline void initMemory() {
				Registry::registryInit();
				if (RegistryThread::registerKey(
				        TMemoryPoolUnifiedThreadImplement<sizeof(T)>::registryKey(),
				        TMemoryPoolUnifiedThreadImplement<sizeof(T)>::registryLink)) {

					TIfHasInitMemory<T>::initMemory();

					RegistryThread::setValue(
					    TMemoryPoolUnifiedThreadImplement<sizeof(T)>::registryLink,
					    RegistryLevel::Static,
					    new TMemoryPoolUnifiedThreadImplement<sizeof(T)>(),
					    TMemoryPoolUnifiedThreadImplement<sizeof(T)>::resourceDelete,
					    nullptr);
				} else {
					TIfHasInitMemoryRecursiveGuardThread<T>::initMemory();
				};
			};
	};

};

#endif

#endif

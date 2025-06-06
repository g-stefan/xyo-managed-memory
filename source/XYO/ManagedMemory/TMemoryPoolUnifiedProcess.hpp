// Managed Memory
// Copyright (c) 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLUNIFIEDPROCESS_HPP
#define XYO_MANAGEDMEMORY_TMEMORYPOOLUNIFIEDPROCESS_HPP

#if defined(XYO_MANAGEDMEMORY_TMEMORYPOOL_SYSTEM) | defined(XYO_MANAGEDMEMORY_TMEMORYPOOL_UNIFIED_AS_SYSTEM)

#	ifndef XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP
#		include <XYO/ManagedMemory/TMemorySystem.hpp>
#	endif

namespace XYO::ManagedMemory {

	template <typename T>
	struct TMemoryPoolUnifiedProcess : TMemorySystem<T> {};

};

#else

#	ifndef XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP
#		include <XYO/ManagedMemory/TMemorySystem.hpp>
#	endif

#	ifndef XYO_MANAGEDMEMORY_REGISTRYPROCESS_HPP
#		include <XYO/ManagedMemory/RegistryProcess.hpp>
#	endif

#	ifndef XYO_MANAGEDMEMORY_TXLIST1_HPP
#		include <XYO/ManagedMemory/TXList1.hpp>
#	endif

namespace XYO::ManagedMemory {

	template <size_t sizeOfT>
	class TMemoryPoolUnifiedProcessImplement {
		protected:
#	ifdef XYO_PLATFORM_MULTI_THREAD
			CriticalSection criticalSection;
#	endif
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

			inline TMemoryPoolUnifiedProcessImplement() {
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

			inline ~TMemoryPoolUnifiedProcessImplement() {

#	ifdef XYO_MANAGEDMEMORY_TMEMORYPOOL_CHECK_COUNT
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
#	ifdef XYO_PLATFORM_MULTI_THREAD
				criticalSection.enter();
#	endif
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
#	ifdef XYO_PLATFORM_MULTI_THREAD
				criticalSection.leave();
#	endif
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

				Link *itemListToFree = nullptr;

#	ifdef XYO_PLATFORM_MULTI_THREAD
				criticalSection.enter();
#	endif

				this_ = (void *)((reinterpret_cast<uint8_t *>(this_)) - offsetof(Link, value));
				ListLink::push(rootFreeLink, ((Link *)this_));
				++rootFreeLinkCount;

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

#	ifdef XYO_PLATFORM_MULTI_THREAD
				criticalSection.leave();
#	endif

				if (itemListToFree != nullptr) {
					ListLink::deleteList(itemListToFree);
				};
			};

			static TAtomic<TMemoryPoolUnifiedProcessImplement *> memoryPool;
			static const char *registryKey();
			static void resourceDelete(void *);
	};

	template <size_t sizeOfT>
	const char *TMemoryPoolUnifiedProcessImplement<sizeOfT>::registryKey() {
		return typeid(TMemoryPoolUnifiedProcessImplement<sizeOfT>).name();
	};

	template <size_t sizeOfT>
	TAtomic<TMemoryPoolUnifiedProcessImplement<sizeOfT> *> TMemoryPoolUnifiedProcessImplement<sizeOfT>::memoryPool(nullptr);

	template <size_t sizeOfT>
	void TMemoryPoolUnifiedProcessImplement<sizeOfT>::resourceDelete(void *this_) {
		delete reinterpret_cast<TMemoryPoolUnifiedProcessImplement<sizeOfT> *>(this_);
	};

	//

	template <typename T>
	class TMemoryPoolUnifiedProcessRecursiveGuard {
		public:
			static TAtomic<TMemoryPoolUnifiedProcessRecursiveGuard *> memoryGuard;
			static const char *registryKey();
			static void resourceDelete(void *);
	};

	template <typename T>
	const char *TMemoryPoolUnifiedProcessRecursiveGuard<T>::registryKey() {
		return typeid(TMemoryPoolUnifiedProcessRecursiveGuard<T>).name();
	};

	template <typename T>
	TAtomic<TMemoryPoolUnifiedProcessRecursiveGuard<T> *> TMemoryPoolUnifiedProcessRecursiveGuard<T>::memoryGuard(nullptr);

	template <typename T>
	void TMemoryPoolUnifiedProcessRecursiveGuard<T>::resourceDelete(void *this_) {
		delete reinterpret_cast<TMemoryPoolUnifiedProcessRecursiveGuard<T> *>(this_);
	};

	//

	template <typename T, bool hasInitMemory>
	struct TIfHasInitMemoryRecursiveGuardProcessBase {
			static inline void initMemory(){};
	};

	template <typename T>
	struct TIfHasInitMemoryRecursiveGuardProcessBase<T, true> {
			static inline void initMemory() {

				void *registryRecursiveGuard;
				if (RegistryProcess::checkAndRegisterKey(
				        TMemoryPoolUnifiedProcessRecursiveGuard<T>::registryKey(), registryRecursiveGuard, [] { return (TMemoryPoolUnifiedProcessRecursiveGuard<T>::memoryGuard.get() == nullptr); }, [](void *this__) {
					TMemoryPoolUnifiedProcessRecursiveGuard<T>
					*this_ = reinterpret_cast<TMemoryPoolUnifiedProcessRecursiveGuard<T> *>(this__);
					TMemoryPoolUnifiedProcessRecursiveGuard<T>::memoryGuard.set(this_); })) {

					TIfHasInitMemory<T>::initMemory();

					TMemoryPoolUnifiedProcessRecursiveGuard<T>::memoryGuard.set(new TMemoryPoolUnifiedProcessRecursiveGuard<T>());

					RegistryProcess::setValue(
					    registryRecursiveGuard,
					    RegistryLevel::Static,
					    TMemoryPoolUnifiedProcessRecursiveGuard<T>::memoryGuard.get(),
					    TMemoryPoolUnifiedProcessRecursiveGuard<T>::resourceDelete,
					    nullptr);
				};
			};
	};

	template <typename T>
	struct TIfHasInitMemoryRecursiveGuardProcess : TIfHasInitMemoryRecursiveGuardProcessBase<T, THasInitMemory<T>::value> {
	};

	//

	template <typename T>
	class TMemoryPoolUnifiedProcess {
		protected:
			static inline const std::string deleteMemoryWithoutInitialization_() {
				std::string retV("deleteMemory without initialization ");
				retV += TMemoryPoolUnifiedProcessImplement<sizeof(T)>::registryKey();
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
				if (!TMemoryPoolUnifiedProcessImplement<sizeof(T)>::memoryPool.get()) {
					TMemoryPoolUnifiedProcessImplement<sizeof(T)>::memoryPool.set(
					    reinterpret_cast<TMemoryPoolUnifiedProcessImplement<sizeof(T)> *>(
					        RegistryProcess::getKey(TMemoryPoolUnifiedProcessImplement<sizeof(T)>::registryKey())));
					if (!TMemoryPoolUnifiedProcessImplement<sizeof(T)>::memoryPool.get()) {
						throw std::runtime_error(deleteMemoryWithoutInitialization_());
					};
				};
				//
				//
				//

				(TMemoryPoolUnifiedProcessImplement<sizeof(T)>::memoryPool.get())
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
				if (!TMemoryPoolUnifiedProcessImplement<sizeof(T)>::memoryPool.get()) {
					initMemory();
				};
				T *this_ = new ((TMemoryPoolUnifiedProcessImplement<sizeof(T)>::memoryPool.get())->newMemory()) T(std::forward<Args>(args)...);
				TIfHasSetDeleteMemory<T>::setDeleteMemory(this_, (DeleteMemory)deleteMemory_, this_);
				TIfHasActiveConstructor<T>::activeConstructor(this_);
				return this_;
			};

			static inline void deleteMemory(T *this_) {
				TDeleteMemory<T, THasDecReferenceCount<T>::value>::deleteMemory(this_);
			};

			static inline void initMemory() {
				void *registryLink;
				Registry::registryInit();
				// ---
				if (RegistryProcess::checkAndRegisterKey(
				        TMemoryPoolUnifiedProcessImplement<sizeof(T)>::registryKey(), registryLink, [] { return (TMemoryPoolUnifiedProcessImplement<sizeof(T)>::memoryPool.get() == nullptr); }, [](void *this__) {
						TMemoryPoolUnifiedProcessImplement<sizeof(T)>
						*this_ = reinterpret_cast<TMemoryPoolUnifiedProcessImplement<sizeof(T)> *>(this__);
						TMemoryPoolUnifiedProcessImplement<sizeof(T)>::memoryPool.set(this_); })) {

					TIfHasInitMemory<T>::initMemory();

					TMemoryPoolUnifiedProcessImplement<sizeof(T)>::memoryPool.set(new TMemoryPoolUnifiedProcessImplement<sizeof(T)>());

					RegistryProcess::setValue(
					    registryLink,
					    RegistryLevel::Static,
					    TMemoryPoolUnifiedProcessImplement<sizeof(T)>::memoryPool.get(),
					    TMemoryPoolUnifiedProcessImplement<sizeof(T)>::resourceDelete,
					    nullptr);
				} else {
					TIfHasInitMemoryRecursiveGuardProcess<T>::initMemory();
				};
			};
	};

};

#endif

#endif

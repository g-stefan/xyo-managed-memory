// Managed Memory
// Copyright (c) 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLACTIVEPROCESS_HPP
#define XYO_MANAGEDMEMORY_TMEMORYPOOLACTIVEPROCESS_HPP

#ifdef XYO_MANAGEDMEMORY_TMEMORYPOOL_SYSTEM

#	ifndef XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP
#		include <XYO/ManagedMemory/TMemorySystem.hpp>
#	endif

namespace XYO::ManagedMemory {

	template <typename T>
	struct TMemoryPoolActiveProcess : TMemorySystem<T> {};

};

#elif defined(XYO_MANAGEDMEMORY_TMEMORYPOOL_ACTIVE_AS_UNIFIED)

#	ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLUNIFIEDPROCESS_HPP
#		include <XYO/ManagedMemory/TMemoryPoolUnifiedProcess.hpp>
#	endif

namespace XYO::ManagedMemory {

	template <typename T>
	struct TMemoryPoolActiveProcess : TMemoryPoolUnifiedProcess<T> {};

};

#else

#	ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLUNIFIEDPROCESS_HPP
#		include <XYO/ManagedMemory/TMemoryPoolUnifiedProcess.hpp>
#	endif

#	ifndef XYO_MANAGEDMEMORY_TXLIST1_HPP
#		include <XYO/ManagedMemory/TXList1.hpp>
#	endif

namespace XYO::ManagedMemory {

	template <typename T>
	class TMemoryPoolActiveProcessImplement {
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

					uint8_t value[sizeof(T)];
#	ifdef XYO_MANAGEDMEMORY_TMEMORYPOOL_CHECK
					bool isDeleted;
#	endif
			};

#	ifdef XYO_MANAGEDMEMORY_TMEMORYPOOL_ACTIVE_LEVEL_IS_SYSTEM
			typedef TXList1<Link, TMemorySystem> ListLink;
#	else
			typedef TXList1<Link, TMemoryPoolUnifiedProcess> ListLink;
#	endif
			Link *poolFreeLink;
			size_t poolFreeLinkCount;
#	ifdef XYO_MANAGEDMEMORY_TMEMORYPOOL_CHECK_COUNT
			size_t checkCount;
#	endif

			inline TMemoryPoolActiveProcessImplement() {
				ListLink::constructor(poolFreeLink);
				poolFreeLinkCount = 0;
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

			inline ~TMemoryPoolActiveProcessImplement() {

#	ifdef XYO_MANAGEDMEMORY_TMEMORYPOOL_CHECK_COUNT
				if (checkCount != 0) {
					throw std::runtime_error(checkCountNotZero_());
				};
#	endif

				deleteListLink(poolFreeLink);
			};

			inline void deleteListLink(Link *&poolLink) {
				Link *this_;
				while (poolLink) {
					this_ = poolLink;
					poolLink = poolLink->next;
					TIfHasActiveFinalizer<T>::activeFinalizer(reinterpret_cast<T *>(&this_->value[0]));
					TIfHasSetDeleteMemory<T>::setDeleteMemory(reinterpret_cast<T *>(&this_->value[0]), nullptr, nullptr);
					(reinterpret_cast<T *>(&this_->value[0]))->~T();
					ListLink::deleteNode(this_);
				};
			};

			inline void grow() {
				size_t k;
				Link *this_;
				for (k = 0; k < NewElementCount; ++k) {
					this_ = ListLink::newNode();
					new (&this_->value[0]) T();
#	ifdef XYO_MANAGEDMEMORY_TMEMORYPOOL_CHECK
					this_->isDeleted = true;
#	endif
					++poolFreeLinkCount;
					ListLink::push(poolFreeLink, this_);
					TIfHasSetDeleteMemory<T>::setDeleteMemory(reinterpret_cast<T *>(&this_->value[0]), (DeleteMemory)deleteMemory_, reinterpret_cast<T *>(&this_->value[0]));
				};
			};

			inline T *newMemory() {
				T *this_;
#	ifdef XYO_PLATFORM_MULTI_THREAD
				criticalSection.enter();
#	endif
				if (!poolFreeLink) {
					grow();
				};
				this_ = reinterpret_cast<T *>(&poolFreeLink->value[0]);
#	ifdef XYO_MANAGEDMEMORY_TMEMORYPOOL_CHECK
				poolFreeLink->isDeleted = false;
#	endif
				--poolFreeLinkCount;
				ListLink::popUnsafeX(poolFreeLink);

#	ifdef XYO_MANAGEDMEMORY_TMEMORYPOOL_CHECK_COUNT
				checkCount++;
#	endif

#	ifdef XYO_PLATFORM_MULTI_THREAD
				criticalSection.leave();
#	endif
				TIfHasActiveConstructor<T>::activeConstructor(this_);
				return this_;
			};

#	ifdef XYO_MANAGEDMEMORY_TMEMORYPOOL_CHECK
			static inline const std::string deleteMemoryOnAlreadyDeletedObject_() {
				std::string retV("deleteMemory on already deleted object ");
				retV += registryKey();
				return retV;
			};
#	endif

			inline void deleteMemory(T *this_) {
#	ifdef XYO_MANAGEDMEMORY_TMEMORYPOOL_CHECK
				if ((reinterpret_cast<Link *>((reinterpret_cast<uint8_t *>(this_)) - offsetof(Link, value)))->isDeleted) {
					throw std::runtime_error(deleteMemoryOnAlreadyDeletedObject_());
				};
				(reinterpret_cast<Link *>((reinterpret_cast<uint8_t *>(this_)) - offsetof(Link, value)))->isDeleted = true;
#	endif
#	ifdef XYO_MANAGEDMEMORY_TMEMORYPOOL_CHECK_COUNT
				checkCount--;
#	endif

				TIfHasActiveDestructor<T>::activeDestructor(this_);

				Link *itemListToFree = nullptr;

#	ifdef XYO_PLATFORM_MULTI_THREAD
				criticalSection.enter();
#	endif
				this_ = reinterpret_cast<T *>((reinterpret_cast<uint8_t *>(this_)) - offsetof(Link, value));
				ListLink::push(poolFreeLink, (reinterpret_cast<Link *>(this_)));
				++poolFreeLinkCount;

				if (poolFreeLinkCount == FreeElementCountThreshold) {
					Link *item;
					size_t k;
					for (k = 0; k < FreeElementCount; ++k) {
						if (poolFreeLink) {
							--poolFreeLinkCount;
							item = poolFreeLink;
							ListLink::popUnsafeX(poolFreeLink);
							ListLink::push(itemListToFree, item);
							continue;
						};
						poolFreeLinkCount = 0;
						break;
					};
				};

#	ifdef XYO_PLATFORM_MULTI_THREAD
				criticalSection.leave();
#	endif

				if (itemListToFree != nullptr) {
					deleteListLink(itemListToFree);
				};
			};

			static inline void initMemory() {
				ListLink::initMemory();
			};

			static inline const std::string deleteMemoryWithoutInitialization_() {
				std::string retV("deleteMemory without initialization ");
				retV += TMemoryPoolActiveProcessImplement<T>::registryKey();
				return retV;
			};

			static inline void deleteMemory_(T *this_) {

				//
				// dynamic link guard, can be multiple instances in different libraries
				// this will recover the original instance
				//
				if (!memoryPool.get()) {
					memoryPool.set(reinterpret_cast<TMemoryPoolActiveProcessImplement<T> *>(
					    RegistryProcess::getKey(TMemoryPoolActiveProcessImplement<T>::registryKey())));
					if (!memoryPool.get()) {
						throw std::runtime_error(deleteMemoryWithoutInitialization_());
					};
				};
				//
				//
				//

				(memoryPool.get())->deleteMemory(this_);
			};

			static TAtomic<TMemoryPoolActiveProcessImplement *> memoryPool;
			static const char *registryKey();
			static void resourceDelete(void *);
			static void resourceFinalizer(void *);
	};

	template <typename T>
	const char *TMemoryPoolActiveProcessImplement<T>::registryKey() {
		return typeid(TMemoryPoolActiveProcessImplement<T>).name();
	};

	template <typename T>
	TAtomic<TMemoryPoolActiveProcessImplement<T> *> TMemoryPoolActiveProcessImplement<T>::memoryPool(nullptr);

	template <typename T>
	void TMemoryPoolActiveProcessImplement<T>::resourceDelete(void *this_) {
		delete (TMemoryPoolActiveProcessImplement<T> *)this_;
	};

	template <typename T>
	void TMemoryPoolActiveProcessImplement<T>::resourceFinalizer(void *this_) {
		TMemoryPoolActiveProcessImplement<T>::Link *scan = ((TMemoryPoolActiveProcessImplement<T> *)this_)->poolFreeLink;
		while (scan) {
			TIfHasActiveFinalizer<T>::activeFinalizer(reinterpret_cast<T *>(&scan->value[0]));
			scan = scan->next;
		};
	};

	template <typename T>
	class TMemoryPoolActiveProcess {
		protected:
			template <typename U, bool hasDecReferenceCount>
			struct TDeleteMemory {

					static inline void deleteMemory(U *this_) {
						TMemoryPoolActiveProcessImplement<T>::deleteMemory_(this_);
					};
			};

			template <typename U>
			struct TDeleteMemory<U, true> {

					static inline void deleteMemory(U *this_) {
						this_->decReferenceCount();
					};
			};

		public:
			static inline T *newMemory() {
				if (!TMemoryPoolActiveProcessImplement<T>::memoryPool.get()) {
					initMemory();
				};
				return (TMemoryPoolActiveProcessImplement<T>::memoryPool.get())->newMemory();
			};

			static inline void deleteMemory(T *this_) {
				TDeleteMemory<T, THasDecReferenceCount<T>::value>::deleteMemory(this_);
			};

			static inline void initMemory() {
				Registry::registryInit();
				TMemoryPoolActiveProcessImplement<T>::initMemory();
				void *registryLink;

				//
				if (RegistryProcess::checkAndRegisterKey(
				        TMemoryPoolActiveProcessImplement<T>::registryKey(), registryLink, [] { return (TMemoryPoolActiveProcessImplement<T>::memoryPool.get() == nullptr); }, [](void *this__) {
						TMemoryPoolActiveProcessImplement<T>
						*this_ = reinterpret_cast<TMemoryPoolActiveProcessImplement<T> *>(this__);
						TMemoryPoolActiveProcessImplement<T>::memoryPool.set(this_); })) {
					TIfHasInitMemory<T>::initMemory();

					TMemoryPoolActiveProcessImplement<T>::memoryPool.set(new TMemoryPoolActiveProcessImplement<T>());

					RegistryProcess::setValue(
					    registryLink,
					    RegistryLevel::Active,
					    TMemoryPoolActiveProcessImplement<T>::memoryPool.get(),
					    TMemoryPoolActiveProcessImplement<T>::resourceDelete,
					    (THasActiveFinalizer<T>::value) ? TMemoryPoolActiveProcessImplement<T>::resourceFinalizer : nullptr);
				};
			};
	};

};
#endif

#endif

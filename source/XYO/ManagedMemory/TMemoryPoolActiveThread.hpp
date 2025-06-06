// Managed Memory
// Copyright (c) 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLACTIVETHREAD_HPP
#define XYO_MANAGEDMEMORY_TMEMORYPOOLACTIVETHREAD_HPP

#ifdef XYO_MANAGEDMEMORY_TMEMORYPOOL_SYSTEM

#	ifndef XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP
#		include <XYO/ManagedMemory/TMemorySystem.hpp>
#	endif

namespace XYO::ManagedMemory {

	template <typename T>
	struct TMemoryPoolActiveThread : TMemorySystem<T> {};

};

#elif defined(XYO_MANAGEDMEMORY_TMEMORYPOOL_ACTIVE_AS_UNIFIED)

#	ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLUNIFIEDTHREAD_HPP
#		include <XYO/ManagedMemory/TMemoryPoolUnifiedThread.hpp>
#	endif

namespace XYO::ManagedMemory {

	template <typename T>
	struct TMemoryPoolActiveThread : TMemoryPoolUnifiedThread<T> {};

};

#elif defined(XYO_PLATFORM_SINGLE_THREAD)

#	ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLACTIVEPROCESS_HPP
#		include <XYO/ManagedMemory/TMemoryPoolActiveProcess.hpp>
#	endif

namespace XYO::ManagedMemory {

	template <typename T>
	struct TMemoryPoolActiveThread : TMemoryPoolActiveProcess<T> {};

};

#else

#	ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLUNIFIEDTHREAD_HPP
#		include <XYO/ManagedMemory/TMemoryPoolUnifiedThread.hpp>
#	endif

#	ifndef XYO_MANAGEDMEMORY_TXLIST1_HPP
#		include <XYO/ManagedMemory/TXList1.hpp>
#	endif

#	ifndef XYO_MANAGEDMEMORY_REGISTRYTHREAD_HPP
#		include <XYO/ManagedMemory/RegistryThread.hpp>
#	endif

namespace XYO::ManagedMemory {

	template <typename T>
	class TMemoryPoolActiveThreadImplement {
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
			typedef TXList1<Link, TMemoryPoolUnifiedThread> ListLink;
#	endif
			Link *poolFreeLink;
			size_t poolFreeLinkCount;
#	ifdef XYO_MANAGEDMEMORY_TMEMORYPOOL_CHECK_COUNT
			size_t checkCount;
#	endif

			inline TMemoryPoolActiveThreadImplement() {
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

			inline ~TMemoryPoolActiveThreadImplement() {

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
				this_ = reinterpret_cast<T *>((reinterpret_cast<uint8_t *>(this_)) - offsetof(Link, value));
				ListLink::push(poolFreeLink, reinterpret_cast<Link *>(this_));
				++poolFreeLinkCount;

				Link *itemListToFree = nullptr;

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

				if (itemListToFree != nullptr) {
					deleteListLink(itemListToFree);
				};
			};

			static inline void initMemory() {
				ListLink::initMemory();
			};

			static inline const std::string deleteMemoryWithoutInitialization_() {
				std::string retV("deleteMemory without initialization ");
				retV += registryKey();
				return retV;
			};

			static inline void deleteMemory_(T *this_) {

				//
				// dynamic link guard, can be multiple instances in different libraries
				// this will recover the original instance
				//
				if (!registryLink) {
					registryLink = RegistryThread::getKey(registryKey());
					if (!registryLink) {
						throw std::runtime_error(deleteMemoryWithoutInitialization_());
					};
				};
				//
				//
				//

				(
				    (TMemoryPoolActiveThreadImplement<T> *)
				        RegistryThread::getValue(registryLink))
				    ->deleteMemory(this_);
			};

			static size_t registryLink;
			static const char *registryKey();
			static void resourceDelete(void *);
			static void resourceFinalizer(void *);
	};

	template <typename T>
	const char *TMemoryPoolActiveThreadImplement<T>::registryKey() {
		return typeid(TMemoryPoolActiveThreadImplement<T>).name();
	};

	template <typename T>
	size_t TMemoryPoolActiveThreadImplement<T>::registryLink = 0;

	template <typename T>
	void TMemoryPoolActiveThreadImplement<T>::resourceDelete(void *this_) {
		delete (TMemoryPoolActiveThreadImplement<T> *)this_;
	};

	template <typename T>
	void TMemoryPoolActiveThreadImplement<T>::resourceFinalizer(void *this_) {
		TMemoryPoolActiveThreadImplement<T>::Link *scan = ((TMemoryPoolActiveThreadImplement<T> *)this_)->poolFreeLink;
		while (scan) {
			TIfHasActiveFinalizer<T>::activeFinalizer(reinterpret_cast<T *>(&scan->value[0]));
			scan = scan->next;
		};
	};

	template <typename T>
	class TMemoryPoolActiveThread {
		protected:
			template <typename U, bool hasDecReferenceCount>
			struct TDeleteMemory {

					static inline void deleteMemory(U *this_) {
						TMemoryPoolActiveThreadImplement<T>::deleteMemory_(this_);
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
				T *this_ = reinterpret_cast<T *>(RegistryThread::getValue(TMemoryPoolActiveThreadImplement<T>::registryLink));
				if (!this_) {
					initMemory();
					this_ = reinterpret_cast<T *>(RegistryThread::getValue(TMemoryPoolActiveThreadImplement<T>::registryLink));
				};
				return (reinterpret_cast<TMemoryPoolActiveThreadImplement<T> *>(this_))->newMemory();
			};

			static inline void deleteMemory(T *this_) {
				TDeleteMemory<T, THasDecReferenceCount<T>::value>::deleteMemory(this_);
			};

			static inline void initMemory() {
				Registry::registryInit();
				TMemoryPoolActiveThreadImplement<T>::initMemory();

				if (RegistryThread::registerKey(
				        TMemoryPoolActiveThreadImplement<T>::registryKey(),
				        TMemoryPoolActiveThreadImplement<T>::registryLink)) {

					TIfHasInitMemory<T>::initMemory();

					RegistryThread::setValue(
					    TMemoryPoolActiveThreadImplement<T>::registryLink,
					    RegistryLevel::Active,
					    new TMemoryPoolActiveThreadImplement<T>(),
					    TMemoryPoolActiveThreadImplement<T>::resourceDelete,
					    (THasActiveFinalizer<T>::value) ? TMemoryPoolActiveThreadImplement<T>::resourceFinalizer : nullptr);
				};
			};
	};

};

#endif

#endif

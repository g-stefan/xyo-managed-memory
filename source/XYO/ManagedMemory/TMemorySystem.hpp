// Managed Memory
// Copyright (c) 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP
#define XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP

#ifndef XYO_MANAGEDMEMORY_DELETEMEMORY_HPP
#	include <XYO/ManagedMemory/DeleteMemory.hpp>
#endif

#ifndef XYO_MANAGEDMEMORY_FINALIZEMEMORY_HPP
#	include <XYO/ManagedMemory/FinalizeMemory.hpp>
#endif

#ifndef XYO_MANAGEDMEMORY_REGISTRY_HPP
#	include <XYO/ManagedMemory/Registry.hpp>
#endif

#ifndef XYO_MANAGEDMEMORY_TIFHASINITMEMORY_HPP
#	include <XYO/ManagedMemory/TIfHasInitMemory.hpp>
#endif

#ifndef XYO_MANAGEDMEMORY_TIFHASINCREFRENCECOUNT_HPP
#	include <XYO/ManagedMemory/TIfHasIncReferenceCount.hpp>
#endif

#ifndef XYO_MANAGEDMEMORY_TIFHASDECREFRENCECOUNT_HPP
#	include <XYO/ManagedMemory/TIfHasDecReferenceCount.hpp>
#endif

#ifndef XYO_MANAGEDMEMORY_TIFHASSETDELETEMEMORY_HPP
#	include <XYO/ManagedMemory/TIfHasSetDeleteMemory.hpp>
#endif

#ifndef XYO_MANAGEDMEMORY_TIFHASPOINTERLINK_HPP
#	include <XYO/ManagedMemory/TIfHasPointerLink.hpp>
#endif

#ifndef XYO_MANAGEDMEMORY_TIFHASACTIVECONSTRUCTOR_HPP
#	include <XYO/ManagedMemory/TIfHasActiveConstructor.hpp>
#endif

#ifndef XYO_MANAGEDMEMORY_TIFHASACTIVEDESTRUCTOR_HPP
#	include <XYO/ManagedMemory/TIfHasActiveDestructor.hpp>
#endif

#ifndef XYO_MANAGEDMEMORY_TIFHASACTIVEFINALIZER_HPP
#	include <XYO/ManagedMemory/TIfHasActiveFinalizer.hpp>
#endif

#ifndef XYO_MANAGEDMEMORY_OBJECT_HPP
#	include <XYO/ManagedMemory/Object.hpp>
#endif

#ifndef XYO_MANAGEDMEMORY_TPOINTER_HPP
#	include <XYO/ManagedMemory/TPointer.hpp>
#endif

#ifndef XYO_MANAGEDMEMORY_TPOINTERX_HPP
#	include <XYO/ManagedMemory/TPointerX.hpp>
#endif

namespace XYO::ManagedMemory {

	template <typename T>
	class TMemorySystem {
		protected:
			static inline void deleteMemory_(T *this_) {
				TIfHasActiveDestructor<T>::activeDestructor(this_);
				TIfHasActiveFinalizer<T>::activeFinalizer(this_);
				TIfHasSetDeleteMemory<T>::setDeleteMemory(this_, nullptr, nullptr);
				delete this_;
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
				T *this_ = new T(std::forward<Args>(args)...);
				TIfHasSetDeleteMemory<T>::setDeleteMemory(this_, (DeleteMemory)deleteMemory_, this_);
				TIfHasActiveConstructor<T>::activeConstructor(this_);
				return this_;
			};

			static inline void deleteMemory(T *this_) {
				TDeleteMemory<T, THasDecReferenceCount<T>::value>::deleteMemory(this_);
			};

			static inline void initMemory() {
				Registry::registryInit();
				TIfHasInitMemory<T>::initMemory();
			};
	};

};

#endif

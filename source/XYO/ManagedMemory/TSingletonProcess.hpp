// Managed Memory
// Copyright (c) 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_TSINGLETONPROCESS_HPP
#define XYO_MANAGEDMEMORY_TSINGLETONPROCESS_HPP

#ifndef XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP
#	include <XYO/ManagedMemory/TMemorySystem.hpp>
#endif

#ifndef XYO_MANAGEDMEMORY_REGISTRYPROCESS_HPP
#	include <XYO/ManagedMemory/RegistryProcess.hpp>
#endif

namespace XYO::ManagedMemory {

	template <typename T>
	class TSingletonProcess {
			XYO_PLATFORM_DISALLOW_COPY_ASSIGN_MOVE(TSingletonProcess);

		protected:
			inline TSingletonProcess(){};

		public:
			static TAtomic<T *> singletonLink;
			static const char *registryKey();
			static void resourceDelete(void *);
			static void resourceFinalizer(void *);

			static inline T *getValue() {
				T *retV = singletonLink.get();
				if (retV == nullptr) {
					initMemory();
					return singletonLink.get();
				};
				return retV;
			};

			static inline void initMemory() {
				void *registryLink;

				if (RegistryProcess::checkAndRegisterKey(
				        registryKey(), registryLink, [] { return (singletonLink.get() == nullptr); }, [](void *this__) {
						T *this_ = reinterpret_cast<T *>
							(this__);
						singletonLink.set(this_); })) {
					TMemorySystem<T>::initMemory();

					T *this_ = TMemorySystem<T>::newMemory();
					TIfHasIncReferenceCount<T>::incReferenceCount(this_);

					singletonLink.set(this_);

					RegistryProcess::setValue(
					    registryLink,
					    RegistryLevel::Singleton,
					    this_,
					    resourceDelete,
					    (THasActiveFinalizer<T>::value) ? resourceFinalizer : nullptr);
				};
			};
	};

	template <typename T>
	const char *TSingletonProcess<T>::registryKey() {
		return typeid(TSingletonProcess<T>).name();
	};

	template <typename T>
	TAtomic<T *> TSingletonProcess<T>::singletonLink(nullptr);

	template <typename T>
	void TSingletonProcess<T>::resourceDelete(void *this_) {
		TMemorySystem<T>::deleteMemory(reinterpret_cast<T *>(this_));
	};

	template <typename T>
	void TSingletonProcess<T>::resourceFinalizer(void *this_) {
		TIfHasActiveFinalizer<T>::activeFinalizer(reinterpret_cast<T *>(this_));
	};

};

#endif

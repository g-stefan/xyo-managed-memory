// Managed Memory
// Copyright (c) 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_TREFERENCE_HPP
#define XYO_MANAGEDMEMORY_TREFERENCE_HPP

#ifndef XYO_MANAGEDMEMORY_DEPENDENCY_HPP
#	include <XYO/ManagedMemory/Dependency.hpp>
#endif

namespace XYO::ManagedMemory {

	template <typename T, void DeleteMemoryT(T *)>
	class TReference {
		protected:
			T *object;

		public:
			inline TReference() = delete;

			inline ~TReference() {
				DeleteMemoryT(object);
			};

			//

			inline TReference(const T *value) {
				object = const_cast<T *>(value);
			};

			inline TReference(const TReference &value) = delete;
			inline TReference(TReference &&value) = delete;

			//

			inline TReference &operator=(const TReference &value) = delete;
			inline TReference &operator=(TReference &&value) = delete;

			//

			inline T *operator->() const {
				return object;
			};

			inline operator T *() const {
				return object;
			};

			inline T *value() const {
				return object;
			};
	};

};

#endif

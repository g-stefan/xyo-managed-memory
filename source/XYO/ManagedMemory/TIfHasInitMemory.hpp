// Managed Memory
// Copyright (c) 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT
#ifndef XYO_MANAGEDMEMORY_TIFHASINITMEMORY_HPP
#define XYO_MANAGEDMEMORY_TIFHASINITMEMORY_HPP

#ifndef XYO_MANAGEDMEMORY_DEPENDENCY_HPP
#	include <XYO/ManagedMemory/Dependency.hpp>
#endif

namespace XYO::ManagedMemory {

	template <typename T>
	class THasInitMemory {
		protected:
			template <typename U, void (*)()>
			struct TCheckMember;

			template <typename U>
			static char TTestMember(TCheckMember<U, &U::initMemory> *);

			template <typename U>
			static int TTestMember(...);

		public:
			static const bool value = sizeof(TTestMember<T>(nullptr)) == sizeof(char);
	};

	template <typename T, bool hasInitMemory>
	struct TIfHasInitMemoryBase {
			static inline void initMemory(){};
	};

	template <typename T>
	struct TIfHasInitMemoryBase<T, true> {
			static inline void initMemory() {
				T::initMemory();
			};
	};

	template <typename T>
	struct TIfHasInitMemory : TIfHasInitMemoryBase<T, THasInitMemory<T>::value> {
	};

};

#endif

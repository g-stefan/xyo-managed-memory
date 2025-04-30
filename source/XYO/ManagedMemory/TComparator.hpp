// Managed Memory
// Copyright (c) 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_TCOMPARATOR_HPP
#define XYO_MANAGEDMEMORY_TCOMPARATOR_HPP

#ifndef XYO_MANAGEDMEMORY_DEPENDENCY_HPP
#	include <XYO/ManagedMemory/Dependency.hpp>
#endif

namespace XYO::ManagedMemory {

	template <typename T>
	struct TComparator {

			static inline bool isEqual(const T &x, const T &y) {
				return x == y;
			};

			static inline bool isNotEqual(const T &x, const T &y) {
				return x != y;
			};

			static inline bool isLess(const T &x, const T &y) {
				return x < y;
			};

			static inline bool isGreater(const T &x, const T &y) {
				return x > y;
			};

			static inline bool isLessOrEqual(const T &x, const T &y) {
				return x <= y;
			};

			static inline bool isGreaterOrEqual(const T &x, const T &y) {
				return x >= y;
			};

			static inline int compare(const T &x, const T &y) {
				if (x < y) {
					return -1;
				};
				if (x == y) {
					return 0;
				};
				return 1;
			};
	};

};

#ifndef XYO_MANAGEDMEMORY_TCOMPARATOR_STRING_CHAR_HPP
#	include <XYO/ManagedMemory/TComparator-String-Char.hpp>
#endif

#endif

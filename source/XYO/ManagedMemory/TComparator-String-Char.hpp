// Managed Memory
// Copyright (c) 2022 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2022 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_TCOMPARATOR_STRING_CHAR_HPP
#define XYO_MANAGEDMEMORY_TCOMPARATOR_STRING_CHAR_HPP

#ifndef XYO_MANAGEDMEMORY_TCOMPARATOR_HPP
#	include <XYO/ManagedMemory/TComparator.hpp>
#endif

namespace XYO::ManagedMemory {

	template <>
	struct TComparator<const char *> {

			static inline bool isEqual(const char *x, const char *y) {
				return (strcmp(x, y) == 0);
			};

			static inline bool isNotEqual(const char *x, const char *y) {
				return (strcmp(x, y) != 0);
			};

			static inline bool isLess(const char *x, const char *y) {
				return (strcmp(x, y) < 0);
			};

			static inline bool isGreater(const char *x, const char *y) {
				return (strcmp(x, y) > 0);
			};

			static inline bool isLessOrEqual(const char *x, const char *y) {
				return (strcmp(x, y) <= 0);
			};

			static inline bool isGreaterOrEqual(const char *x, const char *y) {
				return (strcmp(x, y) >= 0);
			};

			static inline int compare(const char *x, const char *y) {
				return strcmp(x, y);
			};
	};

	template <>
	struct TComparator<char *> : TComparator<const char *> {
	};

};

#endif

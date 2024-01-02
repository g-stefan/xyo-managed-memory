// Managed Memory
// Copyright (c) 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_TCOMPARATOR_TPOINTER_HPP
#	define XYO_MANAGEDMEMORY_TCOMPARATOR_TPOINTER__HPP

#	ifndef XYO_MANAGEDMEMORY_TPOINTER_HPP
#		include <XYO/ManagedMemory/TPointer.hpp>
#	endif

#	ifndef XYO_MANAGEDMEMORY_TCOMPARATOR_HPP
#		include <XYO/ManagedMemory/TComparator.hpp>
#	endif

namespace XYO::ManagedMemory {

	template <typename T_>
	struct TComparator<TPointer<T_>> {
			typedef TPointer<T_> T;

			static inline bool isEqual(const T &x, const T &y) {
				return TComparator<T_>::isEqual(*x, *y);
			};

			static inline bool isNotEqual(const T &x, const T &y) {
				return TComparator<T_>::isNotEqual(*x, *y);
			};

			static inline bool isLess(const T &x, const T &y) {
				return TComparator<T_>::isLess(*x, *y);
			};

			static inline bool isGreater(const T &x, const T &y) {
				return TComparator<T_>::isGreater(*x, *y);
			};

			static inline bool isLessOrEqual(const T &x, const T &y) {
				return TComparator<T_>::isLessOrEqual(*x, *y);
			};

			static inline bool isGreaterOrEqual(const T &x, const T &y) {
				return TComparator<T_>::isGreaterOrEqual(*x, *y);
			};

			static inline int compare(const T &x, const T &y) {
				return TComparator<T_>::compare(*x, *y);
			};
	};

};

#endif

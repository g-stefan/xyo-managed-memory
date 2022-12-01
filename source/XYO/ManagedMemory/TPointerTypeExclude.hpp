// Managed Memory
// Copyright (c) 2022 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2022 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_TPOINTERTYPEEXCLUDE_HPP
#define XYO_MANAGEDMEMORY_TPOINTERTYPEEXCLUDE_HPP

#ifndef XYO_MANAGEDMEMORY_TPOINTER_HPP
#	include <XYO/ManagedMemory/TPointer.hpp>
#endif

#ifndef XYO_MANAGEDMEMORY_TPOINTERX_HPP
#	include <XYO/ManagedMemory/TPointerX.hpp>
#endif

namespace XYO::ManagedMemory {

	template <typename T>
	struct TPointerTypeExclude {

			template <typename U>
			struct TUnknownType;
			template <typename U>
			struct TUnknownPointer;
			template <typename U>
			struct TUnknownPointerX;

			typedef TUnknownType<T> Type;
			typedef TUnknownPointer<T> Pointer;
			typedef TUnknownPointerX<T> PointerX;
	};

	template <typename T>
	struct TPointerTypeExclude<TPointer<T>> {

			template <typename U>
			struct TUnknownPointer;

			typedef T Type;
			typedef TUnknownPointer<T> Pointer;
			typedef TPointerX<T> PointerX;
	};

	template <typename T>
	struct TPointerTypeExclude<TPointerX<T>> {

			template <typename U>
			struct TUnknownPointerX;

			typedef T Type;
			typedef TPointer<T> Pointer;
			typedef TUnknownPointerX<T> PointerX;
	};

};

#endif

// Managed Memory
// Copyright (c) 2022 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2022 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_TPOINTERTYPE_HPP
#define XYO_MANAGEDMEMORY_TPOINTERTYPE_HPP

#ifndef XYO_MANAGEDMEMORY_TPOINTER_HPP
#	include <XYO/ManagedMemory/TPointer.hpp>
#endif

#ifndef XYO_MANAGEDMEMORY_TPOINTERX_HPP
#	include <XYO/ManagedMemory/TPointerX.hpp>
#endif

namespace XYO::ManagedMemory {

	template <typename T>
	struct TPointerType {
			typedef T Type;
			typedef TPointer<T> Pointer;
			typedef TPointerX<T> PointerX;
	};

	template <typename T>
	struct TPointerType<TPointer<T>> {
			typedef T Type;
			typedef TPointer<T> Pointer;
			typedef TPointerX<T> PointerX;
	};

	template <typename T>
	struct TPointerType<TPointerX<T>> {
			typedef T Type;
			typedef TPointer<T> Pointer;
			typedef TPointerX<T> PointerX;
	};

};

#endif

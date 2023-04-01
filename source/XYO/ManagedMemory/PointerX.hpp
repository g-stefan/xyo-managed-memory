// Managed Memory
// Copyright (c) 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_POINTERX_HPP
#define XYO_MANAGEDMEMORY_POINTERX_HPP

#ifndef XYO_MANAGEDMEMORY_TXLIST2NODE_HPP
#	include <XYO/ManagedMemory/TXList2Node.hpp>
#endif

namespace XYO::ManagedMemory {

	struct PointerX : TXList2Node<PointerX> {
			class Object *link;
			void *object;
	};

};

#endif

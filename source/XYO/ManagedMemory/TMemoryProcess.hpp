// Managed Memory
// Copyright (c) 2022 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2022 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_TMEMORYPROCESS_HPP
#define XYO_MANAGEDMEMORY_TMEMORYPROCESS_HPP

#ifdef XYO_TMEMORYPOOL_SYSTEM

#	ifndef XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP
#		include <XYO/ManagedMemory/TMemorySystem.hpp>
#	endif

namespace XYO::ManagedMemory {

	template <typename T>
	struct TMemoryProcess : TMemorySystem<T> {};

};

#else

#	ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLPROCESS_HPP
#		include <XYO/ManagedMemory/TMemoryPoolProcess.hpp>
#	endif

namespace XYO::ManagedMemory {

	template <typename T>
	struct TMemoryProcess : TMemoryPoolProcess<T> {};

};

#endif

#endif

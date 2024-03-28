// Managed Memory
// Copyright (c) 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_TMEMORYPOOL_HPP
#define XYO_MANAGEDMEMORY_TMEMORYPOOL_HPP

#ifdef XYO_MANAGEDMEMORY_TMEMORYPOOL_SYSTEM

#	ifndef XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP
#		include <XYO/ManagedMemory/TMemorySystem.hpp>
#	endif

namespace XYO::ManagedMemory {

	template <typename T>
	struct TMemoryPool : TMemorySystem<T> {};

};

#else

#	ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLPROCESS_HPP
#		include <XYO/ManagedMemory/TMemoryPoolProcess.hpp>
#	endif

#	ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLTHREAD_HPP
#		include <XYO/ManagedMemory/TMemoryPoolThread.hpp>
#	endif

namespace XYO::ManagedMemory {

	template <typename T>
	struct TMemoryPool : TMemoryPoolThread<T> {};

};

#endif

#endif

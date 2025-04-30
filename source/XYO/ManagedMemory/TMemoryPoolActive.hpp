// Managed Memory
// Copyright (c) 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLACTIVE_HPP
#define XYO_MANAGEDMEMORY_TMEMORYPOOLACTIVE_HPP

#ifdef XYO_MANAGEDMEMORY_TMEMORYPOOL_SYSTEM

#	ifndef XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP
#		include <XYO/ManagedMemory/TMemorySystem.hpp>
#	endif

namespace XYO::ManagedMemory {

	template <typename T>
	struct TMemoryPoolActive : TMemorySystem<T> {};

};

#elif defined(XYO_MANAGEDMEMORY_TMEMORYPOOL_ACTIVE_AS_UNIFIED)

#	ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLUNIFIED_HPP
#		include <XYO/ManagedMemory/TMemoryPoolUnified.hpp>
#	endif

namespace XYO::ManagedMemory {

	template <typename T>
	struct TMemoryPoolActive : TMemoryPoolUnified<T> {};

};

#else

#	ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLACTIVEPROCESS_HPP
#		include <XYO/ManagedMemory/TMemoryPoolActiveProcess.hpp>
#	endif

#	ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLACTIVETHREAD_HPP
#		include <XYO/ManagedMemory/TMemoryPoolActiveThread.hpp>
#	endif

namespace XYO::ManagedMemory {

	template <typename T>
	struct TMemoryPoolActive : TMemoryPoolActiveThread<T> {};

};

#endif

#endif

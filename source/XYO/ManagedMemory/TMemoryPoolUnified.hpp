// Managed Memory
// Copyright (c) 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLUNIFIED_HPP
#define XYO_MANAGEDMEMORY_TMEMORYPOOLUNIFIED_HPP

#ifdef XYO_MANAGEDMEMORY_TMEMORYPOOL_SYSTEM

#	ifndef XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP
#		include <XYO/ManagedMemory/TMemorySystem.hpp>
#	endif

namespace XYO::ManagedMemory {

	template <typename T>
	struct TMemoryPoolUnified : TMemorySystem<T> {};

};

#else

#	ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLUNIFIEDPROCESS_HPP
#		include <XYO/ManagedMemory/TMemoryPoolUnifiedProcess.hpp>
#	endif

#	ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLUNIFIEDTHREAD_HPP
#		include <XYO/ManagedMemory/TMemoryPoolUnifiedThread.hpp>
#	endif

namespace XYO::ManagedMemory {

	template <typename T>
	struct TMemoryPoolUnified : TMemoryPoolUnifiedThread<T> {};

};

#endif

#endif

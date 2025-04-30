// Managed Memory
// Copyright (c) 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_TMEMORY_HPP
#define XYO_MANAGEDMEMORY_TMEMORY_HPP

#ifndef XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP
#	include <XYO/ManagedMemory/TMemorySystem.hpp>
#endif

#ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLUNIFIED_HPP
#	include <XYO/ManagedMemory/TMemoryPoolUnified.hpp>
#endif

#ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLACTIVE_HPP
#	include <XYO/ManagedMemory/TMemoryPoolActive.hpp>
#endif

#ifndef XYO_MANAGEDMEMORY_TMEMORYPROCESS_HPP
#	include <XYO/ManagedMemory/TMemoryProcess.hpp>
#endif

#ifndef XYO_MANAGEDMEMORY_TMEMORYTHREAD_HPP
#	include <XYO/ManagedMemory/TMemoryThread.hpp>
#endif

#ifndef XYO_MANAGEDMEMORY_TMEMORYPOOL_HPP
#	include <XYO/ManagedMemory/TMemoryPool.hpp>
#endif

#ifdef XYO_MANAGEDMEMORY_TMEMORYPOOL_SYSTEM

namespace XYO::ManagedMemory {

	template <typename T>
	struct TMemory : TMemorySystem<T> {};

};

#else

namespace XYO::ManagedMemory {

	template <typename T>
	struct TMemory : TMemoryThread<T> {};

};

#endif

#endif

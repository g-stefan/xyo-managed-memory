// Managed Memory
// Copyright (c) 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_DEPENDENCY_HPP
#define XYO_MANAGEDMEMORY_DEPENDENCY_HPP

#ifndef XYO_PLATFORM_HPP
#	include <XYO/Platform.hpp>
#endif

#ifndef XYO_MANAGEDMEMORY_CONFIG_HPP
#	include <XYO/ManagedMemory/Config.hpp>
#endif

// -- Export

#ifndef XYO_MANAGEDMEMORY_INTERNAL
#	ifdef XYO_MANAGED_MEMORY_INTERNAL
#		define XYO_MANAGEDMEMORY_INTERNAL
#	endif
#endif

#ifdef XYO_MANAGEDMEMORY_INTERNAL
#	define XYO_MANAGEDMEMORY_EXPORT XYO_PLATFORM_LIBRARY_EXPORT
#else
#	define XYO_MANAGEDMEMORY_EXPORT XYO_PLATFORM_LIBRARY_IMPORT
#endif
#ifdef XYO_MANAGEDMEMORY_LIBRARY
#	undef XYO_MANAGEDMEMORY_EXPORT
#	define XYO_MANAGEDMEMORY_EXPORT
#endif

namespace XYO::ManagedMemory {
	using namespace XYO::Platform;
	using XYO::Platform::Multithreading::CriticalSection;
	using XYO::Platform::Multithreading::TAtomic;
};

#endif

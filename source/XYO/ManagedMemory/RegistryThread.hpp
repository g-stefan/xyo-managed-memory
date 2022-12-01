// Managed Memory
// Copyright (c) 2022 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2022 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_REGISTRYTHREAD_HPP
#define XYO_MANAGEDMEMORY_REGISTRYTHREAD_HPP

#ifndef XYO_MANAGEDMEMORY_REGISTRYLEVEL_HPP
#	include <XYO/ManagedMemory/RegistryLevel.hpp>
#endif

#ifndef XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP
#	include <XYO/ManagedMemory/TMemorySystem.hpp>
#endif

#ifdef XYO_MULTI_THREAD
namespace XYO::ManagedMemory {
	namespace RegistryThread {

		XYO_MANAGEDMEMORY_EXPORT void processBegin();
		XYO_MANAGEDMEMORY_EXPORT void processEnd();
		XYO_MANAGEDMEMORY_EXPORT void threadBegin();
		XYO_MANAGEDMEMORY_EXPORT void threadEnd();
		XYO_MANAGEDMEMORY_EXPORT bool registerKey(const char *registryKey, size_t &registryLink);
		XYO_MANAGEDMEMORY_EXPORT void setValue(size_t registryLink, size_t categoryLevel, void *resourceThis, DeleteMemory deleteResource, FinalizeMemory finalizeResource);
		XYO_MANAGEDMEMORY_EXPORT void *getValue(size_t registryLink);
		XYO_MANAGEDMEMORY_EXPORT size_t getKey(const char *registryKey);

	};
};
#endif

#endif

// Managed Memory
// Copyright (c) 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_REGISTRYPROCESS_HPP
#define XYO_MANAGEDMEMORY_REGISTRYPROCESS_HPP

#ifndef XYO_MANAGEDMEMORY_REGISTRYLEVEL_HPP
#	include <XYO/ManagedMemory/RegistryLevel.hpp>
#endif

#ifndef XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP
#	include <XYO/ManagedMemory/TMemorySystem.hpp>
#endif

namespace XYO::ManagedMemory::RegistryProcess {

	XYO_MANAGEDMEMORY_EXPORT void processBegin();
	XYO_MANAGEDMEMORY_EXPORT void processEnd();
	XYO_MANAGEDMEMORY_EXPORT bool checkAndRegisterKey(const char *registryKey, void *&registryLink, const std::function<bool()> &valueIsNullptr, const std::function<void(void *)> &setValue);
	XYO_MANAGEDMEMORY_EXPORT void setValue(void *registryLink, size_t categoryLevel, void *resourceThis, DeleteMemory deleteResource, FinalizeMemory finalizerResource);
	XYO_MANAGEDMEMORY_EXPORT void *getValue(void *registryLink);
	XYO_MANAGEDMEMORY_EXPORT void *getKey(const char *registryKey);

};

#endif

// Managed Memory
// Copyright (c) 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_VERSION_HPP
#define XYO_MANAGEDMEMORY_VERSION_HPP

#ifndef XYO_MANAGEDMEMORY_DEPENDENCY_HPP
#	include <XYO/ManagedMemory/Dependency.hpp>
#endif

namespace XYO::ManagedMemory::Version {

	XYO_MANAGEDMEMORY_EXPORT const char *version();
	XYO_MANAGEDMEMORY_EXPORT const char *build();
	XYO_MANAGEDMEMORY_EXPORT const char *versionWithBuild();
	XYO_MANAGEDMEMORY_EXPORT const char *datetime();

};

#endif

// Managed Memory
// Copyright (c) 2022 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2022 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_COPYRIGHT_HPP
#define XYO_MANAGEDMEMORY_COPYRIGHT_HPP

#ifndef XYO_MANAGEDMEMORY_DEPENDENCY_HPP
#	include <XYO/ManagedMemory/Dependency.hpp>
#endif

namespace XYO::ManagedMemory::Copyright {
	XYO_MANAGEDMEMORY_EXPORT const char *copyright();
	XYO_MANAGEDMEMORY_EXPORT const char *publisher();
	XYO_MANAGEDMEMORY_EXPORT const char *company();
	XYO_MANAGEDMEMORY_EXPORT const char *contact();
	XYO_MANAGEDMEMORY_EXPORT const char *fullCopyright();
};

#endif

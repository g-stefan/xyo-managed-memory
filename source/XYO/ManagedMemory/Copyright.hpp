// Managed Memory
// Copyright (c) 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_COPYRIGHT_HPP
#define XYO_MANAGEDMEMORY_COPYRIGHT_HPP

#ifndef XYO_MANAGEDMEMORY_DEPENDENCY_HPP
#	include <XYO/ManagedMemory/Dependency.hpp>
#endif

namespace XYO::ManagedMemory::Copyright {
	XYO_MANAGEDMEMORY_EXPORT std::string copyright();
	XYO_MANAGEDMEMORY_EXPORT std::string publisher();
	XYO_MANAGEDMEMORY_EXPORT std::string company();
	XYO_MANAGEDMEMORY_EXPORT std::string contact();
};

#endif

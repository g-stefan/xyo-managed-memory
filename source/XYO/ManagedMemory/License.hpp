// Managed Memory
// Copyright (c) 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_LICENSE_HPP
#define XYO_MANAGEDMEMORY_LICENSE_HPP

#ifndef XYO_MANAGEDMEMORY_DEPENDENCY_HPP
#	include <XYO/ManagedMemory/Dependency.hpp>
#endif

namespace XYO::ManagedMemory::License {

	XYO_MANAGEDMEMORY_EXPORT std::string license();
	XYO_MANAGEDMEMORY_EXPORT std::string shortLicense();
	XYO_MANAGEDMEMORY_EXPORT std::string licenseMITShort();
	XYO_MANAGEDMEMORY_EXPORT std::string licenseMITHeader();
	XYO_MANAGEDMEMORY_EXPORT std::string licenseMITContent();

};

#endif

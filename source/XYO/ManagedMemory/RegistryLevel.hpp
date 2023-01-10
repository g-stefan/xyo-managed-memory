// Managed Memory
// Copyright (c) 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_REGISTRYLEVEL_HPP
#define XYO_MANAGEDMEMORY_REGISTRYLEVEL_HPP

#ifndef XYO_MANAGEDMEMORY_DEPENDENCY_HPP
#	include <XYO/ManagedMemory/Dependency.hpp>
#endif

namespace XYO::ManagedMemory {
	namespace RegistryLevel {

		enum {
			System = 0,
			Static = 1,
			Active = 2,
			Singleton = 3
		};

	};
};

#endif

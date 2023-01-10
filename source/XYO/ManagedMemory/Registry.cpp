// Managed Memory
// Copyright (c) 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/ManagedMemory/Registry.hpp>
#include <XYO/ManagedMemory/RegistryProcess.hpp>

namespace XYO::ManagedMemory::Registry {

	class RegistryInit {
		public:
			RegistryInit();
			~RegistryInit();
	};

	RegistryInit::RegistryInit() {
		RegistryProcess::processBegin();
	};

	RegistryInit::~RegistryInit() {
		RegistryProcess::processEnd();
	};

	void *registryInit() {
		static bool registryInitIsRecursive = false;
		if (registryInitIsRecursive) {
			return nullptr;
		};
		registryInitIsRecursive = true;
		static RegistryInit registryInitInstance;
		registryInitIsRecursive = false;
		return &registryInitInstance;
	};

};

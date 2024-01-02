// Managed Memory
// Copyright (c) 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_REGISTRYDATA_HPP
#define XYO_MANAGEDMEMORY_REGISTRYDATA_HPP

#ifndef XYO_MANAGEDMEMORY_TXLIST2_HPP
#	include <XYO/ManagedMemory/TXList2.hpp>
#endif

namespace XYO::ManagedMemory {

	struct RegistryDataNode : TXList2Node<RegistryDataNode> {
			void *resourceThis;
			DeleteMemory deleteResource;
			FinalizeMemory finalizeResource;
	};

	typedef TXList2<RegistryDataNode> RegistryDataList;

	namespace RegistryData {

		XYO_MANAGEDMEMORY_EXPORT void finalizeResource(RegistryDataNode *this_);
		XYO_MANAGEDMEMORY_EXPORT void deleteResource(RegistryDataNode *this_);

	};

};

#endif

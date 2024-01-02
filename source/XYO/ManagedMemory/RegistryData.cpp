// Managed Memory
// Copyright (c) 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/ManagedMemory/RegistryData.hpp>

namespace XYO::ManagedMemory {

	namespace RegistryData {

		void finalizeResource(RegistryDataNode *this_) {
			RegistryDataNode *scan;
			for (scan = this_; scan; scan = scan->next) {
				if (scan->resourceThis) {
					if (scan->finalizeResource) {
						(*scan->finalizeResource)(scan->resourceThis);
					};
				};
			};
		};

		void deleteResource(RegistryDataNode *this_) {
			RegistryDataNode *scan;
			for (scan = this_; scan; scan = scan->next) {
				if (scan->resourceThis) {
					if (scan->deleteResource) {
						(*scan->deleteResource)(scan->resourceThis);
					};
				};
			};
		};

	};
};

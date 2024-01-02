// Managed Memory
// Copyright (c) 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_REGISTRYKEY_HPP
#define XYO_MANAGEDMEMORY_REGISTRYKEY_HPP

#ifndef XYO_MANAGEDMEMORY_TXREDBLACKTREE_HPP
#	include <XYO/ManagedMemory/TXRedBlackTree.hpp>
#endif

#ifndef XYO_MANAGEDMEMORY_TATOMIC_HPP
#	include <XYO/ManagedMemory/TAtomic.hpp>
#endif

namespace XYO::ManagedMemory {

	struct RegistryKeyNode : TXRedBlackTreeNode<RegistryKeyNode, const char *> {
			TAtomic<void *> processValue;
			size_t threadValue;
	};

	typedef TXRedBlackTree<RegistryKeyNode> RegistryKeyRBTree;

	namespace RegistryKey {

		XYO_MANAGEDMEMORY_EXPORT bool checkAndRegisterKey(const char *key, RegistryKeyNode *&this_);
		XYO_MANAGEDMEMORY_EXPORT RegistryKeyNode *getKey(const char *key);

		XYO_MANAGEDMEMORY_EXPORT void processBegin();
		XYO_MANAGEDMEMORY_EXPORT void processEnd();

#ifdef XYO_MULTI_THREAD
		XYO_MANAGEDMEMORY_EXPORT void criticalEnter();
		XYO_MANAGEDMEMORY_EXPORT void criticalLeave();
#endif

#ifdef XYO_SINGLE_THREAD
		inline void criticalEnter(){};

		inline void criticalLeave(){};
#endif

	};

};

#endif

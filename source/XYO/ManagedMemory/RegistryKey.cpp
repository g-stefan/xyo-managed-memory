// Managed Memory
// Copyright (c) 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/ManagedMemory/RegistryKey.hpp>

namespace XYO::ManagedMemory {

	namespace RegistryKey {
		using namespace XYO::Platform::Multithreading;

		static RegistryKeyNode *root = nullptr;
		static size_t threadKey;

		typedef RegistryKeyRBTree RBTree;

#ifdef XYO_PLATFORM_MULTI_THREAD
		static CriticalSection *criticalSection;
#endif

		bool checkAndRegisterKey(const char *key, RegistryKeyNode *&this_) {
#ifdef XYO_PLATFORM_MULTI_THREAD
			criticalSection->enter();
			this_ = RBTree::find(root, key);
			if (this_ != nullptr) {
				criticalSection->leave();
				return false;
			};

			try {
				this_ = RBTree::newNode();
			} catch (...) {
				criticalSection->leave();
				throw;
			};

			this_->key = key;
			this_->processValue.set(nullptr);
			this_->threadValue = threadKey;

			threadKey++;

			RBTree::insertNode(root, this_);

			criticalSection->leave();

			return true;
#endif

#ifdef XYO_PLATFORM_SINGLE_THREAD
			this_ = RBTree::find(root, key);
			if (this_ != nullptr) {
				return false;
			};

			this_ = RBTree::newNode();

			this_->key = key;
			this_->processValue.set(nullptr);
			this_->threadValue = threadKey;

			threadKey++;

			RBTree::insertNode(root, this_);

			return true;
#endif
		};

		RegistryKeyNode *getKey(const char *key) {
#ifdef XYO_PLATFORM_MULTI_THREAD
			RegistryKeyNode *this_;
			criticalSection->enter();
			this_ = RBTree::find(root, key);
			criticalSection->leave();
			return this_;
#endif
#ifdef XYO_PLATFORM_SINGLE_THREAD
			return RBTree::find(root, key);
#endif
		};

		void processBegin() {

#ifdef XYO_PLATFORM_MULTI_THREAD
			criticalSection = new CriticalSection();
#endif

			RBTree::constructor(root);
			threadKey = 1;
		};

		void processEnd() {

			RBTree::destructor(root);

#ifdef XYO_PLATFORM_MULTI_THREAD
			delete criticalSection;
#endif
		};

#ifdef XYO_PLATFORM_MULTI_THREAD

		void criticalEnter() {
			criticalSection->enter();
		};

		void criticalLeave() {
			criticalSection->leave();
		};

#endif

	};
};

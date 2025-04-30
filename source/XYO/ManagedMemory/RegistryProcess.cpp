// Managed Memory
// Copyright (c) 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/ManagedMemory/RegistryData.hpp>
#include <XYO/ManagedMemory/RegistryKey.hpp>
#include <XYO/ManagedMemory/Registry.hpp>
#include <XYO/ManagedMemory/RegistryThread.hpp>
#include <XYO/ManagedMemory/RegistryProcess.hpp>

#ifdef XYO_PLATFORM_OS_WINDOWS
#	include <windows.h>
#endif

#ifdef XYO_PLATFORM_OS_LINUX
#	include <pthread.h>
#	include <unistd.h>
#	include <time.h>
#endif

namespace XYO::ManagedMemory::RegistryProcess {

	typedef RegistryDataList List;

	static RegistryDataNode *data[4];

	void processBegin() {

		RegistryKey::processBegin();

		List::constructor(data[RegistryLevel::Singleton]);
		List::constructor(data[RegistryLevel::Active]);
		List::constructor(data[RegistryLevel::Static]);
		List::constructor(data[RegistryLevel::System]);

#ifdef XYO_PLATFORM_MULTI_THREAD
		RegistryThread::processBegin();
#endif
	};

	void processEnd() {

#ifdef XYO_PLATFORM_MULTI_THREAD
		RegistryThread::processEnd();
#endif
		RegistryData::finalizeResource(data[RegistryLevel::Singleton]);
		RegistryData::finalizeResource(data[RegistryLevel::Active]);
		RegistryData::finalizeResource(data[RegistryLevel::Static]);
		RegistryData::finalizeResource(data[RegistryLevel::System]);

		RegistryData::deleteResource(data[RegistryLevel::Singleton]);
		RegistryData::deleteResource(data[RegistryLevel::Active]);
		RegistryData::deleteResource(data[RegistryLevel::Static]);
		RegistryData::deleteResource(data[RegistryLevel::System]);

		List::destructor(data[RegistryLevel::Singleton]);
		List::destructor(data[RegistryLevel::Active]);
		List::destructor(data[RegistryLevel::Static]);
		List::destructor(data[RegistryLevel::System]);

		RegistryKey::processEnd();
	};

	bool checkAndRegisterKey(const char *registryKey, void *&registryLink, const std::function<bool()> &valueIsNullptr, const std::function<void(void *)> &setValue) {
		Registry::registryInit();

		if (RegistryKey::checkAndRegisterKey(registryKey, reinterpret_cast<RegistryKeyNode *&>(registryLink))) {
			return true;
		};

		setValue(reinterpret_cast<RegistryKeyNode *&>(registryLink)->processValue.get());

#ifdef XYO_PLATFORM_MULTI_THREAD

		while (valueIsNullptr()) {
			Platform::Multithreading::Thread::sleep(1);
			setValue(reinterpret_cast<RegistryKeyNode *&>(registryLink)->processValue.get());
		};

#endif

		return false;
	};

	void setValue(void *registryLink, size_t categoryLevel, void *resourceThis, DeleteMemory deleteResource, FinalizeMemory finalizeResource) {
		RegistryDataNode *node = List::newNode();
		List::push(data[categoryLevel], node);
		node->resourceThis = resourceThis;
		node->deleteResource = deleteResource;
		node->finalizeResource = finalizeResource;
		(reinterpret_cast<RegistryKeyNode *>(registryLink))->processValue.set(resourceThis);
	};

	void *getValue(void *registryLink) {
		return (reinterpret_cast<RegistryKeyNode *>(registryLink))->processValue.get();
	};

	void *getKey(const char *registryKey) {
		RegistryKeyNode *node = RegistryKey::getKey(registryKey);
		if (node) {
			return node->processValue;
		};
		return nullptr;
	};

};

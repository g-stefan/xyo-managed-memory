// Managed Memory
// Copyright (c) 2022 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2022 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/ManagedMemory/Dependency.hpp>
#include <XYO/ManagedMemory/CriticalSection.hpp>

#ifdef XYO_OS_LINUX

#	include <pthread.h>
#	include <unistd.h>

#	ifdef XYO_MULTI_THREAD

namespace XYO::ManagedMemory {

	class CriticalSection_ {
		public:
			pthread_mutex_t section;
	};

	CriticalSection::CriticalSection() {
		criticalSection = new CriticalSection_();
		if (pthread_mutex_init(&criticalSection->section, nullptr)) {
			throw std::runtime_error("pthread_mutex_init");
		};
	};

	CriticalSection::~CriticalSection() noexcept(false) {
		if (pthread_mutex_destroy(&criticalSection->section)) {
			throw std::runtime_error("pthread_mutex_destroy");
		};
		delete criticalSection;
	};

	void CriticalSection::enter() {
		if (pthread_mutex_lock(&criticalSection->section)) {
			throw std::runtime_error("pthread_mutex_lock");
		};
	};

	void CriticalSection::leave() {
		if (pthread_mutex_unlock(&criticalSection->section)) {
			throw std::runtime_error("pthread_mutex_unlock");
		};
	};

};

#	endif

#endif

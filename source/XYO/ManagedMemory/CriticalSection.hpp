// Managed Memory
// Copyright (c) 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_CRITICALSECTION_HPP
#define XYO_MANAGEDMEMORY_CRITICALSECTION_HPP

#ifndef XYO_MANAGEDMEMORY_DEPENDENCY_HPP
#	include <XYO/ManagedMemory/Dependency.hpp>
#endif

#ifdef XYO_MULTI_THREAD
namespace XYO::ManagedMemory {

	class CriticalSection_;

	class CriticalSection {
			XYO_DISALLOW_COPY_ASSIGN_MOVE(CriticalSection);

		protected:
			CriticalSection_ *criticalSection;

		public:
			static const bool isCriticalSection = true;

			XYO_MANAGEDMEMORY_EXPORT CriticalSection();
#	ifdef XYO_OS_LINUX
			XYO_MANAGEDMEMORY_EXPORT ~CriticalSection() noexcept(false);
#	else
			XYO_MANAGEDMEMORY_EXPORT ~CriticalSection();
#	endif

			XYO_MANAGEDMEMORY_EXPORT void enter();
			XYO_MANAGEDMEMORY_EXPORT void leave();
	};

};
#endif

#ifdef XYO_SINGLE_THREAD
namespace XYO::ManagedMemory {

	class CriticalSection {
			XYO_DISALLOW_COPY_ASSIGN_MOVE(CriticalSection);

		public:
			static const bool isCriticalSection = false;

			CriticalSection() = default;

			inline void enter(){};

			inline void leave(){};
	};

};
#endif

#endif

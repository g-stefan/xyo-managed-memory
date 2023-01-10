// Managed Memory
// Copyright (c) 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_TSINGLETON_HPP
#define XYO_MANAGEDMEMORY_TSINGLETON_HPP

#ifndef XYO_MANAGEDMEMORY_TSINGLETONPROCESS_HPP
#	include <XYO/ManagedMemory/TSingletonProcess.hpp>
#endif

#ifndef XYO_MANAGEDMEMORY_TSINGLETONTHREAD_HPP
#	include <XYO/ManagedMemory/TSingletonThread.hpp>
#endif

namespace XYO::ManagedMemory {

	template <typename T>
	struct TSingleton : TSingletonThread<T> {};

};

#endif

// Managed Memory
// Copyright (c) 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_DEPENDENCY_HPP
#define XYO_MANAGEDMEMORY_DEPENDENCY_HPP

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <typeinfo>
#include <utility>
#include <stdexcept>
#include <new>
#include <atomic>
#include <functional>
#include <type_traits>

#ifndef XYO_MANAGEDMEMORY_CONFIG_HPP
#	include <XYO/ManagedMemory/Config.hpp>
#endif

// -- Export

#ifdef XYO_COMPILE_DYNAMIC_LIBRARY
#	ifndef XYO_LIBRARY_EXPORT
#		ifdef XYO_COMPILER_MSVC
#			define XYO_LIBRARY_EXPORT __declspec(dllexport)
#		endif
#		ifdef XYO_COMPILER_GCC
#			define XYO_LIBRARY_EXPORT
#		endif
#	endif
#	ifndef XYO_LIBRARY_IMPORT
#		ifdef XYO_COMPILER_MSVC
#			define XYO_LIBRARY_IMPORT __declspec(dllimport)
#		endif
#		ifdef XYO_COMPILER_GCC
#			define XYO_LIBRARY_IMPORT
#		endif
#	endif
#else
#	ifndef XYO_LIBRARY_EXPORT
#		define XYO_LIBRARY_EXPORT
#	endif
#	ifndef XYO_LIBRARY_IMPORT
#		define XYO_LIBRARY_IMPORT
#	endif
#endif

#ifndef XYO_MANAGEDMEMORY_INTERNAL
#	ifdef XYO_MANAGED_MEMORY_INTERNAL
#		define XYO_MANAGEDMEMORY_INTERNAL
#	endif
#endif

#ifdef XYO_MANAGEDMEMORY_INTERNAL
#	define XYO_MANAGEDMEMORY_EXPORT XYO_LIBRARY_EXPORT
#else
#	define XYO_MANAGEDMEMORY_EXPORT XYO_LIBRARY_IMPORT
#endif

// -- Defaults

#ifndef XYO_MULTI_THREAD
#	ifndef XYO_SINGLE_THREAD
#		define XYO_MULTI_THREAD
#	endif
#endif

#ifndef XYO_APPLICATION_64BIT
#	ifndef XYO_APPLICATION_32BIT
#		define XYO_APPLICATION_64BIT
#	endif
#endif

#ifdef XYO_OS_MINGW
#	ifndef XYO_OS_WINDOWS
#		define XYO_OS_WINDOWS
#	endif
#endif

// -- Checking

#ifndef XYO_COMPILER_MSVC
#	ifndef XYO_COMPILER_GCC
#		error "XYO_COMPILER_MSVC or XYO_COMPILER_GCC must be defined"
#	endif
#endif

#ifndef XYO_OS_WINDOWS
#	ifndef XYO_OS_LINUX
#		ifndef XYO_OS_MINGW
#			error "XYO_OS_WINDOWS or XYO_OS_LINUX or XYO_OS_MINGW must be defined"
#		endif
#	endif
#endif

#ifndef XYO_MULTI_THREAD
#	ifndef XYO_SINGLE_THREAD
#		error "XYO_MULTI_THREAD or XYO_SINGLE_THREAD must be defined"
#	endif
#endif

#ifndef XYO_APPLICATION_64BIT
#	ifndef XYO_APPLICATION_32BIT
#		error "XYO_APPLICATION_64BIT or XYO_APPLICATION_32BIT must be defined"
#	endif
#endif

//

#ifdef XYO_OS_WINDOWS
#	ifdef XYO_MEMORY_LEAK_DETECTOR_VLD
#		ifndef WIN32_LEAN_AND_MEAN
#			define WIN32_LEAN_AND_MEAN
#		endif
#		include <windows.h>
#		include "vld.h"
#	endif
#endif

//

#ifdef XYO_MULTI_THREAD
#	ifdef XYO_COMPILER_MSVC
#		define XYO_THREAD_LOCAL __declspec(thread)
#	endif
#	ifdef XYO_COMPILER_GCC
#		define XYO_THREAD_LOCAL __thread
#	endif
#else
#	define XYO_THREAD_LOCAL
#endif

//

#ifdef XYO_APPLICATION_64BIT
#	ifdef XYO_COMPILER_GCC
#		define XYO_FORMAT_SIZET "%lu"
#	else
#		define XYO_FORMAT_SIZET "%llu"
#	endif
#else
#	define XYO_FORMAT_SIZET "%lu"
#endif

//

#define XYO_DISALLOW_COPY_ASSIGN_MOVE(T)  \
private:                                  \
	T(const T &) = delete;            \
	T(T &&) = delete;                 \
	T &operator=(const T &) = delete; \
	T &operator=(T &&) = delete

#define XYO_INTERFACE(T) \
protected:               \
	T() = default;   \
	~T() = default;  \
	XYO_DISALLOW_COPY_ASSIGN_MOVE(T)

#endif

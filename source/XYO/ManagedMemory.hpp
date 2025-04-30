// Managed Memory
// Copyright (c) 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_HPP
#define XYO_MANAGEDMEMORY_HPP

#include <XYO/ManagedMemory/Dependency.hpp>
#include <XYO/ManagedMemory/Copyright.hpp>
#include <XYO/ManagedMemory/License.hpp>
#include <XYO/ManagedMemory/Version.hpp>

// -

#include <XYO/ManagedMemory/DeleteMemory.hpp>
#include <XYO/ManagedMemory/FinalizeMemory.hpp>
#include <XYO/ManagedMemory/TGetClassOfMember.hpp>
#include <XYO/ManagedMemory/TComparator.hpp>
#include <XYO/ManagedMemory/TIfHasInitMemory.hpp>
#include <XYO/ManagedMemory/TIfHasIncReferenceCount.hpp>
#include <XYO/ManagedMemory/TIfHasDecReferenceCount.hpp>
#include <XYO/ManagedMemory/TIfHasSetDeleteMemory.hpp>
#include <XYO/ManagedMemory/TIfHasPointerLink.hpp>
#include <XYO/ManagedMemory/TIfHasActiveConstructor.hpp>
#include <XYO/ManagedMemory/TIfHasActiveDestructor.hpp>
#include <XYO/ManagedMemory/TIfHasActiveFinalizer.hpp>
#include <XYO/ManagedMemory/Registry.hpp>
#include <XYO/ManagedMemory/PointerX.hpp>
#include <XYO/ManagedMemory/Object.hpp>
#include <XYO/ManagedMemory/TTransfer.hpp>
#include <XYO/ManagedMemory/TPointer.hpp>
#include <XYO/ManagedMemory/TPointerX.hpp>
#include <XYO/ManagedMemory/TMemorySystem.hpp>

// --

#include <XYO/ManagedMemory/TXList1.hpp>
#include <XYO/ManagedMemory/TXList2.hpp>
#include <XYO/ManagedMemory/TXRedBlackTree.hpp>

// ---

#include <XYO/ManagedMemory/RegistryData.hpp>
#include <XYO/ManagedMemory/RegistryKey.hpp>
#include <XYO/ManagedMemory/RegistryLevel.hpp>
#include <XYO/ManagedMemory/RegistryProcess.hpp>
#include <XYO/ManagedMemory/RegistryThread.hpp>
#include <XYO/ManagedMemory/TSingletonProcess.hpp>
#include <XYO/ManagedMemory/TSingletonThread.hpp>
#include <XYO/ManagedMemory/TSingleton.hpp>
#include <XYO/ManagedMemory/TMemoryPoolUnifiedProcess.hpp>
#include <XYO/ManagedMemory/TMemoryPoolUnifiedThread.hpp>
#include <XYO/ManagedMemory/TMemoryPoolUnified.hpp>
#include <XYO/ManagedMemory/TMemoryPoolProcess.hpp>
#include <XYO/ManagedMemory/TMemoryPoolThread.hpp>
#include <XYO/ManagedMemory/TMemoryPool.hpp>
#include <XYO/ManagedMemory/TMemoryPoolActiveProcess.hpp>
#include <XYO/ManagedMemory/TMemoryPoolActiveThread.hpp>
#include <XYO/ManagedMemory/TMemoryPoolActive.hpp>
#include <XYO/ManagedMemory/TMemoryProcess.hpp>
#include <XYO/ManagedMemory/TMemoryThread.hpp>
#include <XYO/ManagedMemory/TMemory.hpp>

#endif

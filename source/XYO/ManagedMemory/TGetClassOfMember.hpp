// Managed Memory
// Copyright (c) 2022 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2022 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_TGETCLASSOFMEMBER_HPP
#define XYO_MANAGEDMEMORY_TGETCLASSOFMEMBER_HPP

#ifndef XYO_MANAGEDMEMORY_DEPENDENCY_HPP
#	include <XYO/ManagedMemory/Dependency.hpp>
#endif

namespace XYO::ManagedMemory {

	template <typename T, typename X>
	T TGetClassOfMember(X T::*);

};

#endif

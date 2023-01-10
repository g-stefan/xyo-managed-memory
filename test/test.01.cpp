// Created by Grigore Stefan <g_stefan@yahoo.com>
// Public domain (Unlicense) <http://unlicense.org>
// SPDX-FileCopyrightText: 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: Unlicense

#include <XYO/ManagedMemory.hpp>

using namespace XYO::ManagedMemory;

void test() {
	TPointer<Object> a;
	a.newMemory();

	if (a->hasOneReference()) {
		printf("%p : Has one reference\r\n", a.value());
	};

	TPointer<Object> b(a);

	if (!a->hasOneReference()) {
		printf("%p : Has multiple references\r\n", b.value());
	} else {
		throw std::runtime_error("#1 Single reference");
	};
};

int main(int cmdN, char *cmdS[]) {
	try {

		test();

		return 0;

	} catch (const std::exception &e) {
		printf("* Error: %s\n", e.what());
	} catch (...) {
		printf("* Error: Unknown\n");
	};

	return 1;
};

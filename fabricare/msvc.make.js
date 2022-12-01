// Created by Grigore Stefan <g_stefan@yahoo.com>
// Public domain (Unlicense) <http://unlicense.org>
// SPDX-FileCopyrightText: 2022 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: Unlicense

Shell.mkdirRecursivelyIfNotExists("output");
Shell.mkdirRecursivelyIfNotExists("temp");

// ---

var defines = [
	"_CRT_SECURE_NO_WARNINGS",
	"XYO_OS_WINDOWS",
	"XYO_COMPILER_MSVC",
	"XYO_MULTI_THREAD",
	"XYO_PLATFORM=\"" + Platform.name + "\""
];

if (Platform.machine == "x64") {
	defines[defines.length] = "XYO_APPLICATION_64BIT";
};

if (Platform.machine == "x86") {
	defines[defines.length] = "XYO_APPLICATION_32BIT";
};

compileAndRunTemp({
	project : Project.name + ".config",
	type : "exe",
	defines : defines,
	includePath : [ "source" ],
	cppSource : [ "source/" + Project.sourcePath + ".Config.cpp" ],
	crt : "static"
});

// ---

if (!Fabricare.include("msvc.make." + Project.make)) {
	messageError("Don't know how to make '" + Project.make + "'!");
	exit(1);
};

// Created by Grigore Stefan <g_stefan@yahoo.com>
// Public domain (Unlicense) <http://unlicense.org>
// SPDX-FileCopyrightText: 2022 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: Unlicense

messageAction("make");

Shell.mkdirRecursivelyIfNotExists("output");
Shell.mkdirRecursivelyIfNotExists("temp");

// ---

var defines = [];

if(OS.isWindows()){
	defines = defines.concat([
		"_CRT_SECURE_NO_WARNINGS",
		"XYO_OS_WINDOWS"
	]);

	if(Platform.name.indexOf("msvc")>=0){
		defines = defines.concat([
			"XYO_COMPILER_MSVC"
		]);
	};

	if(Platform.name.indexOf("mingw")>=0){
		defines = defines.concat([
			"XYO_COMPILER_GCC"
		]);
	};
};

if(OS.isLinux()){
	defines = defines.concat([
		"XYO_OS_LINUX",
		"XYO_COMPILER_GCC"
	]);
};

defines = defines.concat([
	"XYO_MULTI_THREAD",
	"XYO_PLATFORM=\"" + Platform.name + "\""
]);

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

if (!Fabricare.include("make." + Project.make)) {
	messageError("Don't know how to make '" + Project.make + "'!");
	exit(1);
};

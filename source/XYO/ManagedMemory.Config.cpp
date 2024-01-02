// Managed Memory Configuration
// Created by Grigore Stefan <g_stefan@yahoo.com>
// Public domain (Unlicense) <http://unlicense.org>
// SPDX-FileCopyrightText: 2016-2024 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: Unlicense

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <iterator>
#include <algorithm>

using namespace std;

void stringReplace(string &data, string toSearch, string replaceWith) {
	size_t pos = data.find(toSearch);
	while (pos != string::npos) {
		data.replace(pos, toSearch.size(), replaceWith);
		pos = data.find(toSearch, pos + replaceWith.size());
	};
};

bool fileReplaceLine(string fileIn_, string fileOut_, map<string, string> &toReplace) {
	fstream fileIn;
	fstream fileOut;
	map<string, string>::iterator index;

	fileIn.open(fileIn_, ios::in);
	fileOut.open(fileOut_, ios::out);

	if (fileIn.is_open()) {
		if (fileOut.is_open()) {

			string line;
			while (getline(fileIn, line)) {
				for (index = toReplace.begin(); index != toReplace.end(); index++) {
					stringReplace(line, index->first, index->second);
				};
				fileOut << line << '\n';
			};

			fileOut.close();
			fileIn.close();
			return true;
		};
		fileIn.close();
	};

	return false;
};

bool fileCompare(string fileName1, string fileName2) {
	std::ifstream file1(fileName1, ifstream::binary | ifstream::ate);
	std::ifstream file2(fileName2, ifstream::binary | ifstream::ate);

	if (file1.fail() || file1.fail()) {
		return false;
	};

	if (file1.tellg() != file2.tellg()) {
		return false;
	};

	file1.seekg(0, ifstream::beg);
	file2.seekg(0, ifstream::beg);

	return equal(istreambuf_iterator<char>(file1.rdbuf()),
	             istreambuf_iterator<char>(),
	             istreambuf_iterator<char>(file2.rdbuf()));
};

// --

string configFileIn = "source/XYO/ManagedMemory/Config.Template.hpp";
string configFileOut = "source/XYO/ManagedMemory/Config.hpp";
string configFileCheck = "temp/Config.hpp";

map<string, string> configMap;

void configEnable(string what) {
	string toFind;
	string toReplace;

	toFind = "// #define ";
	toFind += what;

	toReplace = "#define ";
	toReplace += what;

	configMap.insert(pair<string, string>(toFind, toReplace));
};

void configSetPlatform(string value) {
	string toFind;
	string toReplace;

	toFind = "// #define XYO_PLATFORM \"unknown\"";

	toReplace = "#define XYO_PLATFORM \"";
	toReplace += value;
	toReplace += "\"";

	configMap.insert(pair<string, string>(toFind, toReplace));
};

// --

int main(int cmdN, char *cmdS[]) {

// -- Operating System
#ifdef XYO_OS_WINDOWS
	configEnable("XYO_OS_WINDOWS");
#endif
#ifdef XYO_OS_LINUX
	configEnable("XYO_OS_LINUX");
#endif
#ifdef XYO_OS_MINGW
	configEnable("XYO_OS_MINGW");
#endif

// -- Compiler
#ifdef XYO_COMPILER_MSVC
	configEnable("XYO_COMPILER_MSVC");
#endif
#ifdef XYO_COMPILER_GCC
	configEnable("XYO_COMPILER_GCC");
#endif

// -- Application
#ifdef XYO_APPLICATION_64BIT
	configEnable("XYO_APPLICATION_64BIT");
#endif
#ifdef XYO_APPLICATION_32BIT
	configEnable("XYO_APPLICATION_32BIT");
#endif

// -- Thread support
#ifdef XYO_SINGLE_THREAD
	configEnable("XYO_SINGLE_THREAD");
#endif
#ifdef XYO_MULTI_THREAD
	configEnable("XYO_MULTI_THREAD");
#endif

// -- Compile
#ifdef XYO_COMPILE_DYNAMIC_LIBRARY
	configEnable("XYO_COMPILE_DYNAMIC_LIBRARY");
#endif

// -- Platform
#define XYO_PLATFORM_STR_B(X) #X
#define XYO_PLATFORM_STR_A(X) XYO_PLATFORM_STR_B(X)
#define XYO_PLATFORM_STR XYO_PLATFORM_STR_A(XYO_PLATFORM)

	configSetPlatform(XYO_PLATFORM_STR);

// -- System
#ifdef XYO_MANAGEDMEMORY_64BIT
	configEnable("XYO_MANAGEDMEMORY_64BIT");
#endif

// -- Debug
#ifdef XYO_MEMORY_LEAK_DETECTOR_VLD
	configEnable("XYO_MEMORY_LEAK_DETECTOR_VLD");
#endif
#ifdef XYO_TMEMORYPOOL_SYSTEM
	configEnable("XYO_TMEMORYPOOL_SYSTEM");
#endif
#ifdef XYO_TMEMORYPOOL_ACTIVE_AS_UNIFIED
	configEnable("XYO_TMEMORYPOOL_ACTIVE_AS_UNIFIED");
#endif
#ifdef XYO_TMEMORYPOOL_ACTIVE_LEVEL_IS_SYSTEM
	configEnable("XYO_TMEMORYPOOL_ACTIVE_LEVEL_IS_SYSTEM");
#endif
#ifdef XYO_TMEMORYPOOL_UNIFIED_AS_SYSTEM
	configEnable("XYO_TMEMORYPOOL_UNIFIED_AS_SYSTEM");
#endif
#ifdef XYO_TMEMORYPOOL_CHECK
	configEnable("XYO_TMEMORYPOOL_CHECK");
#endif
#ifdef XYO_TMEMORYPOOL_CHECK_COUNT
	configEnable("XYO_TMEMORYPOOL_CHECK_COUNT");
#endif

	if (!fileReplaceLine(configFileIn, configFileCheck, configMap)) {
		cout << "ManagedMemory - Configuration check error\n";
		return 1;
	};

	if (!fileCompare(configFileCheck, configFileOut)) {
		if (!fileReplaceLine(configFileIn, configFileOut, configMap)) {
			cout << "ManagedMemory - Configuration error\n";
			return 1;
		};
	};

	cout << "ManagedMemory - Configured\n";

	return 0;
};

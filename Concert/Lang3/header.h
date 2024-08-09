
#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <mutex>
#include <stack>
#include <atomic>
#include <iostream>
#include <sstream>
#include <set>
#include <unordered_map>

#include "standardLibrary.h"
#include "HandleStore.h"

class CodeStore;
class Var;
class VarStore;
class WorkspaceStore;
class ObjectStore;

const std::wstring SOFTWARE_NAME = L"Concert";
const std::wstring SOFTWARE_VERSION_STRING = L"0.0.9.6";
const std::wstring SOFTWARE_VERSION_CODE = L"1527";
const std::wstring SOFTWARE_AUTHOR = L"Daniel Puckowski";

extern std::unordered_map<std::wstring, std::wstring> varLockMap;
extern std::unordered_map<std::wstring, std::mutex*> lockMap;
extern std::thread::id mainThreadId;

extern ConcertHandleEnvironment::HandleStore gHandleStore;
extern thread_local CodeStore* codeStore;

extern thread_local VarStore* lastWorkspace;
extern thread_local Var* returnVar;

extern thread_local std::stack<int> conditionalStack;
extern thread_local std::vector<std::wstring> callStack;

extern thread_local std::unordered_map<std::wstring, int> mFunctionMap;
extern thread_local std::unordered_map<std::wstring, LibraryFunction> mLibraryMap;

extern thread_local int currentLine;
extern thread_local int statementCount;
extern thread_local int returnVarInt;
extern thread_local bool createdRetVar;
extern thread_local int tryBlockCount;

extern int threadCount;
extern std::mutex callNameMutex;
extern std::vector<std::wstring> callNameStack;
extern bool debugEnabled;

#include "stringFunctions.h"

#include "HandleStore.h"
#include "CodeStore.h"
#include "WorkspaceStore.h"
#include "Var.h"
#include "VarStore.h"
#include "ObjectStore.h"

#include "sourceFunctions.h"
#include "timer.h"
#include "interpreter.h"

void printSoftwareInformation()
{
	std::wcout << SOFTWARE_NAME << std::endl;
	std::wcout << "Version: " << SOFTWARE_VERSION_STRING << std::endl;
	std::wcout << "Author: " << SOFTWARE_AUTHOR << std::endl;
}

#endif
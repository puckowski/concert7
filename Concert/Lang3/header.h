
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

const std::string SOFTWARE_NAME = "Concert";
const std::string SOFTWARE_VERSION_STRING = "0.0.8.5";
const std::string SOFTWARE_VERSION_CODE = "1220";
const std::string SOFTWARE_AUTHOR = "Daniel Puckowski";

extern std::unordered_map<std::string, std::string> varLockMap;
extern std::unordered_map<std::string, std::mutex*> lockMap;
extern std::thread::id mainThreadId;

extern ConcertHandleEnvironment::HandleStore gHandleStore;
extern thread_local CodeStore* codeStore;

extern thread_local VarStore* lastWorkspace;
extern thread_local Var* returnVar;

extern thread_local std::stack<int> conditionalStack;
extern thread_local std::vector<std::string> callStack;

extern thread_local std::unordered_map<std::string, int> mFunctionMap;
extern thread_local std::unordered_map<std::string, LibraryFunction> mLibraryMap;

extern thread_local int currentLine;
extern thread_local int statementCount;
extern thread_local int returnVarInt;
extern thread_local bool createdRetVar;

extern std::mutex callNameMutex;
extern std::vector<std::string> callNameStack;
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
	std::cout << SOFTWARE_NAME << std::endl;
	std::cout << "Version: " << SOFTWARE_VERSION_STRING << std::endl;
	std::cout << "Author: " << SOFTWARE_AUTHOR << std::endl;
}

#endif
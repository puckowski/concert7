#ifndef MAIN_CPP
#define MAIN_CPP

#include "header.h"
#include <Windows.h>

std::unordered_map<std::wstring, std::wstring> varLockMap;
std::unordered_map<std::wstring, std::mutex*> lockMap;
std::thread::id mainThreadId;

ConcertHandleEnvironment::HandleStore gHandleStore;
thread_local CodeStore* codeStore;
thread_local WorkspaceStore* gWorkspaceStore;

thread_local VarStore* lastWorkspace;
thread_local Var* returnVar;

thread_local std::vector<std::wstring> workspaceStack;
thread_local std::stack<int> conditionalStack;
thread_local std::vector<std::wstring> callStack;

thread_local std::unordered_map<std::wstring, int> mFunctionMap;
thread_local std::unordered_map<std::wstring, LibraryFunction> mLibraryMap;

thread_local int currentLine;
thread_local int statementCount;
thread_local int returnVarInt;
thread_local bool createdRetVar;
thread_local int tryBlockCount;

thread_local bool createStruct;
thread_local std::unordered_map<std::wstring, int> mStructMap;

std::mutex callNameMutex;
std::vector<std::wstring> callNameStack;
bool debugEnabled;

int main(int argc, char *argv[])
{
	SetConsoleOutputCP(CP_UTF8);

	//argc = 2;
	//debugEnabled = 1;

	if (argc < 2) {
		printSoftwareInformation();

		std::cout << "Enter filename to execute." << std::endl;

		return 0;
	}

	if (argc >= 3)
	{
		debugEnabled = atoi(argv[2]);
		// std::cout << "Debug state: " << debugEnabled << std::endl;
	}

	mainThreadId = std::this_thread::get_id();

	codeStore = new CodeStore();

	gWorkspaceStore = new WorkspaceStore();
	gWorkspaceStore->addGlobalStore(new VarStore());

	if (argc > 3)
	{
		Var* argvVar = new Var(L"argv", TYPE_STRING, (argc - 3));
		std::wstring* pstr = static_cast<std::wstring*>(argvVar->data);
	
		int index = 0;
		for (int i = 3; i < argc; ++i)
		{
			pstr[index] = std::wstring(utf8_to_wstring(argv[i]));
			index++;
		}

		gWorkspaceStore->getStore()->addVar(argvVar);

		Var* argcVar = new Var((argc - 3));
		argcVar->name = L"argc";

		gWorkspaceStore->getStore()->addVar(argcVar);
	}

	//auto t1 = getTime();
	readStatementsFromFile(utf8_to_wstring(argv[1]));
	// auto t2 = getTime();
	 //printTimeDifferenceAll(t1, t2);

	currentLine = 0;

	if (debugEnabled == true)
	{
		callNameMutex.lock();
		std::wostringstream ss;
		ss << std::this_thread::get_id();
		std::wstring idstr = ss.str();
		callNameStack.push_back(idstr + L"_main");
		callNameMutex.unlock();

		auto t1 = getTime();
		exec(currentLine);
		auto t2 = getTime();
		printTimeDifferenceAll(t1, t2);
	}
	else
	{
		exec(currentLine);
	}

	delete gWorkspaceStore;

	delete stringLibraryFunctions;
	delete mathLibraryFunctions;
	delete fileLibraryFunctions;

	delete codeStore;

	for (auto mutex : lockMap)
	{
		delete mutex.second;
	}

	gHandleStore.clearStore();

	delete returnVar;

	//std::cin.get();
}
#endif
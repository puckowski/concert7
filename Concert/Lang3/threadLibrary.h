
#ifndef THREAD_LIBRARY_H
#define THREAD_LIBRARY_H

#include <vector>
#include <string>
#include <chrono>

#include "header.h"
#include "Var.h"
#include "variableFunctions.h"

void libraryThreadGetId(std::vector<std::wstring>& arguments, const int& argumentsSize)
{
	Var* returnVar = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);
	std::wstring* returnData = static_cast<std::wstring*>(returnVar->data);

	std::wostringstream ss;
	ss << std::this_thread::get_id();
	std::wstring idstr = ss.str();

	returnData[returnVarInt] = idstr;
}

void libraryThreadHardwareConcurrency(std::vector<std::wstring>& arguments, const int& argumentsSize)
{
	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

	int* returnData = static_cast<int*>(v->data);

	returnData[returnVarInt] = std::thread::hardware_concurrency();
}

void libraryThreadSleep(std::vector<std::wstring>& arguments, const int& argumentsSize)
{
	int r1;
	bool createdInt;
	Var* intVar = getVar(arguments[2], r1, createdInt);

	switch (intVar->type)
	{
	case TYPE_INT:
	{
		int* pstr = static_cast<int*>(intVar->data);

		std::this_thread::sleep_for(std::chrono::milliseconds(pstr[r1]));

		break;
	}
	case TYPE_LONG:
	{
		long long int* pstr = static_cast<long long int*>(intVar->data);

		std::this_thread::sleep_for(std::chrono::milliseconds(pstr[r1]));

		break;
	}
	}

	if (createdInt) {
		delete intVar;
		intVar = nullptr;
	}
}

#endif

#ifndef THREAD_LIBRARY_H
#define THREAD_LIBRARY_H

#include <vector>
#include <string>

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

#endif
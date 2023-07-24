
#ifndef THREAD_LIBRARY_H
#define THREAD_LIBRARY_H

#include <vector>
#include <string>

#include "header.h"
#include "Var.h"
#include "variableFunctions.h"

void libraryThreadGetId(std::vector<std::string>& arguments, const int& argumentsSize)
{
	Var* returnVar = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);
	std::string* returnData = static_cast<std::string*>(returnVar->data);

	std::ostringstream ss;
	ss << std::this_thread::get_id();
	std::string idstr = ss.str();

	returnData[returnVarInt] = idstr;
}

#endif
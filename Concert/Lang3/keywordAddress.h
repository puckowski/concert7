
#ifndef KEYWORD_ADDRESS_H
#define KEYWORD_ADDRESS_H

#include <string>
#include <vector>

#include "sourceFunctions.h"

void executeKeywordAddress(std::vector<std::wstring>& tokens)
{
	int index2;
	bool createdVar2 = false;

	Var* nameVar = getVar(tokens[1], index2, createdVar2);
	
	int index3;
	bool createdVar3 = false;

	Var* retVar = getVar(tokens[2], index3, createdVar3);
	int* retData = static_cast<int*>(retVar->data);
	retData[0] = reinterpret_cast<std::uintptr_t>(nameVar);

	if (createdVar2) {
		delete nameVar;
		nameVar = nullptr;
	}
}

#endif

#ifndef KEYWORD_RETURN_H
#define KEYWORD_RETURN_H

#include <vector>
#include <string>

#include "sourceFunctions.h"
#include "variableFunctions.h"
#include "operatorFunctions.h"

void executeKeywordReturn(const int &tokensSize, std::vector<std::wstring> &tokens)
{
	if (tokensSize == 2)
	{
		if (returnVar != nullptr)
		{
			delete returnVar;
		}

		Var* v = getVar(tokens[1], returnVarInt, createdRetVar);
		returnVar = new Var(v->name, v->type, v->size);
		execAssignOperator(returnVar, v);
	}
}

#endif

#ifndef KEYWORD_INSTANCEOF_H
#define KEYWORD_INSTANCEOF_H

#include <vector>
#include <string>

#include "Var.h"
#include "variableFunctions.h"
#include "mutexFunctions.h"

void executeKeywordInstanceof(std::vector<std::wstring> &tokens)
{
	std::mutex* mtx = getMutex(tokens[1]);

	if (mtx == nullptr)
	{
		int r1, r2;
		Var* lhsVar = getVar(tokens[1], r1);

		Var* rhsVar = getVar(tokens[2], r2);
		std::wstring* rhsData = static_cast<std::wstring*>(rhsVar->data);
		
		int type = lhsVar->type;

		switch (type)
		{
		case 0:
		{
			rhsData[r2] = L"int";

			break;
		}
		case 1:
		{
			rhsData[r2] = L"double";

			break;
		}
		case 2:
		{
			rhsData[r2] = L"string";

			break;
		}
		case 3:
		{
			rhsData[r2] = L"long";

			break;
		}
		case 41:
		{
			rhsData[r2] = L"object";

			break;
		}
		}
	}
	else
	{
		int r2;
		Var* rhsVar = getVar(tokens[2], r2);
		std::wstring* rhsData = static_cast<std::wstring*>(rhsVar->data);
		rhsData[r2] = L"mutex";
	}
}

#endif
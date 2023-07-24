
#ifndef KEYWORD_INSTANCEOF_H
#define KEYWORD_INSTANCEOF_H

#include <vector>
#include <string>

#include "Var.h"
#include "variableFunctions.h"
#include "mutexFunctions.h"

void executeKeywordInstanceof(std::vector<std::string> &tokens)
{
	std::mutex* mtx = getMutex(tokens[1]);

	if (mtx == nullptr)
	{
		int r1, r2;
		Var* lhsVar = getVar(tokens[1], r1);

		Var* rhsVar = getVar(tokens[2], r2);
		std::string* rhsData = static_cast<std::string*>(rhsVar->data);
		
		int type = lhsVar->type;

		switch (type)
		{
		case 0:
		{
			rhsData[r2] = "int";

			break;
		}
		case 1:
		{
			rhsData[r2] = "double";

			break;
		}
		case 2:
		{
			rhsData[r2] = "string";

			break;
		}
		case 3:
		{
			rhsData[r2] = "long";

			break;
		}
		case 41:
		{
			rhsData[r2] = "object";

			break;
		}
		}
	}
	else
	{
		int r2;
		Var* rhsVar = getVar(tokens[2], r2);
		std::string* rhsData = static_cast<std::string*>(rhsVar->data);
		rhsData[r2] = "mutex";
	}
}

#endif
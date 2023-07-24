
#ifndef KEYWORD_SIZEOF_H
#define KEYWORD_SIZEOF_H

#include <vector>
#include <string>

#include "Var.h"
#include "variableFunctions.h"

void executeKeywordSizeof(const int& tokensSize, std::vector<std::string> &tokens)
{
	if (tokensSize == 3)
	{
		int r1, r2;
		Var* lhsVar = getVar(tokens[1], r1);

		Var* rhsVar = getVar(tokens[2], r2);
		int* rhsData = static_cast<int*>(rhsVar->data);
		rhsData[r2] = lhsVar->size;
	}
	else
	{
		std::string byteFlag = tokens[3];
		int byteFlagInt = std::stod(byteFlag);

		if (byteFlagInt == 1)
		{
			int r1, r2;
			Var* lhsVar = getVar(tokens[1], r1);

			Var* rhsVar = getVar(tokens[2], r2);
			int* rhsData = static_cast<int*>(rhsVar->data);
			rhsData[r2] = sizeof(lhsVar->data) * lhsVar->size;
		}
		else
		{
			int r1, r2;
			Var* lhsVar = getVar(tokens[1], r1);

			Var* rhsVar = getVar(tokens[2], r2);
			int* rhsData = static_cast<int*>(rhsVar->data);
			rhsData[r2] = lhsVar->size;
		}
	}
}

#endif

#ifndef KEYWORD_READ_H
#define KEYWORD_READ_H

#include <vector>
#include <string>
#include <iostream>

#include "Var.h"
#include "variableFunctions.h"

void executeKeywordRead(std::vector<std::wstring> &tokens)
{
	std::wstring line;
	std::getline(std::wcin, line);

	std::wstring token;
	std::wstringstream ss(line);

	int i = 1;

	while (ss >> token) 
	{
		int r1;
		Var* lhsVar = getVar(tokens[i], r1);
		std::wstring* pstr = static_cast<std::wstring*>(lhsVar->data);
		pstr[r1] = token;

		i++;
	}
}

#endif
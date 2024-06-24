
#ifndef KEYWORD_READLN_H
#define KEYWORD_READLN_H

#include <vector>
#include <string>
#include <iostream>

#include "Var.h"
#include "variableFunctions.h"

void executeKeywordReadln(std::vector<std::wstring> &tokens)
{
	int r1;
	Var* lhsVar = getVar(tokens[1], r1);

	std::wstring* pstr = static_cast<std::wstring*>(lhsVar->data);

	std::getline(std::wcin, pstr[r1]);
}

#endif
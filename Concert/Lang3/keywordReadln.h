
#ifndef KEYWORD_READLN_H
#define KEYWORD_READLN_H

#include <vector>
#include <string>
#include <iostream>

#include "Var.h"
#include "variableFunctions.h"

void executeKeywordReadln(std::vector<std::string> &tokens)
{
	int r1;
	Var* lhsVar = getVar(tokens[1], r1);

	std::string* pstr = static_cast<std::string*>(lhsVar->data);

	std::getline(std::cin, pstr[r1]);
}

#endif
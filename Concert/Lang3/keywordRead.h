
#ifndef KEYWORD_READ_H
#define KEYWORD_READ_H

#include <vector>
#include <string>
#include <iostream>

#include "Var.h"
#include "variableFunctions.h"

void executeKeywordRead(std::vector<std::string> &tokens)
{
	std::string line;
	std::getline(std::cin, line);

	std::string token;
	std::stringstream ss(line);

	int i = 1;

	while (ss >> token) 
	{
		int r1;
		Var* lhsVar = getVar(tokens[i], r1);
		std::string* pstr = static_cast<std::string*>(lhsVar->data);
		pstr[r1] = token;

		i++;
	}
}

#endif
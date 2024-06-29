
#ifndef KEYWORD_READ_H
#define KEYWORD_READ_H

#include <vector>
#include <string>
#include <iostream>

#include "Var.h"
#include "variableFunctions.h"

void executeKeywordRead(std::vector<std::wstring> &tokens)
{
	boost::locale::generator gen;
	std::locale loc = gen("en_US.UTF-8");
	std::locale::global(loc);

	std::string utf8_input;
	std::getline(std::cin, utf8_input);

	std::wstring utf16_input = boost::locale::conv::utf_to_utf<wchar_t>(utf8_input);

	int r1;
	Var* lhsVar = getVar(tokens[1], r1);

	std::wstring token;
	std::wstringstream ss(utf16_input);

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
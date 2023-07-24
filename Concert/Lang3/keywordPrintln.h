
#ifndef KEYWORD_PRINTLN_H
#define KEYWORD_PRINTLN_H

#include <vector>
#include <string>
#include <iomanip>
#include <iostream>

#include "Var.h"
#include "variableFunctions.h"
#include "printFunctions.h"

void executeKeywordPrintln(const int &tokensSize, std::vector<std::string> &tokens)
{
	for (int i = 1; i < tokens.size(); ++i)
	{
		bool created = false;
		int r1;
		Var* v = getVar(tokens[i], r1, created);

		ReservedWord lhsType = v->type;

		switch (lhsType)
		{
		case TYPE_INT:
		{
			int* pstr = static_cast<int*>(v->data);

			std::cout << pstr[r1];

			break;
		}
		case TYPE_LONG:
		{
			long long int* pstr = static_cast<long long int*>(v->data);

			std::cout << pstr[r1];

			break;
		}
		case TYPE_DOUBLE:
		{
			double* pstr = static_cast<double*>(v->data);

			std::cout << std::fixed << pstr[r1];

			break;
		}
		case TYPE_STRING:
		{
			std::string* pstr = static_cast<std::string*>(v->data);

			std::cout << pstr[r1];

			break;
		}
		}

		if (created == true)
			delete v;
	}

	std::cout << std::endl;
}

#endif
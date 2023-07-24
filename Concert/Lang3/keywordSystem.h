
#ifndef KEYWORD_SYSTEM_H
#define KEYWORD_SYSTEM_H

#include <string>
#include <vector>

#include "sourceFunctions.h"

void executeKeywordSystem(const int &tokensSize, std::vector<std::string> &tokens)
{
	for (int i = 1; i < tokens.size(); ++i)
	{
		bool created = false;
		int r1;
		Var* v = getVar(tokens[i], r1, created);

		std::string* pstr = static_cast<std::string*>(v->data);
		system(pstr[r1].c_str());

		if (created)
		{
			delete v;
		}
	}
}

#endif
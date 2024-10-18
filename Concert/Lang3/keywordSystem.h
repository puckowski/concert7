
#ifndef KEYWORD_SYSTEM_H
#define KEYWORD_SYSTEM_H

#include <string>
#include <vector>

#include "sourceFunctions.h"

void executeKeywordSystem(const int &tokensSize, std::vector<std::wstring> &tokens)
{
	for (int i = 1; i < tokens.size(); ++i)
	{
		bool created = false;
		int r1;
		Var* v = getVar(tokens[i], r1, created);

		std::wstring* pstr = static_cast<std::wstring*>(v->data);
		system(wstring_to_utf8(pstr[r1]).c_str());

		if (created)
		{
			delete v;
			v = nullptr;
		}
	}
}

#endif
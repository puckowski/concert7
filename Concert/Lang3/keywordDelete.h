
#ifndef KEYWORD_DELETE_H
#define KEYWORD_DELETE_H

#include <string>
#include <vector>

#include "sourceFunctions.h"

void executeKeywordDelete(std::vector<std::wstring> &tokens)
{
	bool created = false;
	int r1;
	Var* varName = getVar(tokens[1], r1, created);

	std::wstring* pstr = static_cast<std::wstring*>(varName->data);

	VarStore* vs = gWorkspaceStore->getStore();
	std::wstring name = pstr[r1];
	vs->removeVar(name);

	if (created)
	{
		delete varName;
		varName = nullptr;
	}
}

#endif
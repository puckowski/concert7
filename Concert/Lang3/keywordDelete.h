
#ifndef KEYWORD_DELETE_H
#define KEYWORD_DELETE_H

#include <string>
#include <vector>

#include "sourceFunctions.h"

void executeKeywordDelete(std::vector<std::string> &tokens)
{
	bool created = false;
	int r1;
	Var* varName = getVar(tokens[1], r1, created);

	std::string* pstr = static_cast<std::string*>(varName->data);

	gWorkspaceStore->getStore()->removeVar(pstr[r1]);

	if (created)
	{
		delete varName;
	}
}

#endif
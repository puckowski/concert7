
#ifndef KEYWORD_ALIAS_H
#define KEYWORD_ALIAS_H

#include <string>
#include <vector>

#include "sourceFunctions.h"

void executeKeywordAlias(std::vector<std::string>& tokens)
{
	const std::string toAliasName = tokens[1];

	int index2;
	bool createdVar2 = false;

	Var* nameVar = getVar(tokens[2], index2, createdVar2);
	std::string* objectName = static_cast<std::string*>(nameVar->data);
	const std::string aliasName = objectName[index2];

	VarStore* vs = gWorkspaceStore->getStore();
	vs->addVarAlias(toAliasName, aliasName);

	if (createdVar2)
		delete nameVar;
}

#endif
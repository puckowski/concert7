
#ifndef KEYWORD_KEYS_H
#define KEYWORD_KEYS_H

#include <string>
#include <vector>

#include "Var.h"
#include "variableFunctions.h"

void executeKeywordKeys(const int& tokensSize, std::vector<std::wstring>& tokens)
{
	int index;
	bool createdVar = false;

	// Name of var to create, may be a "" string
	Var* nameVar = getVar(tokens[2], index, createdVar);
	std::wstring* objectName = static_cast<std::wstring*>(nameVar->data);

	int objIndex;
	Var* objVar = getVar(tokens[1], objIndex);
	ObjectStore** objStore = static_cast<ObjectStore**>(objVar->data);
	ObjectStore* obj = objStore[objIndex];

	std::vector<std::wstring> keys = obj->getKeys();

	gWorkspaceStore->getStore()->addVar(new Var(objectName[index], TYPE_STRING, keys.size()));
	
	Var* createdKeyVar = gWorkspaceStore->getStore()->getVar(objectName[index], objIndex);
	std::wstring* keysArr = static_cast<std::wstring*>(createdKeyVar->data);
	// ignore objIndex here
	for (int i = 0; i < keys.size(); ++i) 
	{
		keysArr[i] = keys.at(i);
	}

	if (createdVar == true)
	{
		delete nameVar;
		nameVar = nullptr;
	}
}

#endif
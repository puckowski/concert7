
#ifndef OBJECT_DECLARATION_H
#define OBJECT_DECLARATION_H

#include <vector>
#include <string>

#include "Var.h"
#include "declaration.h"
#include "variableFunctions.h"

const int OBJECT_NAME_INDEX = 1;
const int OBJECT_SIZE_INDEX = 2;

const int DECLARE_OBJECT_VARIABLE = 2;
const int DECLARE_OBJECT_ARRAY    = 3;

const int OBJECT_VARIABLE_SIZE = 1;

void declareObjectVariable(const int& tokensSize, std::vector<std::string>& tokens)
{
	if (tokensSize == DECLARE_OBJECT_VARIABLE)
	{
		std::string name = tokens[OBJECT_NAME_INDEX];
		std::string::size_type accessorIndex = name.find_last_of(".");

		if (accessorIndex == std::string::npos)
		{
			gWorkspaceStore->getStore()->addVar(new Var(tokens[OBJECT_NAME_INDEX], TYPE_OBJECT, OBJECT_VARIABLE_SIZE));
		}
		else
		{
			std::string storeName = name.substr(0, accessorIndex);
			std::string varName = name.substr(accessorIndex + 1, name.length());
			std::string::size_type indexQuote = varName.find("'");

			if (indexQuote != std::string::npos)
			{
				varName = varName.substr(indexQuote + 1, varName.find("'", indexQuote + 1) - 1);
				int r1;
				Var* v = getVar(varName, r1);
				std::string* pstr = static_cast<std::string*>(v->data);
				varName = pstr[r1];
			}

			int intValue = 0;

			ObjectStore** var = static_cast<ObjectStore**>(gWorkspaceStore->getStore()->getVar(storeName, intValue)->data);
			ObjectStore* obj = var[intValue];
			obj->addVar(varName, TYPE_OBJECT);
		}
	}
	else if (tokensSize == DECLARE_OBJECT_ARRAY)
	{
		// Only object x 10 for now...

		int index;
		bool createdVar = false;

		Var* var = getVar(tokens[OBJECT_SIZE_INDEX], index, createdVar);
		int* sizeArray = static_cast<int*>(var->data);

		std::string name = tokens[OBJECT_NAME_INDEX];
		std::string::size_type accessorIndex = name.find_last_of(".");

		if (accessorIndex == std::string::npos)
		{
			gWorkspaceStore->getStore()->addVar(new Var(tokens[OBJECT_NAME_INDEX], TYPE_OBJECT, sizeArray[index]));
		}
		else
		{
			std::string storeName = name.substr(0, accessorIndex);
			std::string varName = name.substr(accessorIndex + 1, name.length());
			std::string::size_type indexQuote = varName.find("'");

			if (indexQuote != std::string::npos)
			{
				varName = varName.substr(indexQuote + 1, varName.find("'", indexQuote + 1) - 1);
				int r1;
				Var* v = getVar(varName, r1);
				std::string* pstr = static_cast<std::string*>(v->data);
				varName = pstr[r1];
			}

			int intValue = 0;

			ObjectStore** var = static_cast<ObjectStore**>(gWorkspaceStore->getStore()->getVar(storeName, intValue)->data);
			ObjectStore* obj = var[intValue];
			obj->addVar(varName, TYPE_OBJECT, sizeArray[index]);
		}

		if (createdVar == true)
		{
			delete var;
		}
	}
}

#endif
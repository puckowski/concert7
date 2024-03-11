
#ifndef LONG_DECLARATION_H
#define LONG_DECLARATION_H

#include <vector>
#include <string>

#include "Var.h"
#include "declaration.h"
#include "variableFunctions.h"

const int LONG_NAME_INDEX = 1;
const int LONG_SIZE_INDEX = 2;

const int DECLARE_LONG_VARIABLE = 2;
const int DECLARE_LONG_ARRAY = 3;

const int LONG_VARIABLE_SIZE = 1;

void declareLongVariable(const int &tokensSize, std::vector<std::string> &tokens)
{
	if (tokensSize == DECLARE_LONG_VARIABLE)
	{
		std::string name = tokens[1];
		std::string::size_type accessorIndex = name.find_last_of(".");

		if (accessorIndex == std::string::npos)
		{
			gWorkspaceStore->getStore()->addVar(new Var(tokens[LONG_NAME_INDEX], TYPE_LONG, LONG_VARIABLE_SIZE));
		}
		else
		{
			std::string storeName = name.substr(0, accessorIndex);
			std::string varName = name.substr(accessorIndex + 1, name.length());
			int intValue = 0;

			ObjectStore** var = static_cast<ObjectStore**>(gWorkspaceStore->getStore()->getVar(storeName, intValue)->data);
			ObjectStore* obj = var[intValue];
			obj->addVar(varName, TYPE_LONG);
		}
	}
	else if (tokensSize == DECLARE_LONG_ARRAY)
	{
		std::string name = tokens[1];
		std::string::size_type accessorIndex = name.find_last_of(".");

		int index;
		bool createdVar = false;

		Var* var = getVar(tokens[INT_SIZE_INDEX], index, createdVar);
		int* sizeArray = static_cast<int*>(var->data);

		if (accessorIndex == std::string::npos)
		{
			gWorkspaceStore->getStore()->addVar(new Var(tokens[LONG_NAME_INDEX], TYPE_LONG, sizeArray[index]));
		}
		else
		{
			std::string storeName = name.substr(0, accessorIndex);
			std::string varName = name.substr(accessorIndex + 1, name.length());
			int intValue = 0;

			ObjectStore** var = static_cast<ObjectStore**>(gWorkspaceStore->getStore()->getVar(storeName, intValue)->data);
			ObjectStore* obj = var[intValue];
			obj->addVar(varName, TYPE_LONG, sizeArray[index]);
		}

		if (createdVar == true)
		{
			delete var;
		}
	}
	else if (tokensSize >= INITIALIZE_TOKEN_COUNT_MINIMUM)
	{
		if (tokens[CHECK_VARIABLE_INITIALIZATION_INDEX] == "=")
		{
			gWorkspaceStore->getStore()->addVar(new Var(tokens[LONG_NAME_INDEX], TYPE_LONG, LONG_VARIABLE_SIZE));

			executeInitialization(INITIALIZE_VARIABLE_START_INDEX, tokens);
		}
		else //if (tokens[CHECK_ARRAY_INITIALIZATION_INDEX] == "=")
		{
			int index;
			bool createdVar = false;

			Var* var = getVar(tokens[LONG_SIZE_INDEX], index, createdVar);
			int* sizeArray = static_cast<int*>(var->data);

			gWorkspaceStore->getStore()->addVar(new Var(tokens[LONG_NAME_INDEX], TYPE_LONG, sizeArray[index]));

			executeInitialization(INITIALIZE_ARRAY_START_INDEX, sizeArray[index], tokens);

			if (createdVar == true)
			{
				delete var;
			}
		}
	}
}

#endif
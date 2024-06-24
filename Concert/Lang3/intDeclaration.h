
#ifndef INT_DECLARATION_H
#define INT_DECLARATION_H

#include <vector>
#include <string>

#include "Var.h"
#include "declaration.h"
#include "variableFunctions.h"

const int INT_NAME_INDEX = 1;
const int INT_SIZE_INDEX = 2;

const int DECLARE_INT_VARIABLE = 2;
const int DECLARE_INT_ARRAY    = 3;

const int INT_VARIABLE_SIZE    = 1;

void declareIntVariable(const int &tokensSize, std::vector<std::wstring> &tokens)
{
	if (tokensSize == DECLARE_INT_VARIABLE)
	{
		std::wstring name = tokens[1];
		std::wstring::size_type accessorIndex = name.find_last_of(L".");

		if (accessorIndex == std::wstring::npos)
		{
			gWorkspaceStore->getStore()->addVar(new Var(tokens[INT_NAME_INDEX], TYPE_INT, INT_VARIABLE_SIZE));
		} 
		else 
		{
			std::wstring storeName = name.substr(0, accessorIndex);
			std::wstring varName = name.substr(accessorIndex + 1, name.length());
			int intValue = 0;

			ObjectStore** var = static_cast<ObjectStore**>(gWorkspaceStore->getStore()->getVar(storeName, intValue)->data);
			ObjectStore* obj = var[intValue];
			obj->addVar(varName, TYPE_INT);
		}
	}
	else if(tokensSize == DECLARE_INT_ARRAY)
	{
		std::wstring name = tokens[1];
		std::wstring::size_type accessorIndex = name.find_last_of(L".");

		int index;
		bool createdVar = false;

		Var* var = getVar(tokens[INT_SIZE_INDEX], index, createdVar);
		int* sizeArray = static_cast<int*>(var->data);

		if (accessorIndex == std::wstring::npos)
		{
			gWorkspaceStore->getStore()->addVar(new Var(tokens[INT_NAME_INDEX], TYPE_INT, sizeArray[index]));
		}
		else
		{
			std::wstring storeName = name.substr(0, accessorIndex);
			std::wstring varName = name.substr(accessorIndex + 1, name.length());
			int intValue = 0;

			ObjectStore** var = static_cast<ObjectStore**>(gWorkspaceStore->getStore()->getVar(storeName, intValue)->data);
			ObjectStore* obj = var[intValue];
			obj->addVar(varName, TYPE_INT, sizeArray[index]);
		}

		if (createdVar == true)
		{
			delete var;
		}
	}
	else if (tokensSize >= INITIALIZE_TOKEN_COUNT_MINIMUM)
	{
		if (tokens[CHECK_VARIABLE_INITIALIZATION_INDEX] == L"=")
		{
			gWorkspaceStore->getStore()->addVar(new Var(tokens[INT_NAME_INDEX], TYPE_INT, INT_VARIABLE_SIZE));

			executeInitialization(INITIALIZE_VARIABLE_START_INDEX, tokens);
		}
		else //if (tokens[CHECK_ARRAY_INITIALIZATION_INDEX] == L"=")
		{
			int index;
			bool createdVar = false;

			Var* var = getVar(tokens[INT_SIZE_INDEX], index, createdVar);
			int* sizeArray = static_cast<int*>(var->data);

			gWorkspaceStore->getStore()->addVar(new Var(tokens[INT_NAME_INDEX], TYPE_INT, sizeArray[index]));

			executeInitialization(INITIALIZE_ARRAY_START_INDEX, sizeArray[index], tokens);

			if (createdVar == true)
			{
				delete var;
			}
		}
	}
}

#endif
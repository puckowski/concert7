
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

void declareLongVariable(const int &tokensSize, std::vector<std::wstring> &tokens)
{
	if (tokensSize == DECLARE_LONG_VARIABLE)
	{
		std::wstring name = tokens[1];
		std::wstring::size_type accessorIndex = name.find_last_of(L".");

		if (accessorIndex == std::wstring::npos)
		{
			gWorkspaceStore->getStore()->addVar(new Var(tokens[LONG_NAME_INDEX], TYPE_LONG, LONG_VARIABLE_SIZE));
		}
		else
		{
			std::wstring storeName = name.substr(0, accessorIndex);
			std::wstring varName = name.substr(accessorIndex + 1, name.length());
			
			bool createdVar;
			Var* dynamicNameVar = getSingleQuoteVar(varName, createdVar);

			if (dynamicNameVar != nullptr)
			{
				std::wstring* pstr = static_cast<std::wstring*>(dynamicNameVar->data);
				VarStore* gStore = gWorkspaceStore->getStore();

				int r1;
				Var* underlyingValue = gStore->getVar(pstr[0], r1);

				if (underlyingValue != nullptr)
				{
					std::wstring* pstr2 = static_cast<std::wstring*>(underlyingValue->data);
					int intValue = 0;

					ObjectStore** var = static_cast<ObjectStore**>(gStore->getVar(storeName, intValue)->data);
					ObjectStore* obj = var[intValue];
					obj->addVar(pstr2[r1], TYPE_LONG);
				}

				if (createdVar)
				{
					delete dynamicNameVar;
					dynamicNameVar = nullptr;
				}
			}
			else
			{
				int intValue = 0;

				ObjectStore** var = static_cast<ObjectStore**>(gWorkspaceStore->getStore()->getVar(storeName, intValue)->data);
				ObjectStore* obj = var[intValue];
				obj->addVar(varName, TYPE_LONG);
			}
		}
	}
	else if (tokensSize == DECLARE_LONG_ARRAY)
	{
		std::wstring name = tokens[1];
		std::wstring::size_type accessorIndex = name.find_last_of(L".");

		int index;
		bool createdVar = false;

		Var* var = getVar(tokens[INT_SIZE_INDEX], index, createdVar);
		int* sizeArray = static_cast<int*>(var->data);

		if (accessorIndex == std::wstring::npos)
		{
			gWorkspaceStore->getStore()->addVar(new Var(tokens[LONG_NAME_INDEX], TYPE_LONG, sizeArray[index]));
		}
		else
		{
			std::wstring storeName = name.substr(0, accessorIndex);
			std::wstring varName = name.substr(accessorIndex + 1, name.length());
			
			bool createdVar;
			Var* dynamicNameVar = getSingleQuoteVar(varName, createdVar);

			if (dynamicNameVar != nullptr)
			{
				std::wstring* pstr = static_cast<std::wstring*>(dynamicNameVar->data);
				VarStore* gStore = gWorkspaceStore->getStore();

				int r1;
				Var* underlyingValue = gStore->getVar(pstr[0], r1);

				if (underlyingValue != nullptr)
				{
					std::wstring* pstr2 = static_cast<std::wstring*>(underlyingValue->data);
					int intValue = 0;

					ObjectStore** var = static_cast<ObjectStore**>(gStore->getVar(storeName, intValue)->data);
					ObjectStore* obj = var[intValue];
					obj->addVar(pstr2[r1], TYPE_LONG, sizeArray[index]);
				}

				if (createdVar)
				{
					delete dynamicNameVar;
					dynamicNameVar = nullptr;
				}
			}
			else
			{
				int intValue = 0;

				ObjectStore** var = static_cast<ObjectStore**>(gWorkspaceStore->getStore()->getVar(storeName, intValue)->data);
				ObjectStore* obj = var[intValue];
				obj->addVar(varName, TYPE_LONG, sizeArray[index]);
			}
		}

		if (createdVar == true)
		{
			delete var;
			var = nullptr;
		}
	}
	else if (tokensSize >= INITIALIZE_TOKEN_COUNT_MINIMUM)
	{
		if (tokens[CHECK_VARIABLE_INITIALIZATION_INDEX] == L"=")
		{
			gWorkspaceStore->getStore()->addVar(new Var(tokens[LONG_NAME_INDEX], TYPE_LONG, LONG_VARIABLE_SIZE));

			executeInitialization(INITIALIZE_VARIABLE_START_INDEX, tokens);
		}
		else //if (tokens[CHECK_ARRAY_INITIALIZATION_INDEX] == L"=")
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
				var = nullptr;
			}
		}
	}
}

#endif
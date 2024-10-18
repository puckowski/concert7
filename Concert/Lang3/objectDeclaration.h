
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

void declareObjectVariable(const int& tokensSize, std::vector<std::wstring>& tokens)
{
	if (tokensSize == DECLARE_OBJECT_VARIABLE)
	{
		std::wstring name = tokens[OBJECT_NAME_INDEX];
		std::wstring::size_type accessorIndex = name.find_last_of(L".");

		if (accessorIndex == std::wstring::npos)
		{
			gWorkspaceStore->getStore()->addVar(new Var(tokens[OBJECT_NAME_INDEX], TYPE_OBJECT, OBJECT_VARIABLE_SIZE));
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
					obj->addVar(pstr2[r1], TYPE_OBJECT);
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
				obj->addVar(varName, TYPE_OBJECT);
			}
		}
	}
	else if (tokensSize == DECLARE_OBJECT_ARRAY)
	{
		// Only object x 10 for now...

		int index;
		bool createdVar = false;

		Var* var = getVar(tokens[OBJECT_SIZE_INDEX], index, createdVar);
		int* sizeArray = static_cast<int*>(var->data);

		std::wstring name = tokens[OBJECT_NAME_INDEX];
		std::wstring::size_type accessorIndex = name.find_last_of(L".");

		if (accessorIndex == std::wstring::npos)
		{
			gWorkspaceStore->getStore()->addVar(new Var(tokens[OBJECT_NAME_INDEX], TYPE_OBJECT, sizeArray[index]));
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
					obj->addVar(pstr2[r1], TYPE_OBJECT, sizeArray[index]);
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
				obj->addVar(varName, TYPE_OBJECT, sizeArray[index]);
			}
		}

		if (createdVar == true)
		{
			delete var;
			var = nullptr;
		}
	}
}

#endif
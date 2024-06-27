
#ifndef VARIABLE_FUNCTIONS_H
#define VARIABLE_FUNCTIONS_H

#include <vector>
#include <string>

class Var;
class VarStore;
class WorkspaceStore;

#include "Var.h"
#include "VarStore.h"
#include "CodeStore.h"
#include "sourceFunctions.h"
#include "WorkspaceStore.h"

const int INITIALIZE_TOKEN_COUNT_MINIMUM = 4;

const int CHECK_VARIABLE_INITIALIZATION_INDEX = 2;
const int CHECK_ARRAY_INITIALIZATION_INDEX    = 3;

const int INITIALIZE_VARIABLE_START_INDEX = 3;
const int INITIALIZE_ARRAY_START_INDEX    = 4;

Var* getVarFromLastWorkspace(const std::wstring &name, int &val, bool &created)
{
	created = false;

	VarStore* vs = lastWorkspace;
	Var* var = vs->getVar(name, val);

	if (var == nullptr)
	{
		if (name.find(L"\"") != std::wstring::npos)
		{
			std::wstring temp = name.substr(1);
			temp = temp.substr(0, temp.length() - 1);

			var = new Var(temp);

			created = true;
		}
		else if (name.find(L".") != std::wstring::npos)
		{
			var = new Var(std::stod(name));

			created = true;
		}
		else
		{
			long long int data = std::stoll(name);
			int dataInt = std::stoi(name);

			if (data == dataInt)
			{
				var = new Var(dataInt);
			}
			else
			{
				var = new Var(data);
			}

			created = true;
		}
	}

	return var;
}

Var* getVarFromLastWorkspace(const std::wstring &name, const ReservedWord lhsVarType, int &val, bool &created)
{
	created = false;

	VarStore* vs = lastWorkspace; 
	Var* var = vs->getVar(name, val);

	if (var == nullptr)
	{
		switch (lhsVarType)
		{
		case TYPE_INT:
		{
			var = new Var(std::stoi(name));
			created = true;

			break;
		}
		case TYPE_LONG:
		{
			var = new Var(std::stoll(name));
			created = true;

			break;
		}
		case TYPE_DOUBLE:
		{
			var = new Var(std::stod(name));
			created = true;

			break;
		}
		case TYPE_STRING:
		{
			std::wstring temp = name.substr(1);
			temp = temp.substr(0, temp.length() - 1);

			var = new Var(temp);
			created = true;

			break;
		}
		}
	}

	return var;
}

Var* getVar(const std::wstring &name, ReservedWord &lhsVarType, int &val, bool &created)
{
	created = false;

	VarStore* vs = gWorkspaceStore->getStore();
	Var* var = vs->getVar(name, val);

	if (var == nullptr)
	{
		switch (lhsVarType)
		{
		case TYPE_INT:
		{
			var = new Var(std::stoi(name));
			created = true;

			break;
		}
		case TYPE_LONG:
		{
			var = new Var(std::stoll(name));
			created = true;

			break;
		}
		case TYPE_DOUBLE:
		{
			var = new Var(std::stod(name));
			created = true;

			break;
		}
		case TYPE_STRING:
		{
			std::wstring temp = name;
			
			if (name.find(L"\"") != std::wstring::npos)
			{
				temp = name.substr(1);
				temp = temp.substr(0, temp.length() - 1);
			}

			var = new Var(temp);
			created = true;

			break;
		}
		}
	}

	return var;
}

Var* getVar(const std::wstring &name, int &val, bool &created)
{
	created = false;

	VarStore* vs = gWorkspaceStore->getStore();
	Var* var = vs->getVar(name, val);

	if (var == nullptr)
	{
		if (name.find(L"\"") != std::wstring::npos)
		{
			std::wstring temp = name.substr(1);
			temp = temp.substr(0, temp.length() - 1);

			var = new Var(temp);
			created = true;
		}
		else if (name.find(L".") != std::wstring::npos)
		{
			var = new Var(std::stod(name));
			created = true;
		}
		else
		{
			var = new Var(std::stoi(name));
			created = true;
		}
	}

	return var;
}

Var* getSingleQuoteVar(const std::wstring& name, bool& created)
{
	created = false;

	Var* var = nullptr;

	if (name.find(L"'") != std::wstring::npos)
	{
		std::wstring temp = name.substr(1);
		temp = temp.substr(0, temp.length() - 1);

		var = new Var(temp);
		created = true;
	}

	return var;
}

Var* getVar(const std::wstring &name, int &val)
{
	VarStore* vs = gWorkspaceStore->getStore();
	Var* var = vs->getVar(name, val);

	return var;
}

#endif
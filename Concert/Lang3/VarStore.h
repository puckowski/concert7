
#ifndef VAR_STORE_H
#define VAR_STORE_H

#include <string>
#include <stack>
#include <iostream>
#include <unordered_map>
#include <cctype>
#include <sstream>
#include <algorithm>
#include <set>

class WorkspaceStore;

extern thread_local WorkspaceStore* gWorkspaceStore;

#include "Var.h"

class VarStore
{
	std::unordered_map<std::wstring, Var*> mVars;

public:
	~VarStore();
	void print();

	void addVar(const std::wstring &name, const ReservedWord &type);
	void addVar(Var* var);

	int removeVar(const std::wstring &name);

	void addVar(const std::wstring name, const ReservedWord type, const int size);
	void addVarAlias(const std::wstring toAliasName, const std::wstring aliasName);
	void addVarAliasWithPointer(Var* toAliasVar, int& varIndex, const std::wstring aliasName);

	Var* addVarWithReference(const std::wstring name, const ReservedWord type, const int size);

	Var* getVar(const std::wstring &name, int &val);

	void reassignVar(Var* toReassign, Var* newVar);// , std::set<long long>& deletedDataSet);

	//
	Var* getSimpleWithIndex(const std::wstring& var, int& index);
	std::wstring getForBracket(const std::wstring& var);
	Var* getVar2(const std::wstring& name, int& index);


	//
	std::wstring getForBracket(const std::wstring& var, bool getReplacement);
	void reassignAllVar(Var* toReassign, Var* newVar);
};

#endif
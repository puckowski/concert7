
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
	std::unordered_map<std::string, Var*> mVars;

public:
	~VarStore();
	void print();

	void addVar(const std::string &name, const ReservedWord &type);

	void addVar(Var* var);

	int removeVar(const std::string &name);

	void addVar(const std::string name, const ReservedWord type, const int size);
	void addVarAlias(const std::string toAliasName, const std::string aliasName);
	void addVarAliasWithPointer(Var* toAliasVar, int& varIndex, const std::string aliasName);

	Var* addVarWithReference(const std::string name, const ReservedWord type, const int size);

	Var* getVar(const std::string &name, int &val);

	void reassignVar(Var* toReassign, Var* newVar, std::set<long long>& deletedDataSet);

	//
	Var* getSimpleWithIndex(const std::string& var, int& index);
	std::string getForBracket(const std::string& var);
	Var* getVar2(const std::string& name, int& index);


	//
	std::string getForBracket(const std::string& var, bool getReplacement);
};

#endif
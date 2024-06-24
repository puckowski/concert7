
#ifndef OBJECT_STORE_H
#define OBJECT_STORE_H

#include <string>
#include <stack>
#include <iostream>
#include <unordered_map>
#include <cctype>
#include <utility>
#include <sstream>
#include <algorithm>

#include "Var.h"

class ObjectStore
{
	std::unordered_map<std::wstring, Var*> mVars;

public:
	ObjectStore();
	~ObjectStore();
	void print();

	void addVar(const std::wstring& name, const ReservedWord& type);

	void addVar(Var* var);

	int removeVar(const std::wstring& name);
	void removeAllVars();

	void addVar(const std::wstring name, const ReservedWord type, const int size);

	Var* addVarWithReference(const std::wstring name, const ReservedWord type, const int size);

	std::vector<std::wstring> getKeys();

	Var* getSimpleWithIndex(const std::wstring& var, int& index);

	std::wstring getForBracket(const std::wstring& var);

	Var* getVar2(const std::wstring& name, int& index);

	Var* getVar(const std::wstring& name, int& val);

	//
	std::wstring getForBracket(const std::wstring& var, bool getReplacement);
};

#endif
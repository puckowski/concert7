
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
	std::unordered_map<std::string, Var*> mVars;

public:
	ObjectStore();
	~ObjectStore();
	void print();

	void addVar(const std::string& name, const ReservedWord& type);

	void addVar(Var* var);

	int removeVar(const std::string& name);
	void removeAllVars();

	void addVar(const std::string name, const ReservedWord type, const int size);

	Var* addVarWithReference(const std::string name, const ReservedWord type, const int size);

	std::vector<std::string> getKeys();

	Var* getSimpleWithIndex(const std::string& var, int& index);

	std::string getForBracket(const std::string& var);

	Var* getVar2(const std::string& name, int& index);

	Var* getVar(const std::string& name, int& val);

	//
	std::string getForBracket(const std::string& var, bool getReplacement);
};

#endif
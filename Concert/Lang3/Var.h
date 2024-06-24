
#ifndef VAR_H
#define VAR_H

#include <string>

#include "reservedWord.h"
class ObjectStore;

class Var
{
public:
	void* data;
	std::wstring name;
	ReservedWord type;
	int size;
	int reassignCount;
	int reassignTargetCount;

	Var(const std::wstring &n, const ReservedWord &t);

	Var(const std::wstring &n, const ReservedWord &t, const int &s);

	Var(int value);

	Var(long long int value);
	Var(double value);

	Var(std::wstring value);

	Var(ObjectStore* value);

	Var(const std::wstring& n, const ReservedWord& t, const int& s, Var* aliasVar);

	~Var();
	void deleteData();
};

#endif

#ifndef VAR_H
#define VAR_H

#include <string>

#include "reservedWord.h"
class ObjectStore;

class Var
{
public:
	void* data;
	std::string name;
	ReservedWord type;
	int size;

	Var(const std::string &n, const ReservedWord &t);

	Var(const std::string &n, const ReservedWord &t, const int &s);

	Var(int value);

	Var(long long int value);
	Var(double value);

	Var(std::string value);

	Var(ObjectStore* value);

	Var(const std::string& n, const ReservedWord& t, const int& s, Var* aliasVar);

	~Var();
	void deleteData();
};

#endif
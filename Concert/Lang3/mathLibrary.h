
#ifndef MATH_LIBRARY_H
#define MATH_LIBRARY_H

#include <vector>
#include <string>
#include <cstdlib>

#include "header.h"
#include "Var.h"
#include "variableFunctions.h"

void libraryMathSeedRand(std::vector<std::string> &arguments, const int &argumentsSize)
{
	srand(time(NULL));
}

void libraryMathRand(std::vector<std::string> &arguments, const int &argumentsSize)
{
	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);
	int* returnData = static_cast<int*>(v->data);

	returnData[returnVarInt] = rand();
}

void libraryMathIntToDouble(std::vector<std::string> &arguments, const int &argumentsSize)
{
	int r1;
	bool createdInt;
	Var* intVar = getVar(arguments[2], r1, createdInt);

	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

	int* pstr = static_cast<int*>(intVar->data);
	double* returnData = static_cast<double*>(v->data);

	returnData[returnVarInt] = pstr[r1];

	if (createdInt)
		delete intVar;
}

void libraryMathAbsoluteValue(std::vector<std::string>& arguments, const int& argumentsSize)
{
	int r1;
	bool createdInt;
	Var* intVar = getVar(arguments[2], r1, createdInt);

	switch (intVar->type)
	{
	case TYPE_INT:
	{
		Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

		int* pstr = static_cast<int*>(intVar->data);
		int* returnData = static_cast<int*>(v->data);

		returnData[returnVarInt] = std::abs(pstr[r1]);

		break;
	}
	case TYPE_LONG:
	{
		Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

		long long int* pstr = static_cast<long long int*>(intVar->data);
		long long int* returnData = static_cast<long long int*>(v->data);

		returnData[returnVarInt] = std::abs(pstr[r1]);

		break;
	}
	case TYPE_DOUBLE:
	{
		Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

		double* pstr = static_cast<double*>(intVar->data);
		double* returnData = static_cast<double*>(v->data);

		returnData[returnVarInt] = std::abs(pstr[r1]);

		break;
	}
	}

	if (createdInt)
		delete intVar;
}

void libraryMathLongToDouble(std::vector<std::string> &arguments, const int &argumentsSize)
{
	int r1;
	bool createdInt;
	Var* intVar = getVar(arguments[2], r1, createdInt);

	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

	long long int* pstr = static_cast<long long int*>(intVar->data);
	double* returnData = static_cast<double*>(v->data);

	returnData[returnVarInt] = pstr[r1];

	if (createdInt)
		delete intVar;
}

void libraryMathIntToLong(std::vector<std::string> &arguments, const int &argumentsSize)
{
	int r1;
	bool createdInt;
	Var* intVar = getVar(arguments[2], r1, createdInt);

	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

	int* pstr = static_cast<int*>(intVar->data);
	long long int* returnData = static_cast<long long int*>(v->data);

	long long int ii = pstr[r1];

	returnData[returnVarInt] = ii;// pstr[r1];

	if (createdInt)
		delete intVar;
}

void libraryMathLongToInt(std::vector<std::string> &arguments, const int &argumentsSize)
{
	int r1;
	bool createdInt;
	Var* intVar = getVar(arguments[2], r1, createdInt);

	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

	long long int* pstr = static_cast<long long int*>(intVar->data);
	int* returnData = static_cast<int*>(v->data);

	returnData[returnVarInt] = pstr[r1];

	if (createdInt)
		delete intVar;
}

void libraryMathDoubleToInt(std::vector<std::string> &arguments, const int &argumentsSize)
{
	int r1;
	bool createdDouble;
	Var* doubleVar = getVar(arguments[2], r1, createdDouble);

	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

	double* pstr = static_cast<double*>(doubleVar->data);
	int* returnData = static_cast<int*>(v->data);

	returnData[returnVarInt] = pstr[r1];

	if (createdDouble)
		delete doubleVar;
}

void libraryMathDoubleToLong(std::vector<std::string> &arguments, const int &argumentsSize)
{
	int r1;
	bool createdDouble;
	Var* doubleVar = getVar(arguments[2], r1, createdDouble);

	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

	double* pstr = static_cast<double*>(doubleVar->data);
	long long int* returnData = static_cast<long long int*>(v->data);

	returnData[returnVarInt] = pstr[r1];

	if (createdDouble)
		delete doubleVar;
}

#endif
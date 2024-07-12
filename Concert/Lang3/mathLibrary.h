
#ifndef MATH_LIBRARY_H
#define MATH_LIBRARY_H

#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>

#include "header.h"
#include "Var.h"
#include "variableFunctions.h"

void libraryMathSeedRand(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	srand(time(NULL));
}

void libraryMathRand(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);
	int* returnData = static_cast<int*>(v->data);

	returnData[returnVarInt] = rand();
}

void libraryMathIntToDouble(std::vector<std::wstring> &arguments, const int &argumentsSize)
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

void libraryMathAbsoluteValue(std::vector<std::wstring>& arguments, const int& argumentsSize)
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

void libraryMathExp(std::vector<std::wstring>& arguments, const int& argumentsSize)
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

		returnData[returnVarInt] = std::exp(pstr[r1]);

		break;
	}
	case TYPE_LONG:
	{
		Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

		long long int* pstr = static_cast<long long int*>(intVar->data);
		long long int* returnData = static_cast<long long int*>(v->data);

		returnData[returnVarInt] = std::expl(pstr[r1]);

		break;
	}
	case TYPE_DOUBLE:
	{
		Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

		double* pstr = static_cast<double*>(intVar->data);
		double* returnData = static_cast<double*>(v->data);

		returnData[returnVarInt] = std::exp(pstr[r1]);

		break;
	}
	}

	if (createdInt)
		delete intVar;
}

void libraryMathPi(std::vector<std::wstring>& arguments, const int& argumentsSize)
{
	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

	double* returnData = static_cast<double*>(v->data);

	returnData[returnVarInt] = 3.141592653589793;
}

void libraryMathSetPrecision(std::vector<std::wstring>& arguments, const int& argumentsSize)
{
	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

	int* returnData = static_cast<int*>(v->data);

	std::cout << std::setprecision(returnData[returnVarInt]);
}

void libraryMathCeil(std::vector<std::wstring>& arguments, const int& argumentsSize)
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

		returnData[returnVarInt] = std::ceil(pstr[r1]);

		break;
	}
	case TYPE_LONG:
	{
		Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

		long long int* pstr = static_cast<long long int*>(intVar->data);
		long long int* returnData = static_cast<long long int*>(v->data);

		returnData[returnVarInt] = std::ceill(pstr[r1]);

		break;
	}
	case TYPE_DOUBLE:
	{
		Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

		double* pstr = static_cast<double*>(intVar->data);
		double* returnData = static_cast<double*>(v->data);

		returnData[returnVarInt] = std::ceilf(pstr[r1]);

		break;
	}
	}

	if (createdInt)
		delete intVar;
}

void libraryMathFloor(std::vector<std::wstring>& arguments, const int& argumentsSize)
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

		returnData[returnVarInt] = std::floor(pstr[r1]);

		break;
	}
	case TYPE_LONG:
	{
		Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

		long long int* pstr = static_cast<long long int*>(intVar->data);
		long long int* returnData = static_cast<long long int*>(v->data);

		returnData[returnVarInt] = std::floorl(pstr[r1]);

		break;
	}
	case TYPE_DOUBLE:
	{
		Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

		double* pstr = static_cast<double*>(intVar->data);
		double* returnData = static_cast<double*>(v->data);

		returnData[returnVarInt] = std::floorf(pstr[r1]);

		break;
	}
	}

	if (createdInt)
		delete intVar;
}

void libraryMathRound(std::vector<std::wstring>& arguments, const int& argumentsSize)
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

		returnData[returnVarInt] = std::round(pstr[r1]);

		break;
	}
	case TYPE_LONG:
	{
		Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

		long long int* pstr = static_cast<long long int*>(intVar->data);
		long long int* returnData = static_cast<long long int*>(v->data);

		returnData[returnVarInt] = std::roundl(pstr[r1]);

		break;
	}
	case TYPE_DOUBLE:
	{
		Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

		double* pstr = static_cast<double*>(intVar->data);
		double* returnData = static_cast<double*>(v->data);

		returnData[returnVarInt] = std::roundf(pstr[r1]);

		break;
	}
	}

	if (createdInt)
		delete intVar;
}

void libraryMathSin(std::vector<std::wstring>& arguments, const int& argumentsSize)
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

		returnData[returnVarInt] = std::sin(pstr[r1]);

		break;
	}
	case TYPE_LONG:
	{
		Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

		long long int* pstr = static_cast<long long int*>(intVar->data);
		long long int* returnData = static_cast<long long int*>(v->data);

		returnData[returnVarInt] = std::sinl(pstr[r1]);

		break;
	}
	case TYPE_DOUBLE:
	{
		Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

		double* pstr = static_cast<double*>(intVar->data);
		double* returnData = static_cast<double*>(v->data);

		returnData[returnVarInt] = std::sinf(pstr[r1]);

		break;
	}
	}

	if (createdInt)
		delete intVar;
}

void libraryMathCos(std::vector<std::wstring>& arguments, const int& argumentsSize)
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

		returnData[returnVarInt] = std::cos(pstr[r1]);

		break;
	}
	case TYPE_LONG:
	{
		Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

		long long int* pstr = static_cast<long long int*>(intVar->data);
		long long int* returnData = static_cast<long long int*>(v->data);

		returnData[returnVarInt] = std::cosl(pstr[r1]);

		break;
	}
	case TYPE_DOUBLE:
	{
		Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

		double* pstr = static_cast<double*>(intVar->data);
		double* returnData = static_cast<double*>(v->data);

		returnData[returnVarInt] = std::cosf(pstr[r1]);

		break;
	}
	}

	if (createdInt)
		delete intVar;
}

void libraryMathTan(std::vector<std::wstring>& arguments, const int& argumentsSize)
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

		returnData[returnVarInt] = std::tan(pstr[r1]);

		break;
	}
	case TYPE_LONG:
	{
		Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

		long long int* pstr = static_cast<long long int*>(intVar->data);
		long long int* returnData = static_cast<long long int*>(v->data);

		returnData[returnVarInt] = std::tanl(pstr[r1]);

		break;
	}
	case TYPE_DOUBLE:
	{
		Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

		double* pstr = static_cast<double*>(intVar->data);
		double* returnData = static_cast<double*>(v->data);

		returnData[returnVarInt] = std::tanf(pstr[r1]);

		break;
	}
	}

	if (createdInt)
		delete intVar;
}

void libraryMathLog10(std::vector<std::wstring>& arguments, const int& argumentsSize)
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

		returnData[returnVarInt] = std::log10(pstr[r1]);

		break;
	}
	case TYPE_LONG:
	{
		Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

		long long int* pstr = static_cast<long long int*>(intVar->data);
		long long int* returnData = static_cast<long long int*>(v->data);

		returnData[returnVarInt] = std::log10l(pstr[r1]);

		break;
	}
	case TYPE_DOUBLE:
	{
		Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

		double* pstr = static_cast<double*>(intVar->data);
		double* returnData = static_cast<double*>(v->data);

		returnData[returnVarInt] = std::log10f(pstr[r1]);

		break;
	}
	}

	if (createdInt)
		delete intVar;
}

void libraryMathSqrt(std::vector<std::wstring>& arguments, const int& argumentsSize)
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

		returnData[returnVarInt] = std::sqrt(pstr[r1]);

		break;
	}
	case TYPE_LONG:
	{
		Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

		long long int* pstr = static_cast<long long int*>(intVar->data);
		long long int* returnData = static_cast<long long int*>(v->data);

		returnData[returnVarInt] = std::sqrtl(pstr[r1]);

		break;
	}
	case TYPE_DOUBLE:
	{
		Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

		double* pstr = static_cast<double*>(intVar->data);
		double* returnData = static_cast<double*>(v->data);

		returnData[returnVarInt] = std::sqrtf(pstr[r1]);

		break;
	}
	}

	if (createdInt)
		delete intVar;
}

void libraryMathLongToDouble(std::vector<std::wstring> &arguments, const int &argumentsSize)
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

void libraryMathIntToLong(std::vector<std::wstring> &arguments, const int &argumentsSize)
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

void libraryMathLongToInt(std::vector<std::wstring> &arguments, const int &argumentsSize)
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

void libraryMathDoubleToInt(std::vector<std::wstring> &arguments, const int &argumentsSize)
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

void libraryMathDoubleToLong(std::vector<std::wstring> &arguments, const int &argumentsSize)
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
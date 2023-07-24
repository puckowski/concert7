
#ifndef PRINT_FUNCTIONS
#define PRINT_FUNCTIONS

#include <string>
#include <iostream>

#include "Var.h"

void println(Var* v)
{
	switch (v->type)
	{
	case TYPE_INT:
	{
		int* pstr = static_cast<int*>(v->data);

		for (int i = 0; i < v->size; ++i)
			std::cout << pstr[i] << " ";

		break;
	}
	case TYPE_LONG:
	{
		long long int* pstr = static_cast<long long int*>(v->data);

		for (int i = 0; i < v->size; ++i)
			std::cout << pstr[i] << " ";

		break;
	}
	case TYPE_DOUBLE:
	{
		double* pstr = static_cast<double*>(v->data);

		for (int i = 0; i < v->size; ++i)
			std::cout << pstr[i] << " ";

		break;
	}
	case TYPE_STRING:
	{
		std::string* pstr = static_cast<std::string*>(v->data);

		for (int i = 0; i < v->size; ++i)
			std::cout << pstr[i] << " ";

		break;
	}
	}
}

void print(Var* v)
{
	switch (v->type)
	{
	case TYPE_INT:
	{
		int* pstr = static_cast<int*>(v->data);
			
		for (int i = 0; i < v->size; ++i)
			std::cout << pstr[i] << " ";

		break;
	}
	case TYPE_DOUBLE:
	{
		double* pstr = static_cast<double*>(v->data);
			
		for (int i = 0; i < v->size; ++i)
			std::cout << pstr[i] << " ";

		break;
	}
	case TYPE_LONG:
	{
		long long int* pstr = static_cast<long long int*>(v->data);

		for (int i = 0; i < v->size; ++i)
			std::cout << pstr[i] << " ";

		break;
	}
	case TYPE_STRING:
	{
		std::string* pstr = static_cast<std::string*>(v->data);
			
		for (int i = 0; i < v->size; ++i)
			std::cout << pstr[i] << " ";

		break;
	}
	}
}

#endif
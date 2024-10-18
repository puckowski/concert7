
#ifndef VAR_CPP
#define VAR_CPP

#include "Var.h"
#include "ObjectStore.h"

const std::wstring NEWLINE_STRING2 = std::wstring(L"\n");

void findAndReplace2(std::wstring& source, std::wstring const& find, std::wstring const& replace)
{
	for (std::wstring::size_type i = 0; (i = source.find(find, i)) != std::wstring::npos;)
	{
		source.replace(i, find.length(), replace);
		i += replace.length();
	}
}

void findAndReplaceNewline2(std::wstring& source)
{
	for (std::wstring::size_type i = 0; (i = source.find(L"\\n", i)) != std::wstring::npos;)
	{
		source.replace(i, 2, NEWLINE_STRING2);
		i += 2;
	}
}

void findAndReplaceQuoteEscape2(std::wstring& source)
{
	for (std::wstring::size_type i = 0; (i = source.find(L"\\\"", i)) != std::wstring::npos;)
	{
		source.replace(i, 2, L"\"");
		i += 2;
	}
}

Var::Var(const std::wstring &n, const ReservedWord &t)
{
	name = n;
	type = t;
	size = 1;
	reassignCount = 0;
	reassignTargetCount = 0;

	switch (t)
	{
	case TYPE_INT:
	{
		int* intArray = new int[1];
		data = intArray;

		break;
	}
	case TYPE_LONG:
	{
		long long int* longLongArray = new long long int[1];
		data = longLongArray;

		break;
	}
	case TYPE_DOUBLE:
	{
		double* doubleArray = new double[1];
		data = doubleArray;

		break;
	}
	case TYPE_STRING:
	{
		std::wstring* stringArray = new std::wstring[1];
		data = stringArray;

		break;
	}
	case TYPE_OBJECT:
	{
		ObjectStore** objStore = new ObjectStore *[1];
		objStore[0] = new ObjectStore();
		data = objStore;

		break;
	}
	}
}

Var::Var(const std::wstring& n, const ReservedWord& t, const int& s, Var* aliasVar)
{
	name = n;
	type = t;
	size = s;
	reassignCount = 0;
	data = aliasVar->data;
}

Var::Var(const std::wstring &n, const ReservedWord &t, const int &s)
{
	name = n;
	type = t;
	size = s;
	reassignCount = 0;
	reassignTargetCount = 0;

	switch (t)
	{
	case TYPE_INT:
	{
		int* intArray = new int[size];
		data = intArray;

		break;
	}
	case TYPE_LONG:
	{
		long long int* longLongArray = new long long int[size];
		data = longLongArray;

		break;
	}
	case TYPE_DOUBLE:
	{
		double* doubleArray = new double[size];
		data = doubleArray;

		break;
	}
	case TYPE_STRING:
	{
		std::wstring* stringArray = new std::wstring[size];
		data = stringArray;

		break;
	}
	case TYPE_OBJECT:
	{
		ObjectStore** objStore = new ObjectStore*[size];
		for (int i = 0; i < size; ++i) {
			objStore[i] = new ObjectStore();
		}
		data = objStore;

		break;
	}
	}
}

Var::Var(int value)
{
	type = TYPE_INT;
	size = 1;
	reassignCount = 0;
	reassignTargetCount = 0;

	int* intArray = new int[1];
	intArray[0] = value;
	data = intArray;
}

Var::Var(long long int value)
{
	type = TYPE_LONG;
	size = 1;
	reassignCount = 0;
	reassignTargetCount = 0;

	long long int* longLongArray = new long long int[1];
	longLongArray[0] = value;
	data = longLongArray;
}

Var::Var(double value)
{
	type = TYPE_DOUBLE;
	size = 1;
	reassignCount = 0;
	reassignTargetCount = 0;

	double* doubleArray = new double[1];
	doubleArray[0] = value;
	data = doubleArray;
}

Var::Var(std::wstring value)
{
	type = TYPE_STRING;
	size = 1;
	reassignCount = 0;
	reassignTargetCount = 0;

	std::wstring* stringArray = new std::wstring[1];
	findAndReplaceNewline2(value);
	findAndReplaceQuoteEscape2(value);
	stringArray[0] = value;
	data = stringArray;
}

Var::Var(ObjectStore* value)
{
	type = TYPE_OBJECT;
	size = 1;
	reassignCount = 0;
	reassignTargetCount = 0;

	data = value;
}

Var::~Var()
{
	if (reassignTargetCount == 1)
	{
		return;
	}
	else if (reassignCount > 0)
	{
		return;
	}

	switch (type)
	{
	case TYPE_INT:
	{
		int* intArray = static_cast<int*>(data);
		delete[] intArray;

		break;
	}
	case TYPE_LONG:
	{
		long long int* longLongArray = static_cast<long long int*>(data);
		delete[] longLongArray;

		break;
	}
	case TYPE_DOUBLE:
	{
		double* doubleArray = static_cast<double*>(data);
		delete[] doubleArray;

		break;
	}
	case TYPE_STRING:
	{
		std::wstring* stringArray = static_cast<std::wstring*>(data);
		delete[] stringArray;

		break;
	}
	case TYPE_OBJECT:
	{
		ObjectStore** objArray = static_cast<ObjectStore**>(data);
		for (int i = 0; i < size; ++i) {
			delete objArray[i];
			objArray[i] = nullptr;
		}
		delete objArray;
		objArray = nullptr;

		break;
	}
	}
}

void Var::deleteData()
{
	if (data == nullptr) 
	{
		return;
	}
	else if (reassignCount > 0) 
	{
		reassignCount--;

		return;
	}

	switch (type)
	{
	case TYPE_INT:
	{
		int* intArray = static_cast<int*>(data);
		delete[] intArray;

		break;
	}
	case TYPE_LONG:
	{
		long long int* longLongArray = static_cast<long long int*>(data);
		delete[] longLongArray;

		break;
	}
	case TYPE_DOUBLE:
	{
		double* doubleArray = static_cast<double*>(data);
		delete[] doubleArray;

		break;
	}
	case TYPE_STRING:
	{
		std::wstring* stringArray = static_cast<std::wstring*>(data);
		delete[] stringArray;

		break;
	}
	case TYPE_OBJECT:
	{
		ObjectStore** objArray = static_cast<ObjectStore**>(data);
		for (int i = 0; i < size; ++i) {
			delete objArray[i];
			objArray[i] = nullptr;
		}
		delete objArray;
		objArray = nullptr;

		break;
	}
	}
}

#endif
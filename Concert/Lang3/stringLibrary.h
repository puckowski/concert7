
#ifndef STRING_LIBRARY_H
#define STRING_LIBRARY_H

#include <vector>
#include <string>
#include <algorithm>
#include <locale>

void libraryStringCharAt(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	int r1, r2;
	bool createdString, createdIndex;
	Var* stringVar = getVar(arguments[2], r1, createdString);
	Var* indexVar = getVar(arguments[3], r2, createdIndex);

	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt , createdRetVar);

	std::wstring* pstr = static_cast<std::wstring*>(stringVar->data);
	int* indexData = static_cast<int*>(indexVar->data);
	std::wstring* returnData = static_cast<std::wstring*>(v->data);

	char c = pstr[r1][indexData[0]];
	returnData[returnVarInt] = std::wstring(1, c);

	if (createdString)
		delete stringVar;

	if (createdIndex)
		delete indexVar;
}

void libraryWcharToString(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	int r1;
	bool createdString;
	Var* stringVar = getVar(arguments[2], r1, createdString);

	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

	int* pstr = static_cast<int*>(stringVar->data);
	wchar_t charValue = pstr[r1];

	std::wstring* returnData = static_cast<std::wstring*>(v->data);

	std::wstring resultStr;
	resultStr.push_back(charValue);

	returnData[returnVarInt] = resultStr;

	if (createdString)
		delete stringVar;
}

void libraryCharToString(std::vector<std::wstring>& arguments, const int& argumentsSize)
{
	int r1;
	bool createdString;
	Var* stringVar = getVar(arguments[2], r1, createdString);

	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

	int* pstr = static_cast<int*>(stringVar->data);
	std::wstring* returnData = static_cast<std::wstring*>(v->data);

	returnData[returnVarInt] = std::wstring(1, pstr[r1]);

	if (createdString)
		delete stringVar;
}

void libraryIntToString(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	int r1;
	bool createdString;
	Var* stringVar = getVar(arguments[2], r1, createdString);

	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

	int* pstr = static_cast<int*>(stringVar->data);
	std::wstring* returnData = static_cast<std::wstring*>(v->data);

	returnData[returnVarInt] = std::to_wstring(pstr[r1]);

	if (createdString)
		delete stringVar;
}

void libraryDoubleToString(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	int r1;
	bool createdString;
	Var* stringVar = getVar(arguments[2], r1, createdString);

	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

	double* pstr = static_cast<double*>(stringVar->data);
	std::wstring* returnData = static_cast<std::wstring*>(v->data);

	returnData[returnVarInt] = std::to_wstring(pstr[r1]);

	if (createdString)
		delete stringVar;
}

void libraryStringToDouble(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	int r1;
	bool createdString;
	Var* stringVar = getVar(arguments[2], r1, createdString);

	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar); 

	std::wstring* pstr = static_cast<std::wstring*>(stringVar->data);
	double* returnData = static_cast<double*>(v->data);

	returnData[returnVarInt] = std::stod(pstr[r1]);

	if (createdString)
		delete stringVar;
}

void libraryCharToInt(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	int r1;
	bool createdString;
	Var* stringVar = getVar(arguments[2], r1, createdString);

	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

	std::wstring* pstr = static_cast<std::wstring*>(stringVar->data);
	int* returnData = static_cast<int*>(v->data);

	returnData[returnVarInt] = pstr[r1][0];

	if (createdString)
		delete stringVar;
}

void libraryStringToInt(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	int r1;
	bool createdString;
	Var* stringVar = getVar(arguments[2], r1, createdString);

	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar); 

	std::wstring* pstr = static_cast<std::wstring*>(stringVar->data);
	int* returnData = static_cast<int*>(v->data);

	returnData[returnVarInt] = std::stoi(pstr[r1]);

	if (createdString)
		delete stringVar;
}

void libraryStringLength(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	int r1;
	bool createdString;
	Var* stringVar = getVar(arguments[2], r1, createdString);

	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar); 

	std::wstring* pstr = static_cast<std::wstring*>(stringVar->data);
	int* returnData = static_cast<int*>(v->data);

	returnData[returnVarInt] = pstr[r1].length();

	if (createdString)
		delete stringVar;
}

void libraryStringContains(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	int r1, r2;
	bool createdString, createdSubstr;
	Var* stringVar = getVar(arguments[2], r1, createdString);
	Var* substrVar = getVar(arguments[3], r2, createdSubstr);

	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt); 

	std::wstring* pstr = static_cast<std::wstring*>(stringVar->data);
	std::wstring* substrData = static_cast<std::wstring*>(substrVar->data);
	int* returnData = static_cast<int*>(v->data);

	returnData[returnVarInt] = (pstr[r1].find(substrData[r2]) != std::wstring::npos);

	if (createdString)
		delete stringVar;

	if (createdSubstr)
		delete substrVar;
}

void libraryStringIndexOf(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	int r1, r2;
	bool createdString, createdIndex;
	Var* stringVar = getVar(arguments[2], r1, createdString);
	Var* indexVar = getVar(arguments[3], r2, createdIndex);

	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar); 

	std::wstring* pstr = static_cast<std::wstring*>(stringVar->data);
	int* indexData = static_cast<int*>(indexVar->data);
	int* returnData = static_cast<int*>(v->data);

	returnData[returnVarInt] = pstr[r1].find(indexData[r2]);

	if (createdString)
		delete stringVar;

	if (createdIndex)
		delete indexVar;
}

void libraryStringSubstring(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	int r1, r2, r3;
	bool createdString, createdStartIndex, createdStopIndex;
	Var* stringVar = getVar(arguments[2], r1, createdString);
	Var* startIndexVar = getVar(arguments[3], r2, createdStartIndex);
	Var* stopIndexVar = getVar(arguments[4], r3, createdStopIndex);

	std::wstring* pstr = static_cast<std::wstring*>(stringVar->data);
	int* startIndexData = static_cast<int*>(startIndexVar->data);
	int* stopIndexData = static_cast<int*>(stopIndexVar->data);

	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);
	std::wstring* returnData = static_cast<std::wstring*>(v->data);

	returnData[returnVarInt] = pstr[r1].substr(startIndexData[r2], stopIndexData[r3]);

	if (createdString)
		delete stringVar;

	if (createdStartIndex)
		delete startIndexVar;

	if (createdStopIndex)
		delete stopIndexVar;
}

void libraryStringLowerCase(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	int r1;
	bool createdString;
	Var* stringVar = getVar(arguments[2], r1, createdString);
	
	std::wstring* pstr = static_cast<std::wstring*>(stringVar->data);
	
	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);
	std::wstring* returnData = static_cast<std::wstring*>(v->data);

	returnData[returnVarInt] = pstr[r1];

	std::transform(returnData[returnVarInt].begin(), returnData[returnVarInt].end(), returnData[returnVarInt].begin(), ::tolower);

	if (createdString)
		delete stringVar;
}

void libraryStringUpperCase(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	int r1;
	bool createdString;
	Var* stringVar = getVar(arguments[2], r1, createdString);

	std::wstring* pstr = static_cast<std::wstring*>(stringVar->data);

	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);
	std::wstring* returnData = static_cast<std::wstring*>(v->data);

	returnData[returnVarInt] = pstr[r1];

	std::transform(returnData[returnVarInt].begin(), returnData[returnVarInt].end(), returnData[returnVarInt].begin(), ::toupper);

	if (createdString)
		delete stringVar;
}

#endif
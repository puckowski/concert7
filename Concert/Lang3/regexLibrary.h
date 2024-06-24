
#ifndef REGEX_LIBRARY_H
#define REGEX_LIBRARY_H

#include <vector>
#include <string>
#include <regex> 

#include "header.h"
#include "Var.h"
#include "variableFunctions.h"

void libraryRegexReplace(std::vector<std::wstring>& arguments, const int& argumentsSize)
{
	int r1;
	bool createdVar = false;
	Var* v = getVar(arguments[2], r1, createdVar);
	std::wstring* pstr = static_cast<std::wstring*>(v->data);
	const std::wstring searchText = pstr[r1];

	r1 = 0;
	bool createdVar2 = false;
	Var* v2 = getVar(arguments[3], r1, createdVar2);
	std::wstring* pstr2 = static_cast<std::wstring*>(v2->data);
	std::wstring regexStr = pstr2[r1];

	r1 = 0;
	bool createdVar3 = false;
	Var* v3 = getVar(arguments[4], r1, createdVar2);
	std::wstring* pstr3 = static_cast<std::wstring*>(v3->data);
	std::wstring replaceStr = pstr3[r1];

	Var* returnVar = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);
	std::wstring* returnData = static_cast<std::wstring*>(returnVar->data);

	returnData[returnVarInt] = std::regex_replace(searchText, std::wregex(regexStr), replaceStr);

	if (createdVar) {
		delete v;
	}

	if (createdVar2) {
		delete v2;
	}

	if (createdVar3) {
		delete v3;
	}
}

void libraryRegexMatch(std::vector<std::wstring>& arguments, const int& argumentsSize)
{
	int r1;
	bool createdVar = false;
	Var* v = getVar(arguments[2], r1, createdVar);
	std::wstring* pstr = static_cast<std::wstring*>(v->data);
	const std::wstring searchText = pstr[r1];

	r1 = 0;
	bool createdVar2 = false;
	Var* v2 = getVar(arguments[3], r1, createdVar2);
	std::wstring* pstr2 = static_cast<std::wstring*>(v2->data);
	std::wstring regexStr = pstr2[r1];

	Var* returnVar = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);
	int* returnData = static_cast<int*>(returnVar->data);

	if (std::regex_match(searchText, std::wregex(regexStr)))
	{
		returnData[returnVarInt] = 1;
	}
	else
	{
		returnData[returnVarInt] = 0;
	}

	if (createdVar) {
		delete v;
	}

	if (createdVar2) {
		delete v2;
	}
}

void libraryRegexSearch(std::vector<std::wstring>& arguments, const int& argumentsSize)
{
	// (L"regexObj", "text to search", "regex")

	int r1;
	bool createdVar = false;
	Var* v = getVar(arguments[2], r1, createdVar);
	std::wstring* pstr = static_cast<std::wstring*>(v->data);
	const std::wstring varName = pstr[r1];

	gWorkspaceStore->getStore()->addVar(new Var(varName, TYPE_OBJECT, 1));

	r1 = 0;
	bool createdVar2 = false;
	Var* v2 = getVar(arguments[3], r1, createdVar2);
	std::wstring* pstr2 = static_cast<std::wstring*>(v2->data);
	std::wstring textToSearch = pstr2[r1];

	r1 = 0;
	bool createdVar3 = false;
	Var* v3 = getVar(arguments[4], r1, createdVar3);
	std::wstring* pstr3 = static_cast<std::wstring*>(v3->data);
	const std::wstring regexToUse = pstr3[r1];

	std::wregex regexp(regexToUse);

	int len = 0;
	std::vector<std::wstring> data;

	std::wsmatch sm;
	while (std::regex_search(textToSearch, sm, regexp))
	{
		data.push_back(sm.str());
		textToSearch = sm.suffix();
		len++;
	}

	r1 = 0;
	ObjectStore** var = static_cast<ObjectStore**>(gWorkspaceStore->getStore()->getVar(varName, r1)->data);
	ObjectStore* obj = var[r1];
	obj->addVar(L"length", TYPE_INT);

	r1 = 0;
	Var* lenVar = obj->getVar(L"length", r1);
	int* pstrLen = static_cast<int*>(lenVar->data);
	pstrLen[r1] = len;

	obj->addVar(L"data", TYPE_STRING, len);
	r1 = 0;
	Var* dataVar = obj->getVar(L"data", r1);
	std::wstring* pstrData = static_cast<std::wstring*>(dataVar->data);
	for (int i = 0; i < len; ++i) {
		pstrData[i] = data[i];
	}

	if (createdVar) {
		delete v;
	}

	if (createdVar2) {
		delete v2;
	}

	if (createdVar3) {
		delete v3;
	}
}

#endif
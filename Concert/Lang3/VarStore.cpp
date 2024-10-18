
#ifndef VAR_STORE_CPP
#define VAR_STORE_CPP

#include <regex>

#include "VarStore.h"
#include "WorkspaceStore.h"
#include "ObjectStore.h"

const std::wregex FLOAT_REGEX(L"[+-]?([0-9]*[.])?[0-9]+");

bool is_digits(const std::wstring& str)
{
	if (str.length() > 0 && str[0] == '-')
	{
		return std::all_of(str.begin() + 1, str.end(), ::isdigit);
	}
	else
	{
		return std::all_of(str.begin(), str.end(), ::isdigit);
	}
}

VarStore::~VarStore()
{
	for (auto it = mVars.begin(); it != mVars.end();)
	{
		for (auto it2 = mVars.begin(); it2 != mVars.end();)
		{
			if (it == it2)
			{
				it2++;
				continue;
			}
			else if (it->second->data == it2->second->data && it->second->reassignCount > 0 && it2->second->reassignCount == 0)
			{
				it2->second->reassignCount++;
				it2++;
			}
			else {
				it2++;
			}
		}

		it++;
	}

	for (auto it = mVars.begin(); it != mVars.end();)
	{
		if (it->second->reassignTargetCount == 1)
		{
			Var* v = it->second;
			it = mVars.erase(it);
			delete v;
			v = nullptr;
		}
		else if (it->second->reassignCount > 0)
		{
			it->second->reassignCount--;

			if (it->second->reassignTargetCount > 1)
			{
				it->second->reassignTargetCount--;
			}
			
			++it;
		}
		else 
		{
			Var* v = it->second;
			it = mVars.erase(it);
			delete v;
			v = nullptr;
		}
	}
}

void VarStore::print() {
	for (auto it = mVars.begin(); it != mVars.end(); ++it)
	{
		std::wcout << it->second->name << std::endl;
	}
}

void VarStore::addVar(const std::wstring &name, const ReservedWord &type)
{
	auto it = mVars.find(name);
	if (it != mVars.end())
	{
		delete it->second;
		it->second = nullptr;
		it->second = new Var(name, type);
	}
	else
	{
		mVars.insert({ name, new Var(name, type) });
	}
	//mVars.insert({ name, new Var(name, type) });
}

void VarStore::addVar(Var* var)
{
	auto it = mVars.find(var->name);
	if (it != mVars.end()) 
	{
		delete it->second;
		it->second = nullptr;
		it->second = var;
	}
	else
	{
		mVars.insert({ var->name, var });
	}
}

int VarStore::removeVar(const std::wstring &name)
{
	Var* v = nullptr;
	auto search = mVars.find(name);

	if (search != mVars.end())
	{
		v = search->second;
	}

	if (v != nullptr)
	{
		delete v;
		v = nullptr;

		return mVars.erase(name);
	}

	return 0; // false
}

void VarStore::addVar(const std::wstring name, const ReservedWord type, const int size)
{
	Var* v = new Var(name, type, size);
	//mVars.insert({ name, v });
	auto it = mVars.find(name);
	if (it != mVars.end())
	{
		delete it->second;
		it->second = nullptr;
		it->second = v;
	}
	else
	{
		mVars.insert({ name, v });
	}
}

void VarStore::addVarAlias(const std::wstring toAliasName, const std::wstring aliasName)
{
	int index;
	Var* toAliasVar = getVar(toAliasName, index);
	Var* v = new Var(aliasName, toAliasVar[index].type, toAliasVar[index].size, toAliasVar);
	auto it = mVars.find(aliasName);
	if (it != mVars.end())
	{
		delete it->second;
		it->second = nullptr;
		it->second = v;
	}
	else
	{
		mVars.insert({ aliasName, v });
	}
	//mVars.insert({ aliasName, v });
}

void VarStore::addVarAliasWithPointer(Var* toAliasVar, int &varIndex, const std::wstring aliasName)
{
	Var* v = new Var(aliasName, toAliasVar[varIndex].type, toAliasVar[varIndex].size, toAliasVar);
	auto it = mVars.find(aliasName);
	if (it != mVars.end()) 
	{
		delete it->second;
		it->second = nullptr;
		it->second = v;
	}
	else 
	{
		mVars.insert({ aliasName, v });
	}
	//mVars.insert({ aliasName, v });
}

void VarStore::reassignAllVar(Var* toReassign, Var* newVar)
{
	for (auto it = mVars.begin(); it != mVars.end(); ++it)
	{
		if (it->second == toReassign)
		{
			reassignVar(it->second, newVar);
		}
	}
}

void VarStore::reassignVar(Var* toReassign, Var* newVar) //, std::set<long long> &deletedDataSet)
{
	toReassign->reassignCount++;
	toReassign->deleteData();

	toReassign->data = newVar->data;
	toReassign->size = newVar->size;
}

Var* VarStore::addVarWithReference(const std::wstring name, const ReservedWord type, const int size)
{
	Var* v = new Var(name, type, size);

	auto it = mVars.find(v->name);
	if (it != mVars.end()) 
	{
		delete it->second;
		it->second = nullptr;
		it->second = v;
	}
	else {
		mVars.insert({ name, v });
	}

	return v;
}

Var* VarStore::getSimpleWithIndex(const std::wstring& var, int& index)
{
	int pos = var.find(L"[");

	if (pos == std::wstring::npos) 
	{
		index = 0;

		auto search = mVars.find(var);

		if (search != mVars.end())
		{
			return search->second;
		}

		return nullptr;
	}
	else 
	{
		std::wstring idx = var.substr(pos + 1, var.find(L"]") - pos - 1);
		index = std::stoi(idx);

		std::wstring varName = var.substr(0, pos);

		auto search = mVars.find(varName);

		if (search != mVars.end())
		{
			return search->second;
		}

		return nullptr;
	}
}

std::wstring VarStore::getForBracket(const std::wstring& var, bool getReplacement)
{
	int openBracketPos = var.find(L"[");
	int closeBracketPos;
	std::wstring varNameSimple;
	std::wstring bracketStrContents;
	std::wstring origVarStrCopy = var;
	std::vector<std::wstring> varStrList;
	std::vector<std::wstring> indexStrList;

	while (openBracketPos != std::wstring::npos)
	{
		varNameSimple = origVarStrCopy.substr(0, openBracketPos);
		varStrList.insert(varStrList.begin(), varNameSimple);

		closeBracketPos = origVarStrCopy.find_last_of(L"]");
		bracketStrContents = origVarStrCopy.substr(openBracketPos + 1, closeBracketPos - openBracketPos - 1);

		origVarStrCopy = bracketStrContents;

		openBracketPos = bracketStrContents.find(L"[");
	}

	indexStrList.push_back(bracketStrContents);

	int lastIndex = 0;
	std::wstring lastVarStr = var;
	Var* currVar = nullptr;
	int currIndex = 0;

	while (varStrList.empty() == false)
	{
		std::wstring indexStr = indexStrList.front();

		int dotPos = indexStr.find(L".");

		if (dotPos != std::wstring::npos)
		{
			int openBracketIndex = var.find(L"[");
			int closeBracketIndex = var.find(L"]");
			std::wstring bracketContentStr = var.substr(openBracketIndex + 1, closeBracketIndex - openBracketIndex - 1);

			currVar = getVar2(bracketContentStr, currIndex);

			if (currVar != nullptr)
			{
				switch (currVar->type)
				{
				case TYPE_INT:
				{
					int* pstr = static_cast<int*>(currVar->data);
					currIndex = pstr[currIndex];

					break;
				}
				case TYPE_LONG:
				{
					long long int* pstr = static_cast<long long int*>(currVar->data);
					currIndex = pstr[currIndex];

					break;
				}
				}
			}

			indexStrList.erase(indexStrList.begin());

			std::wstring var = varStrList.front();
			varStrList.erase(varStrList.begin());

			lastVarStr = var;

			var += L"[" + std::to_wstring(currIndex) + L"]";

			currVar = nullptr;
			auto search = mVars.find(var);

			if (search != mVars.end())
			{
				currVar = search->second;
			}
		}
		else
		{
			if (is_digits(indexStr) == true)
			{
				currIndex = std::stoi(indexStr);
			}
			else
			{
				int indexVarIndex = 0;
				Var* indexVar = getSimpleWithIndex(indexStr, indexVarIndex);

				if (currVar != nullptr)
				{
					switch (currVar->type)
					{
					case TYPE_INT:
					{
						int* pstr = static_cast<int*>(currVar->data);
						currIndex = pstr[currIndex];

						break;
					}
					case TYPE_LONG:
					{
						long long int* pstr = static_cast<long long int*>(currVar->data);
						currIndex = pstr[currIndex];

						break;
					}
					}
				}
			}

			indexStrList.erase(indexStrList.begin());

			std::wstring var = varStrList.front();
			varStrList.erase(varStrList.begin());

			lastVarStr = var;

			currVar = nullptr;
			auto search = mVars.find(var);

			if (search != mVars.end())
			{
				currVar = search->second;
			}
		}
	}

	if (getReplacement == true)
	{
		currVar = nullptr;
		auto search = mVars.find(lastVarStr);

		if (search != mVars.end())
		{
			currVar = search->second;
		}

		std::wstring* pstr = static_cast<std::wstring*>(currVar->data);
		lastVarStr = pstr[0];
	}

	return lastVarStr + L"[" + std::to_wstring(currIndex) + L"]";
}

std::wstring VarStore::getForBracket(const std::wstring& var)
{
	int openBracketPos = var.find(L"[");
	int closeBracketPos;
	std::wstring varNameSimple;
	std::wstring bracketStrContents;
	std::wstring origVarStrCopy = var;
	std::vector<std::wstring> varStrList;
	std::vector<std::wstring> indexStrList;

	while (openBracketPos != std::wstring::npos) 
	{
		varNameSimple = origVarStrCopy.substr(0, openBracketPos);
		varStrList.insert(varStrList.begin(), varNameSimple);

		closeBracketPos = origVarStrCopy.find_last_of(L"]");
		bracketStrContents = origVarStrCopy.substr(openBracketPos + 1, closeBracketPos - openBracketPos - 1);

		origVarStrCopy = bracketStrContents;

		openBracketPos = bracketStrContents.find(L"[");
	}

	indexStrList.push_back(bracketStrContents);

	int lastIndex = 0;
	std::wstring lastVarStr = var;
	Var* currVar = nullptr;
	int currIndex = 0;

	while (varStrList.empty() == false) 
	{
		std::wstring indexStr = indexStrList.front();

		int dotPos = indexStr.find(L".");

		if (dotPos != std::wstring::npos)
		{
			int openBracketIndex = var.find(L"[");
			int closeBracketIndex = var.find(L"]");
			std::wstring bracketContentStr = var.substr(openBracketIndex + 1, closeBracketIndex - openBracketIndex - 1);

			currVar = getVar2(bracketContentStr, currIndex);

			if (currVar != nullptr)
			{
				switch (currVar->type)
				{
				case TYPE_INT:
				{
					int* pstr = static_cast<int*>(currVar->data);
					currIndex = pstr[currIndex];

					break;
				}
				case TYPE_LONG:
				{
					long long int* pstr = static_cast<long long int*>(currVar->data);
					currIndex = pstr[currIndex];

					break;
				}
				}
			}

			indexStrList.erase(indexStrList.begin());

			std::wstring var = varStrList.front();
			varStrList.erase(varStrList.begin());

			lastVarStr = var;

			var += L"[" + std::to_wstring(currIndex) + L"]";

			currVar = nullptr;
			auto search = mVars.find(var);

			if (search != mVars.end())
			{
				currVar = search->second;
			}
		}
		else
		{
			if (is_digits(indexStr) == true)
			{
				currIndex = std::stoi(indexStr);
			}
			else
			{
				int indexVarIndex = 0;
				Var* indexVar = getSimpleWithIndex(indexStr, indexVarIndex);

				if (indexVar != nullptr)
				{
					switch (indexVar->type)
					{
					case TYPE_INT:
					{
						int* pstr = static_cast<int*>(indexVar->data);
						currIndex = pstr[indexVarIndex];

						break;
					}
					case TYPE_LONG:
					{
						long long int* pstr = static_cast<long long int*>(indexVar->data);
						currIndex = pstr[indexVarIndex];

						break;
					}
					}
				}
			}

			indexStrList.erase(indexStrList.begin());

			std::wstring var = varStrList.front();
			varStrList.erase(varStrList.begin());

			lastVarStr = var;

			currVar = nullptr;
			auto search = mVars.find(var);

			if (search != mVars.end())
			{
				currVar = search->second;
			}
		}

		lastIndex = currIndex;

		if (currVar != nullptr)
		{
			switch (currVar->type)
			{
			case TYPE_INT:
			{
				int* pstr = static_cast<int*>(currVar->data);
				indexStrList.push_back(std::to_wstring(pstr[currIndex]));
				lastIndex = currIndex;

				break;
			}
			case TYPE_LONG:
			{
				long long int* pstr = static_cast<long long int*>(currVar->data);
				indexStrList.push_back(std::to_wstring(pstr[currIndex]));
				lastIndex = currIndex;

				break;
			}
			}
		}
	}

	return lastVarStr + L"[" + std::to_wstring(lastIndex) + L"]";
}

bool is_number(const std::wstring& s) {
	return std::regex_match(s, FLOAT_REGEX);
}

Var* VarStore::getVar2(const std::wstring& name, int& index)
{
	index = 0;

	std::wstring::size_type singleQuoteIndex = name.find(L"'");
	int secondQuoteIndex;
	bool hasSingleQuote = false;
	std::wstring quoteReplacementStr, quotedStr;
	int quoteReplaceStartIndex = 0;

	while (singleQuoteIndex != std::wstring::npos)
	{
		hasSingleQuote = true;

		quoteReplacementStr += name.substr(quoteReplaceStartIndex, singleQuoteIndex - quoteReplaceStartIndex);
		secondQuoteIndex = name.find(L"'", singleQuoteIndex + 1);

		quotedStr = name.substr(singleQuoteIndex + 1, secondQuoteIndex - singleQuoteIndex - 1);

		quoteReplacementStr += getForBracket(quotedStr, true);

		singleQuoteIndex = name.find(L"'", secondQuoteIndex + 1);
		quoteReplaceStartIndex = secondQuoteIndex + 1;
	}

	if (hasSingleQuote == true)
	{
		quoteReplacementStr += name.substr(secondQuoteIndex + 1, name.length() - secondQuoteIndex);
	}
	else 
	{
		quoteReplacementStr = name;
	}

	std::wstring doubleBracketTemp;
	int doubleBracketsIndex;

	while (quoteReplacementStr.find(L"][") != std::wstring::npos)
	{
		doubleBracketTemp = quoteReplacementStr.substr(0, quoteReplacementStr.find(L"]["));
		doubleBracketsIndex = quoteReplacementStr.find(L"][");
		
		quoteReplacementStr = quoteReplacementStr.substr(doubleBracketsIndex + 1, quoteReplacementStr.length() - doubleBracketsIndex);
		
		while (doubleBracketTemp[doubleBracketTemp.length() - 1] != '[') 
		{
			doubleBracketTemp.pop_back();
		}
		doubleBracketTemp.pop_back();

		quoteReplacementStr = doubleBracketTemp + quoteReplacementStr;
	}

	std::vector<std::wstring> varTokenList;
	std::wstring varTokenStr;
	int dotPos = quoteReplacementStr.find(L".");
	int dotPosOffset = 0;
	size_t openBracketCount, closeBracketCount;
	Var* currVar = nullptr;

	while (dotPos != std::wstring::npos)
	{
		if (is_number(quoteReplacementStr))
		{
			return currVar;
		}

		varTokenStr = quoteReplacementStr.substr(dotPosOffset, dotPos - dotPosOffset);

		openBracketCount = std::count(varTokenStr.begin(), varTokenStr.end(), '[');
		closeBracketCount = std::count(varTokenStr.begin(), varTokenStr.end(), ']');
		
		if (openBracketCount > closeBracketCount)
		{
			dotPos = quoteReplacementStr.find(L".", dotPos + 1);
		}
		else
		{
			varTokenList.push_back(getForBracket(varTokenStr));
			dotPosOffset = dotPos + 1;
			
			dotPos = quoteReplacementStr.find(L".", dotPos + 1);
		}
	}

	varTokenList.push_back(getForBracket(quoteReplacementStr.substr(dotPosOffset, quoteReplacementStr.length())));

	int lastVarIndex = 0;
	int  currVarIndex;
	Var* lastVar = nullptr;

	for (std::vector<std::wstring>::iterator currVarStr = varTokenList.begin();
		currVarStr != varTokenList.end(); ++currVarStr) 
	{
		if (lastVar != nullptr)
		{
			currVar = nullptr;
		}
		else
		{
			currVar = getSimpleWithIndex(*currVarStr, currVarIndex);
		}

		if (currVar != nullptr)
		{
			switch (currVar->type)
			{
			case TYPE_INT:
			{
				int* pstr = static_cast<int*>(currVar->data);
				lastVarIndex = pstr[currVarIndex];
				index = currVarIndex;

				break;
			}
			case TYPE_LONG:
			{
				long long int* pstr = static_cast<long long int*>(currVar->data);
				lastVarIndex = pstr[currVarIndex];
				index = currVarIndex;

				break;
			}
			case TYPE_STRING:
			{
				index = currVarIndex;

				break;
			}
			case TYPE_DOUBLE:
			{
				index = currVarIndex;

				break;
			}
			case TYPE_OBJECT:
			{
				if (lastVar == nullptr)
				{
					lastVar = currVar;
					index = currVarIndex;
					lastVarIndex = index;
				}
				else
				{
					ObjectStore** var = static_cast<ObjectStore**>(lastVar->data);
					ObjectStore* obj = var[currVarIndex];
					index = currVarIndex;

					lastVar = obj->getVar(*currVarStr, lastVarIndex);
				}

				break;
			}
			}
		}
		else if (lastVar != nullptr)
		{
			ObjectStore** var = static_cast<ObjectStore**>(lastVar->data);
			ObjectStore* obj = var[lastVarIndex];

			lastVar = obj->getVar(*currVarStr, lastVarIndex);
			currVar = lastVar;
			index = lastVarIndex;
		}
	}

	return currVar;
}

Var* VarStore::getVar(const std::wstring &name, int &val)
{
	if (name[0] == '"')
	{
		val = 0;

		return nullptr;
	}

	if (is_digits(name) == true)
	{
		val = 0;

		return nullptr;
	}

	Var* v = getVar2(name, val);
	
	return v;
}

#endif
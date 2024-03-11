
#ifndef VAR_STORE_CPP
#define VAR_STORE_CPP

#include <regex>

#include "VarStore.h"
#include "WorkspaceStore.h"
#include "ObjectStore.h"

const std::regex FLOAT_REGEX("[+-]?([0-9]*[.])?[0-9]+");

bool is_digits(const std::string& str)
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
	for (auto it = mVars.begin(); it != mVars.end(); ++it)
	{
		it = mVars.erase(it);
	}
}

void VarStore::print() {
	for (auto it = mVars.begin(); it != mVars.end(); ++it)
	{
		std::cout << it->second->name << std::endl;
	}
}

void VarStore::addVar(const std::string &name, const ReservedWord &type)
{
	mVars.insert({ name, new Var(name, type) });
}

void VarStore::addVar(Var* var)
{
	mVars.insert({ var->name, var });
}

int VarStore::removeVar(const std::string &name)
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

		return mVars.erase(name);
	}

	return 0; // false
}

void VarStore::addVar(const std::string name, const ReservedWord type, const int size)
{
	Var* v = new Var(name, type, size);
	mVars.insert({ name, v });
}

void VarStore::addVarAlias(const std::string toAliasName, const std::string aliasName)
{
	int index;
	Var* toAliasVar = getVar(toAliasName, index);
	Var* v = new Var(aliasName, toAliasVar[index].type, toAliasVar[index].size, toAliasVar);
	mVars.insert({ aliasName, v });
}

void VarStore::addVarAliasWithPointer(Var* toAliasVar, int &varIndex, const std::string aliasName)
{
	Var* v = new Var(aliasName, toAliasVar[varIndex].type, toAliasVar[varIndex].size, toAliasVar);
	mVars.insert({ aliasName, v });
}

void VarStore::reassignVar(Var* toReassign, Var* newVar, std::set<long long> &deletedDataSet)
{
	long long ref = reinterpret_cast<long long>(toReassign->data);

	if (deletedDataSet.count(ref) == 0) {
		toReassign->deleteData();
	} else {
		deletedDataSet.erase(ref);
	}

	toReassign->data = newVar->data;
	toReassign->size = newVar->size;

	deletedDataSet.insert(ref);
}

Var* VarStore::addVarWithReference(const std::string name, const ReservedWord type, const int size)
{
	Var* v = new Var(name, type, size);
	mVars.insert({ name, v });

	return v;
}

Var* VarStore::getSimpleWithIndex(const std::string& var, int& index)
{
	int pos = var.find("[");

	if (pos == std::string::npos) 
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
		std::string idx = var.substr(pos + 1, var.find("]") - pos - 1);
		index = std::stoi(idx);

		std::string varName = var.substr(0, pos);

		auto search = mVars.find(varName);

		if (search != mVars.end())
		{
			return search->second;
		}

		return nullptr;
	}
}

std::string VarStore::getForBracket(const std::string& var, bool getReplacement)
{
	int openBracketPos = var.find("[");
	int closeBracketPos;
	std::string varNameSimple;
	std::string bracketStrContents;
	std::string origVarStrCopy = var;
	std::vector<std::string> varStrList;
	std::vector<std::string> indexStrList;

	while (openBracketPos != std::string::npos)
	{
		varNameSimple = origVarStrCopy.substr(0, openBracketPos);
		varStrList.insert(varStrList.begin(), varNameSimple);

		closeBracketPos = origVarStrCopy.find_last_of("]");
		bracketStrContents = origVarStrCopy.substr(openBracketPos + 1, closeBracketPos - openBracketPos - 1);

		origVarStrCopy = bracketStrContents;

		openBracketPos = bracketStrContents.find("[");
	}

	indexStrList.push_back(bracketStrContents);

	int lastIndex = 0;
	std::string lastVarStr = var;
	Var* currVar = nullptr;
	int currIndex = 0;

	while (varStrList.empty() == false)
	{
		std::string indexStr = indexStrList.front();

		int dotPos = indexStr.find(".");

		if (dotPos != std::string::npos)
		{
			int openBracketIndex = var.find("[");
			int closeBracketIndex = var.find("]");
			std::string bracketContentStr = var.substr(openBracketIndex + 1, closeBracketIndex - openBracketIndex - 1);

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

			std::string var = varStrList.front();
			varStrList.erase(varStrList.begin());

			lastVarStr = var;

			var += "[" + std::to_string(currIndex) + "]";

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

			std::string var = varStrList.front();
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

		std::string* pstr = static_cast<std::string*>(currVar->data);
		lastVarStr = pstr[0];
	}

	return lastVarStr + "[" + std::to_string(currIndex) + "]";
}

std::string VarStore::getForBracket(const std::string& var)
{
	int openBracketPos = var.find("[");
	int closeBracketPos;
	std::string varNameSimple;
	std::string bracketStrContents;
	std::string origVarStrCopy = var;
	std::vector<std::string> varStrList;
	std::vector<std::string> indexStrList;

	while (openBracketPos != std::string::npos) 
	{
		varNameSimple = origVarStrCopy.substr(0, openBracketPos);
		varStrList.insert(varStrList.begin(), varNameSimple);

		closeBracketPos = origVarStrCopy.find_last_of("]");
		bracketStrContents = origVarStrCopy.substr(openBracketPos + 1, closeBracketPos - openBracketPos - 1);

		origVarStrCopy = bracketStrContents;

		openBracketPos = bracketStrContents.find("[");
	}

	indexStrList.push_back(bracketStrContents);

	int lastIndex = 0;
	std::string lastVarStr = var;
	Var* currVar = nullptr;
	int currIndex = 0;

	while (varStrList.empty() == false) 
	{
		std::string indexStr = indexStrList.front();

		int dotPos = indexStr.find(".");

		if (dotPos != std::string::npos)
		{
			int openBracketIndex = var.find("[");
			int closeBracketIndex = var.find("]");
			std::string bracketContentStr = var.substr(openBracketIndex + 1, closeBracketIndex - openBracketIndex - 1);

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

			std::string var = varStrList.front();
			varStrList.erase(varStrList.begin());

			lastVarStr = var;

			var += "[" + std::to_string(currIndex) + "]";

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

			std::string var = varStrList.front();
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
				indexStrList.push_back(std::to_string(pstr[currIndex]));
				lastIndex = currIndex;

				break;
			}
			case TYPE_LONG:
			{
				long long int* pstr = static_cast<long long int*>(currVar->data);
				indexStrList.push_back(std::to_string(pstr[currIndex]));
				lastIndex = currIndex;

				break;
			}
			}
		}
	}

	return lastVarStr + "[" + std::to_string(lastIndex) + "]";
}

bool is_number(const std::string& s) {
	return std::regex_match(s, FLOAT_REGEX);
}

Var* VarStore::getVar2(const std::string& name, int& index)
{
	index = 0;

	std::string::size_type singleQuoteIndex = name.find("'");
	int secondQuoteIndex;
	bool hasSingleQuote = false;
	std::string quoteReplacementStr, quotedStr;
	int quoteReplaceStartIndex = 0;

	while (singleQuoteIndex != std::string::npos)
	{
		hasSingleQuote = true;

		quoteReplacementStr += name.substr(quoteReplaceStartIndex, singleQuoteIndex - quoteReplaceStartIndex);
		secondQuoteIndex = name.find("'", singleQuoteIndex + 1);

		quotedStr = name.substr(singleQuoteIndex + 1, secondQuoteIndex - singleQuoteIndex - 1);

		quoteReplacementStr += getForBracket(quotedStr, true);

		singleQuoteIndex = name.find("'", secondQuoteIndex + 1);
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

	std::string doubleBracketTemp;
	int doubleBracketsIndex;

	while (quoteReplacementStr.find("][") != std::string::npos)
	{
		doubleBracketTemp = quoteReplacementStr.substr(0, quoteReplacementStr.find("]["));
		doubleBracketsIndex = quoteReplacementStr.find("][");
		
		quoteReplacementStr = quoteReplacementStr.substr(doubleBracketsIndex + 1, quoteReplacementStr.length() - doubleBracketsIndex);
		
		while (doubleBracketTemp[doubleBracketTemp.length() - 1] != '[') 
		{
			doubleBracketTemp.pop_back();
		}
		doubleBracketTemp.pop_back();

		quoteReplacementStr = doubleBracketTemp + quoteReplacementStr;
	}

	std::vector<std::string> varTokenList;
	std::string varTokenStr;
	int dotPos = quoteReplacementStr.find(".");
	int dotPosOffset = 0;
	size_t openBracketCount, closeBracketCount;
	Var* currVar = nullptr;

	while (dotPos != std::string::npos)
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
			dotPos = quoteReplacementStr.find(".", dotPos + 1);
		}
		else
		{
			varTokenList.push_back(getForBracket(varTokenStr));
			dotPosOffset = dotPos + 1;
			
			dotPos = quoteReplacementStr.find(".", dotPos + 1);
		}
	}

	varTokenList.push_back(getForBracket(quoteReplacementStr.substr(dotPosOffset, quoteReplacementStr.length())));

	int lastVarIndex = 0;
	int  currVarIndex;
	Var* lastVar = nullptr;

	for (std::vector<std::string>::iterator currVarStr = varTokenList.begin();
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
		else
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

Var* VarStore::getVar(const std::string &name, int &val)
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
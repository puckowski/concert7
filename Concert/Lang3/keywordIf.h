
#ifndef KEYWORD_IF_H
#define KEYWORD_IF_H

#include <vector>
#include <string>

#include "operatorFunctions.h"

void executeKeywordIf(std::vector<std::wstring> &tokens)
{
	conditionalStack.push(-1);

	int r1, r2;
	int nestedEnd = 0;
	bool createdLhs = false;
	bool createdRhs = false;
	Var* lhsVar = getVar(tokens[1], r1, createdLhs);
	Var* rhsVar = getVar(tokens[3], r2, createdRhs);

	std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<const std::wstring, const Operator>>>> opCheck = OPERATOR_MAP.find(tokens[2]);
	Operator op = opCheck->second;

	switch (op) {
		case OPERATOR_EQUALS: {
			if (execEqualsOperator(lhsVar, r1, rhsVar, r2))
			{
				//
				conditionalStack.push(-2);
			}
			else
			{
				do
				{
					currentLine++;
					
					tokens = codeStore->gStatements[currentLine];

					if (tokens.empty())
					{
						continue;
					}

					if (tokens[0] == L"if") {
						nestedEnd++;
						//conditionalStack.push(-1);
					}
					else if (tokens[0] == L"try")
						nestedEnd++;
					else if (tokens[0] == L"while")
						nestedEnd++;
					else if (tokens[0] == L"else") {
						if (nestedEnd > 0)
							nestedEnd--;
						else {
							currentLine--;
							break;
						}
					}
					else if (tokens[0] == L"end") {
						if (nestedEnd > 0) 
							nestedEnd--;
						else {
							currentLine--;
							break;
						}
					}
				} while (true);
			}

			break;
		}
		case OPERATOR_NOT_EQUALS: {
			if (execNotEqualsOperator(lhsVar, r1, rhsVar, r2))
			{
				//
				conditionalStack.push(-2);
			}
			else
			{
				do
				{
					currentLine++;

					tokens = codeStore->gStatements[currentLine];

					if (tokens.empty())
					{
						continue;
					}

					if (tokens[0] == L"if") {
						nestedEnd++;
						//conditionalStack.push(-1);
					}
					else if (tokens[0] == L"try")
						nestedEnd++;
					else if (tokens[0] == L"while")
						nestedEnd++;
					else if (tokens[0] == L"else") {
						if (nestedEnd > 0)
							nestedEnd--;
						else {
							currentLine--;
							break;
						}
					}
					else if (tokens[0] == L"end") {
						if (nestedEnd > 0)
							nestedEnd--;
						else {
							currentLine--;
							break;
						}
					}
				} while (true);
			}

			break;
		}
		case OPERATOR_LESS_THAN: {
			if (execLessThanOperator(lhsVar, r1, rhsVar, r2))
			{
				//
				conditionalStack.push(-2);
			}
			else
			{
				do
				{
					currentLine++;

					tokens = codeStore->gStatements[currentLine];

					if (tokens.empty())
					{
						continue;
					}

					if (tokens[0] == L"if") {
						nestedEnd++;
						//conditionalStack.push(-1);
					}
					else if (tokens[0] == L"try")
						nestedEnd++;
					else if (tokens[0] == L"while")
						nestedEnd++;
					else if (tokens[0] == L"else") {
						if (nestedEnd > 0)
							nestedEnd--;
						else {
							currentLine--;
							break;
						}
					}
					else if (tokens[0] == L"end") {
						if (nestedEnd > 0)
							nestedEnd--;
						else {
							currentLine--;
							break;
						}
					}
				} while (true);
			}

			break;
		}
		case OPERATOR_GREATER_THAN: {
			if (execGreaterThanOperator(lhsVar, r1, rhsVar, r2))
			{
				//
				conditionalStack.push(-2);
			}
			else
			{
				do
				{
					currentLine++;

					tokens = codeStore->gStatements[currentLine];

					if (tokens.empty())
					{
						continue;
					}

					if (tokens[0] == L"if") {
						nestedEnd++;
						//conditionalStack.push(-1);
					}
					else if (tokens[0] == L"try")
						nestedEnd++;
					else if (tokens[0] == L"while")
						nestedEnd++;
					else if (tokens[0] == L"else") {
						if (nestedEnd > 0)
							nestedEnd--;
						else {
							currentLine--;
							break;
						}
					}
					else if (tokens[0] == L"end") {
						if (nestedEnd > 0)
							nestedEnd--;
						else {
							currentLine--;
							break;
						}
					}
				} while (true);
			}

			break;
		}
		case OPERATOR_LESS_THAN_EQUALS: {
			if (execLessThanOrEqualsOperator(lhsVar, r1, rhsVar, r2))
			{
				//
				conditionalStack.push(-2);
			}
			else
			{
				do
				{
					currentLine++;

					tokens = codeStore->gStatements[currentLine];

					if (tokens.empty())
					{
						continue;
					}

					if (tokens[0] == L"if") {
						nestedEnd++;
						//conditionalStack.push(-1);
					}
					else if (tokens[0] == L"try")
						nestedEnd++;
					else if (tokens[0] == L"while")
						nestedEnd++;
					else if (tokens[0] == L"else") {
						if (nestedEnd > 0)
							nestedEnd--;
						else {
							currentLine--;
							break;
						}
					}
					else if (tokens[0] == L"end") {
						if (nestedEnd > 0)
							nestedEnd--;
						else {
							currentLine--;
							break;
						}
					}
				} while (true);
			}

			break;
		}
		case OPERATOR_GREATER_THAN_EQUALS: {
			if (execGreaterThanOrEqualsOperator(lhsVar, r1, rhsVar, r2))
			{
				//
				conditionalStack.push(-2);
			}
			else
			{
				do
				{
					currentLine++;

					tokens = codeStore->gStatements[currentLine];

					if (tokens.empty())
					{
						continue;
					}

					if (tokens[0] == L"if") {
						nestedEnd++;
						//conditionalStack.push(-1);
					}
					else if (tokens[0] == L"try")
						nestedEnd++;
					else if (tokens[0] == L"while")
						nestedEnd++;
					else if (tokens[0] == L"else") {
						if (nestedEnd > 0)
							nestedEnd--;
						else {
							currentLine--;
							break;
						}
					}
					else if (tokens[0] == L"end") {
						if (nestedEnd > 0)
							nestedEnd--;
						else {
							currentLine--;
							break;
						}
					}
				} while (true);
			}

			break;
		}
	}

	if (createdLhs)
	{
		delete lhsVar;
		lhsVar = nullptr;
	}

	if (createdRhs)
	{
		delete rhsVar;
		rhsVar = nullptr;
	}
}

#endif
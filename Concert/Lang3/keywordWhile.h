
#ifndef KEYWORD_WHILE_H
#define KEYWORD_WHILE_H

#include <vector>
#include <string>

#include "reservedWord.h"
#include "operatorFunctions.h"

void executeKeywordWhile(std::vector<std::string> &tokens)
{
	int r1, r2;
	int nestedEnd = 0;
	bool createdLhs = false;
	bool createdRhs = false;
	Var* lhsVar = getVar(tokens[1], r1, createdLhs);
	Var* rhsVar = getVar(tokens[3], r2, createdRhs);

	std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<const std::string, const Operator>>>> opCheck = OPERATOR_MAP.find(tokens[2]);
	Operator op = opCheck->second;

	switch (op) {
		case OPERATOR_EQUALS: {
			if (execEqualsOperator(lhsVar, r1, rhsVar, r2))
			{
				conditionalStack.push(currentLine);
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

					if (tokens[0] == "if")
						nestedEnd++;
					else if (tokens[0] == "try")
						nestedEnd++;
					else if (tokens[0] == "while")
						nestedEnd++;
					else if (tokens[0] == "end") {
						//currentLine--;

						if (nestedEnd > 0)
							nestedEnd--;
						else
							break;
					}
				} while (true);
			}

			break;
		}
		case OPERATOR_NOT_EQUALS: {
			if (execNotEqualsOperator(lhsVar, r1, rhsVar, r2))
			{
				conditionalStack.push(currentLine);
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

					if (tokens[0] == "if")
						nestedEnd++;
					else if (tokens[0] == "try")
						nestedEnd++;
					else if (tokens[0] == "while")
						nestedEnd++;
					else if (tokens[0] == "end") {
						//currentLine--;

						if (nestedEnd > 0)
							nestedEnd--;
						else
							break;
					}
				} while (true);
			}

			break;
		}
		case OPERATOR_LESS_THAN: {
			if (execLessThanOperator(lhsVar, r1, rhsVar, r2))
			{
				conditionalStack.push(currentLine);
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

					if (tokens[0] == "if")
						nestedEnd++;
					else if (tokens[0] == "try")
						nestedEnd++;
					else if (tokens[0] == "while")
						nestedEnd++;
					else if (tokens[0] == "end") {
						//currentLine--;

						if (nestedEnd > 0)
							nestedEnd--;
						else
							break;
					}
				} while (true);
			}

			break;
		}
		case OPERATOR_GREATER_THAN: {
			if (execGreaterThanOperator(lhsVar, r1, rhsVar, r2))
			{
				conditionalStack.push(currentLine);
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

					if (tokens[0] == "if")
						nestedEnd++;
					else if (tokens[0] == "try")
						nestedEnd++;
					else if (tokens[0] == "while")
						nestedEnd++;
					else if (tokens[0] == "end") {
						//currentLine--;

						if (nestedEnd > 0)
							nestedEnd--;
						else
							break;
					}
				} while (true);
			}

			break;
		}
		case OPERATOR_LESS_THAN_EQUALS: {
			if (execLessThanOrEqualsOperator(lhsVar, r1, rhsVar, r2))
			{
				conditionalStack.push(currentLine);
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

					if (tokens[0] == "if")
						nestedEnd++;
					else if (tokens[0] == "try")
						nestedEnd++;
					else if (tokens[0] == "while")
						nestedEnd++;
					else if (tokens[0] == "end") {
						//currentLine--;

						if (nestedEnd > 0)
							nestedEnd--;
						else
							break;
					}
				} while (true);
			}

			break;
		}
		case OPERATOR_GREATER_THAN_EQUALS: {
			if (execGreaterThanOrEqualsOperator(lhsVar, r1, rhsVar, r2))
			{
				conditionalStack.push(currentLine);
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

					if (tokens[0] == "if")
						nestedEnd++;
					else if (tokens[0] == "try")
						nestedEnd++;
					else if (tokens[0] == "while")
						nestedEnd++;
					else if (tokens[0] == "end") {
						//currentLine--;

						if (nestedEnd > 0)
							nestedEnd--;
						else
							break;
					}
				} while (true);
			}

			break;
		}
	}

	if (createdLhs)
	{
		delete lhsVar;
	}

	if (createdRhs)
	{
		delete rhsVar;
	}
}

#endif
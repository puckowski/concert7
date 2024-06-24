
#ifndef KEYWORD_FUNCTION_H
#define KEYWORD_FUNCTION_H

#include <string>
#include <vector>

#include "Var.h"
#include "variableFunctions.h"
#include "operatorFunctions.h"
#include "sourceFunctions.h"

void executeKeywordFunction(const int &tokensSize, std::vector<std::wstring> &tokens)
{
	if (getFunctionLineFromMap(tokens[1]) == -1)
	{
		addFunctionToMap(tokens[1], currentLine);
		int funcCount = 0;

		do
		{
			currentLine++;

			tokens = codeStore->gStatements[currentLine];

			if (tokens.empty())
			{
				continue;
			}

			if (tokens[0] == L"return" && funcCount == 0)
				break;
			else if (tokens[0] == L"return")
				funcCount--;
			else if (tokens[0] == L"function")
				funcCount++;
		} while (true);
	}
	else
	{
		Var* v = nullptr;
		int r1;
		bool createdV = false;

		for (int i = 2; i < tokensSize; ++i)
		{
			if (tokens[i] == L"using") 
			{
				bool createdVar = false;
				i++;
				Var* var = lastWorkspace->getVar(tokens[i], r1);

				gWorkspaceStore->getStore()->addVar(var);
				var->reassignCount++;

				//callStack.pop_back();
				callStack.erase(callStack.begin());
			}
			else
			{
				auto type = RESERVED_WORD_IDENTIFIER_MAP.find(tokens[i]);
			
				if (type != RESERVED_WORD_IDENTIFIER_MAP.end())
				{
					v = getVarFromLastWorkspace(callStack.front(), type->second, r1, createdV);
				}
				else
				{
					v = getVarFromLastWorkspace(callStack.front(), r1, createdV);
				}

				callStack.erase(callStack.begin());

				if (tokens[i + 2] == L"&")
				{
					i += 3;

					gWorkspaceStore->getStore()->addVarAliasWithPointer(v, r1, tokens[i]);
				}
				else
				{
					i += 2;

					Var* v2 = gWorkspaceStore->getStore()->addVarWithReference(tokens[i], v->type, v->size);
					//Var* v2 = gWorkspaceStore->getStore()->getVar(tokens[i], r1);

					for (int n = 0; n < v->size; ++n)
					{
						execAssignOperator(v2, n, v, n);
					}
				}

				if (createdV)
					delete v;
			}
		}
	}
}

#endif

#ifndef KEYWORD_JOIN_H
#define KEYWORD_JOIN_H

#include <vector>
#include <string>

void executeKeywordJoin(const int &tokensSize, std::vector<std::wstring> &tokens)
{
	CodeStore* newCodeStore = new CodeStore();
	readStatementsIntoNewCodeStore2(currentLine, codeStore, newCodeStore);

	WorkspaceStore* ws = new WorkspaceStore();
	ws->addGlobalStoreWithoutStackEntry(new VarStore());

	for (int i = 2; i < tokensSize; ++i)
	{
		callStack.push_back(tokens[i]);
	}

	tokens[0] = L"call";
	newCodeStore->gStatements.push_back(tokens);

	std::vector<std::wstring> tokens2 = codeStore->gStatements[getFunctionLineFromMap(tokens[1])];
	int tokensSize2 = tokens2.size();

	Var* v = nullptr;
	int r1;
	bool createdV = false;

	for (int i = 2; i < tokensSize2; ++i)
	{
		if (tokens2[i] == L"using") 
		{
			i++;
			Var* var = getVar(tokens[i - 1], r1); 

			ws->getStore()->addVar(var);
			var->reassignCount++;

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

				ws->getStore()->addVar(tokens[i], v->type, v->size);
				Var* v2 = ws->getStore()->getVar(tokens[i], r1);

				for (int n = 0; n < v->size; ++n)
				{
					execAssignOperator(v2, n, v, n);
				}
			}

			if (createdV)
			{
				delete v;
			}
		}
	}

	bool b = true;
	int linetmp = 0;
	std::thread t(exec, std::ref(linetmp), b, newCodeStore, ws, 0, 0);
	t.join();
}

#endif

#ifndef KEYWORD_JOIN_H
#define KEYWORD_JOIN_H

#include <vector>
#include <string>

void executeKeywordJoin(const int &tokensSize, std::vector<std::string> &tokens)
{
	CodeStore* newCodeStore = new CodeStore();
	readStatementsIntoNewCodeStore2(currentLine, codeStore, newCodeStore);

	WorkspaceStore* ws = new WorkspaceStore();
	ws->addGlobalStoreWithoutStackEntry(new VarStore());

	for (int i = 2; i < tokensSize; ++i)
	{
		callStack.push_back(tokens[i]);
	}

	tokens[0] = "call";
	newCodeStore->gStatements.push_back(tokens);

	std::vector<std::string> tokens2 = codeStore->gStatements[getFunctionLineFromMap(tokens[1])];
	int tokensSize2 = tokens2.size();

	Var* v = nullptr;
	int r1;
	bool createdV = false;

	for (int i = 2; i < tokensSize2; ++i)
	{
		if (tokens2[i] == "using") 
		{
			i++;
			Var* var = getVar(tokens[i - 1], r1); 

			ws->getStore()->addVar(var);

			callStack.erase(callStack.begin());
		}
		else
		{
			auto type = RESERVED_WORD_IDENTIFIER_MAP.find(tokens[i]);

			v = getVarFromLastWorkspace(callStack.front(), type->second, r1, createdV);
			callStack.erase(callStack.begin());

			i += 2;

			ws->getStore()->addVar(tokens[i], v->type, v->size);
			Var* v2 = ws->getStore()->getVar(tokens[i], r1);

			for (int n = 0; n < v->size; ++n)
			{
				execAssignOperator(v2, n, v, n);
			}

			if (createdV)
			{
				delete v;
			}
		}
	}

	bool b = true;
	int linetmp = 0;
	std::thread t(exec, std::ref(linetmp), b, newCodeStore, ws, 0);
	t.join();
}

#endif

#ifndef KEYWORD_EXEC_H
#define KEYWORD_EXEC_H

#include <vector>
#include <string>

#include "interpreter.h"
#include "sourceFunctions.h"

void executeKeywordExec(std::vector<std::string> &tokens)
{
	bool created = false;
	int r1;
	Var* v = getVar(tokens[1], r1, created);

	std::string code;

	if (v != nullptr)
	{
		std::string* pstr = static_cast<std::string*>(v->data);
		code = pstr[r1].c_str();
	}
	else
	{
		code = tokens[1];
	}

	int jumpToLine = codeStore->gStatements.size();

	std::vector<std::string> tokens2;
	tokenizeStatement3(code, tokens2, codeStore);

	int oldCurrentLine = currentLine;

	bool newThreadFlag = false;
	exec(jumpToLine, newThreadFlag, codeStore, gWorkspaceStore, 0);

	currentLine = oldCurrentLine;

	statementCount = codeStore->gStatements.size();

	if (created)
	{
		delete v;
	}
}

#endif
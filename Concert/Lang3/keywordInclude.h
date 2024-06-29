
#ifndef KEYWORD_INCLUDE_H
#define KEYWORD_INCLUDE_H

#include <vector>
#include <string>

#include "interpreter.h"
#include "CodeStore.h"
#include "sourceFunctions.h"
#include "interpreter.h"

void executeKeywordInclude(std::vector<std::wstring> &tokens, int &currentLine)
{
	int oldCurrentLine = currentLine;
	int endOfCode = codeStore->gStatements.size();
	
	if (tokens[1].size() > 1) {
		if (tokens[1].front() == '"' && tokens[1].back() == '"') {
			if (tokens[1].size() == 2) {
				tokens[1].erase();
			}
			else {
				tokens[1].erase(tokens[1].begin());
				tokens[1].erase(tokens[1].end() - 1);
			}
		}
	}

	readStatementsFromFile(tokens[1], codeStore);

	bool newThreadFlag = false;
	exec(endOfCode, newThreadFlag, codeStore, gWorkspaceStore, 0, 0);

	currentLine = oldCurrentLine;
}

#endif
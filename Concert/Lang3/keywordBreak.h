
#ifndef KEYWORD_BREAK_H
#define KEYWORD_BREAK_H

#include <string>
#include <vector>

#include "sourceFunctions.h"

void executeKeywordBreak(int &currentLine, std::vector<std::string> &tokens)
{
	int blockCount = 0;

	while (conditionalStack.top() < 0)
	{
		conditionalStack.pop();
	}

	currentLine = conditionalStack.top();

	do
	{
		currentLine++;

		tokens = codeStore->gStatements[currentLine];

		if (tokens[0] == "end" && blockCount == 0) {
			//currentLine--;
			conditionalStack.pop();

			break;
		}
		else if (tokens[0] == "end")
			blockCount--;
		else if (tokens[0] == "if")
			blockCount++;
		else if (tokens[0] == "try")
			blockCount++;
		else if (tokens[0] == "while")
			blockCount++;
	} while (true);
}

#endif
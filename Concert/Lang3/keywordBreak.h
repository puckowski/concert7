
#ifndef KEYWORD_BREAK_H
#define KEYWORD_BREAK_H

#include <string>
#include <vector>

#include "sourceFunctions.h"

void executeKeywordBreak(int &currentLine, std::vector<std::wstring> &tokens)
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

		if (tokens[0] == L"end" && blockCount == 0) {
			//currentLine--;
			conditionalStack.pop();

			break;
		}
		else if (tokens[0] == L"end")
			blockCount--;
		else if (tokens[0] == L"if")
			blockCount++;
		else if (tokens[0] == L"try")
			blockCount++;
		else if (tokens[0] == L"while")
			blockCount++;
	} while (true);
}

#endif
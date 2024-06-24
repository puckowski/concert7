
#ifndef KEYWORD_ELSE_H
#define KEYWORD_ELSE_H

#include "sourceFunctions.h"

void executeKeywordElse(const int &tokensSize, std::vector<std::wstring> &tokens, int &currentLine)
{
	if (conditionalStack.top() == -2) {
		int nestedEnd = 0;

		do
		{
			currentLine++;

			tokens = codeStore->gStatements[currentLine];

			if (tokens.empty())
			{
				continue;
			}

			if (tokens[0] == L"if")
				nestedEnd++;
			else if (tokens[0] == L"try")
				nestedEnd++;
			else if (tokens[0] == L"while")
				nestedEnd++;
			else if (tokens[0] == L"else") {
				if (nestedEnd > 0)
					nestedEnd--;
				else
					break;
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

		conditionalStack.pop();
	}
}

#endif
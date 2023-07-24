
#ifndef KEYWORD_ELSE_H
#define KEYWORD_ELSE_H

#include "sourceFunctions.h"

void executeKeywordElse(const int &tokensSize, std::vector<std::string> &tokens, int &currentLine)
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

			if (tokens[0] == "if")
				nestedEnd++;
			else if (tokens[0] == "try")
				nestedEnd++;
			else if (tokens[0] == "while")
				nestedEnd++;
			else if (tokens[0] == "else") {
				if (nestedEnd > 0)
					nestedEnd--;
				else
					break;
			}
			else if (tokens[0] == "end") {
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
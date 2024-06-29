
#ifndef KEYWORD_CATCH_H
#define KEYWORD_CATCH_H

#include <vector>
#include <string>
#include <exception>
#include <typeinfo>
#include <stdexcept>
#include <iostream>

#include "sourceFunctions.h"

void executeKeywordCatch(int& currentLine, std::vector<std::wstring>& tokens)
{
	if (tryBlockCount > 0)
	{
		do
		{
			currentLine++;
			int blockCount = 0;

			tokens = codeStore->gStatements[currentLine];

			if (tokens.empty())
			{
				continue;
			}

			if (tokens[0] == L"end" && blockCount == 0)
				break;
			else if (tokens[0] == L"end")
				blockCount--;
			else if (tokens[0] == L"if")
				blockCount++;
			else if (tokens[0] == L"try")
				blockCount++;
			else if (tokens[0] == L"while")
				blockCount++;
		} while (true);

		currentLine++;
		tryBlockCount--;
		std::cout << currentLine << " " << tryBlockCount << std::endl;
	}
}

#endif
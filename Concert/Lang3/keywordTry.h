
#ifndef KEYWORD_TRY_H
#define KEYWORD_TRY_H

#include <vector>
#include <string>
#include <exception>
#include <typeinfo>
#include <stdexcept>
#include <iostream>

#include "sourceFunctions.h"

void executeKeywordTry(int &currentLine, std::vector<std::wstring> &tokens)
{
	currentLine++;

	try
	{
		exec(currentLine, false, nullptr, nullptr, 0, 1);
	}
	catch (...)
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

			if (tokens[0] == L"catch" && blockCount == 0)
				break;
			else if (tokens[0] == L"catch")
				blockCount--;
			else if (tokens[0] == L"try")
				blockCount++;
		} while (true);

		return;
	}

	int blockCount = 0;

	do
	{
		currentLine++;

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

	currentLine--;
}

#endif
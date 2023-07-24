
#ifndef KEYWORD_TRY_H
#define KEYWORD_TRY_H

#include <vector>
#include <string>
#include <exception>
#include <typeinfo>
#include <stdexcept>
#include <iostream>

#include "sourceFunctions.h"

void executeKeywordTry(int &currentLine, std::vector<std::string> &tokens)
{
	currentLine++;

	try
	{
		exec(currentLine);
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

			if (tokens[0] == "catch" && blockCount == 0)
				break;
			else if (tokens[0] == "catch")
				blockCount--;
			else if (tokens[0] == "try")
				blockCount++;
		} while (true);

		return;
	}

	do
	{
		currentLine++;
		int blockCount = 0;

		tokens = codeStore->gStatements[currentLine];

		if (tokens.empty())
		{
			continue;
		}

		if (tokens[0] == "end" && blockCount == 0)
			break;
		else if (tokens[0] == "end")
			blockCount--;
		else if (tokens[0] == "if")
			blockCount++;
		else if (tokens[0] == "try")
			blockCount++;
		else if (tokens[0] == "while")
			blockCount++;
	} while (true);

	currentLine--;
}

#endif
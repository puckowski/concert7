
#ifndef KEYWORD_CONTINUE_H
#define KEYWORD_CONTINUE_H

#include <string>
#include <vector>

#include "sourceFunctions.h"

void executeKeywordContinue(int &currentLine, std::vector<std::string> &tokens)
{
	int blockCount = 0;

	while (conditionalStack.top() < 0)
	{
		conditionalStack.pop();
	}

	currentLine = conditionalStack.top();
	currentLine--;

	conditionalStack.pop();
}

#endif

#ifndef KEYWORD_END_H
#define KEYWORD_END_H

#include "sourceFunctions.h"

void executeKeywordEnd(int &currentLine)
{
	if (conditionalStack.empty() == false) 
	{
		int topOfStack = conditionalStack.top();

		if (topOfStack >= 0) // WHILE
		{
			currentLine = conditionalStack.top();
			currentLine--;
		}
		else if (topOfStack == -2) // IF
		{
			conditionalStack.pop();
		}

		conditionalStack.pop();
	}
}

#endif

#ifndef KEYWORD_UNLOCK_H
#define KEYWORD_UNLOCK_H

#include <vector>
#include <string>

#include "sourceFunctions.h"
#include "mutexFunctions.h"

void executeKeywordUnlock(std::vector<std::string> &tokens)
{
	std::mutex* mtx = getMutex(tokens[1]);

	mtx->unlock();
}

#endif
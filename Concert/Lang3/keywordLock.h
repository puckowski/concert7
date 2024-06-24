
#ifndef KEYWORD_LOCK_H
#define KEYWORD_LOCK_H

#include <vector>
#include <string>

#include "sourceFunctions.h"
#include "mutexFunctions.h"

void executeKeywordLock(std::vector<std::wstring> &tokens)
{
	std::mutex* mtx = getMutex(tokens[1]);

	mtx->lock();
}

#endif
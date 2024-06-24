
#ifndef MUTEX_FUNCTIONS_H
#define MUTEX_FUNCTIONS_H

#include <string>
#include <mutex>

#include "sourceFunctions.h"

std::mutex* getMutex(const std::wstring &name)
{
	auto search = lockMap.find(name);

	if (search != lockMap.end())
	{
		return search->second;
	}

	return nullptr;
}

void createMutex(const std::wstring &name)
{
	lockMap.insert({ name, new std::mutex() });
}

#endif
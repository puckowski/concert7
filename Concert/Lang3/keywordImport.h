
#ifndef KEYWORD_IMPORT_H
#define KEYWORD_IMPORT_H

#include <vector>
#include <string>

#include "standardLibrary.h"

void executeKeywordImport(const int &tokensSize, std::vector<std::string> &tokens)
{
	for (int i = 1; i < tokensSize; ++i)
	{
		const std::vector<std::string>* funcs = LIBRARY_IMPORT_MAP.find(tokens[i])->second;

		for (const std::string &function : *funcs)
		{
			mLibraryMap.insert({ function, LIBRARY_FUNCTION_MAP.find(function)->second });
		}
	}
}

#endif
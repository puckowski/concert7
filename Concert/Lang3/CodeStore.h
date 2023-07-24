
#ifndef CODE_STORE_H
#define CODE_STORE_H

#include <vector>
#include <string>

class CodeStore
{
private:

public:
	std::vector<std::vector<std::string>> gStatements;

	CodeStore();

	~CodeStore();
};

#endif
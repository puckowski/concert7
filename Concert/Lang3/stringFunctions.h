
#ifndef STRING_FUNCTIONS_H
#define STRING_FUNCTIONS_H

#include <string>

const std::string NEWLINE_STRING = std::string("\n");

void findAndReplace(std::string& source, std::string const& find, std::string const& replace)
{
	for (std::string::size_type i = 0; (i = source.find(find, i)) != std::string::npos;)
	{
		source.replace(i, find.length(), replace);
		i += replace.length();
	}
}

void findAndReplaceNewline(std::string& source)
{
	for (std::string::size_type i = 0; (i = source.find("\\n", i)) != std::string::npos;)
	{
		source.replace(i, 2, NEWLINE_STRING);
		i += 2;
	}
}

void findAndReplaceQuoteEscape(std::string& source)
{
	for (std::string::size_type i = 0; (i = source.find("\\\"", i)) != std::string::npos;)
	{
		source.replace(i, 2, "\"");
		i += 2;
	}
}

#endif
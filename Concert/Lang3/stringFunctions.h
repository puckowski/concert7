
#ifndef STRING_FUNCTIONS_H
#define STRING_FUNCTIONS_H

#include <string>

const std::wstring NEWLINE_STRING = std::wstring(L"\n");

void findAndReplace(std::wstring& source, std::wstring const& find, std::wstring const& replace)
{
	for (std::wstring::size_type i = 0; (i = source.find(find, i)) != std::wstring::npos;)
	{
		source.replace(i, find.length(), replace);
		i += replace.length();
	}
}

void findAndReplaceNewline(std::wstring& source)
{
	for (std::wstring::size_type i = 0; (i = source.find(L"\\n", i)) != std::wstring::npos;)
	{
		source.replace(i, 2, NEWLINE_STRING);
		i += 2;
	}
}

void findAndReplaceQuoteEscape(std::wstring& source)
{
	for (std::wstring::size_type i = 0; (i = source.find(L"\\\"", i)) != std::wstring::npos;)
	{
		source.replace(i, 2, L"\"");
		i += 2;
	}
}

#endif
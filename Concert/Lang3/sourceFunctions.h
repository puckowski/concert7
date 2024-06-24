
#ifndef SOURCE_FUNCTIONS_H
#define SOURCE_FUNCTIONS_H

#include <string>
#include <vector>
#include <stack>
#include <thread>
#include <sstream>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <mutex>
#include <locale>
#include <boost/locale.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <locale>
#include <codecvt>

#include "header.h"

extern void exec(int &line, bool detached = false, CodeStore* myCodeStore = nullptr, WorkspaceStore* myWorkspaceStore = nullptr, int jumpBackTo = 0);

void addFunctionToMap(const std::wstring &name, int line)
{
	mFunctionMap.insert({ name, line });
}

int getFunctionLineFromMap(const std::wstring &name)
{
	auto search = mFunctionMap.find(name);

	if (search != mFunctionMap.end())
	{
		return search->second;
	}

	return -1;
}

void addToken(std::vector<std::wstring> &tokens, std::wstring &token)
{
	if (token.empty() == false)
	{
		tokens.push_back(token);
	}

	token = L"";
}

void addTokenUnchecked(std::vector<std::wstring> &tokens, std::wstring token)
{
	tokens.push_back(token);
}

void addTokenUncheckedByReference(std::vector<std::wstring> &tokens, std::wstring &token)
{
	tokens.push_back(token);
}

bool peek(const std::wstring &statement, const int &statementLength, const int index, const wchar_t compare)
{
	int peekIndex = index + 1;

	if (peekIndex < statementLength)
	{
		if (statement[peekIndex] == compare)
		{
			return true;
		}
	}

	return false;
}

void tokenizeStatement3(std::wstring &statement, std::vector<std::wstring> &tokens)
{
	std::wstring token = L"";
	int statementLength = statement.length();
	bool isAssignment = false;
	bool isComparison = false;
	wchar_t c;

	for (int i = 0; i < statementLength; ++i)
	{
		c = statement[i];

		switch (c)
		{
		case L'\n':
		{
			break;
		}
		case L'\t':
		{
			break;
		}
		case L'#':
		{
			return;
		}
		case L' ':
		{
			addToken(tokens, token);

			break;
		}
		case L'"':
		{
			do
			{
				if (peek(statement, statementLength, i, '"') == false)
				{
					token += c;

					++i;
					c = statement[i];
				}
				else
				{
					if (c == '\\')
					{
						token += '"';

						++i;
						++i;
						c = statement[i];

						if (c == '"')
						{
							token += L"\"";

							break;
						}
					}
					else
					{
						token += c;
						token += L"\"";
						++i;

						break;
					}
				}
			} while (i < statementLength);

			addToken(tokens, token);

			break;
		}
		case L'&':
		{
			addToken(tokens, token);
			addTokenUnchecked(tokens, L"&");

			break;
		}
		case L'(':
		{
			addToken(tokens, token);
		    addTokenUnchecked(tokens, L"(");

			break;
		}
		case L'|':
		{
			addToken(tokens, token);
			addTokenUnchecked(tokens, L"|");

			break;
		}
		case L'~':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"~=");
				++i;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"~");
			}

			break;
		}
		case L'%':
		{
			addToken(tokens, token);
			addTokenUnchecked(tokens, L"%");

			break;
		}
		case L')':
		{
			addToken(tokens, token);
			addTokenUnchecked(tokens, L")");

			break;
		}
		case L',':
		{
			addToken(tokens, token);

			break;
		}
		case L':':
		{
			addToken(tokens, token);

			break;
		}
		case L'<':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"<=");
				++i;

				isComparison = true;
			}
			else if (peek(statement, statementLength, i, '<') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"<<");
				++i;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"<");

				isComparison = true;
			}

			break;
		}
		case L'>':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L">=");
				++i;

				isComparison = true;
			}
			else if (peek(statement, statementLength, i, '>') == true)
			{
				if (peek(statement, statementLength, i + 1, '>') == true)
				{
					addToken(tokens, token);
					addTokenUnchecked(tokens, L">>>");
					i += 2;
				}
				else
				{
					addToken(tokens, token);
					addTokenUnchecked(tokens, L">>");
					++i;
				}
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L">");

				isComparison = true;
			}

			break;
		}
		case L'+':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"+=");
				++i;

				isAssignment = true;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"+");
			}

			break;
		}
		case L'*':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"*=");
				++i;

				isAssignment = true;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"*");
			}

			break;
		}
		case L'/':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"/=");
				++i;

				isAssignment = true;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"/");
			}

			break;
		}
		case L'^':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"^=");
				++i;

				isAssignment = true;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"^");
			}

			break;
		}
		case L'-':
		{
			if (peek(statement, statementLength, i, '>') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"->");
				++i;
			}
			else if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"-=");
				++i;

				isAssignment = true;
			}
			else if (isAssignment == true)
			{
				token += c;
			}
			else if (isComparison == true)
			{
				token += c;

				isComparison = false;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"-");
			}

			break;
		}
		case L'=':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"==");
				++i;

				isComparison = true;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"=");

				isAssignment = true;
			}

			break;
		}
		case L'!':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"!=");
				++i;

				isComparison = true;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"!");
			}

			break;
		}
		case L';':
		{
			addToken(tokens, token);

			codeStore->gStatements.push_back(tokens);
			tokens.clear();

			isAssignment = false;
			isComparison = false;

			break;
		}
		default:
		{
			token += c;

			break;
		}
		}
	}
}

void tokenizeStatement3(std::wstring &statement, std::vector<std::wstring> &tokens, CodeStore* newCodeStore)
{
	std::wstring token = L"";
	int statementLength = statement.length();
	bool isAssignment = false;
	wchar_t c;

	for (int i = 0; i < statementLength; ++i)
	{
		c = statement[i];

		switch (c)
		{
		case L'\n':
		{
			break;
		}
		case L'\t':
		{
			break;
		}
		case L'#':
		{
			return;
		}
		case L' ':
		{
			addToken(tokens, token);

			break;
		}
		case L'"':
		{
			do
			{
				if (peek(statement, statementLength, i, '"') == false)
				{
					token += c;

					++i;
					c = statement[i];
				}
				else
				{
					if (c == '\\')
					{
						token += '"';

						++i;
						++i;
						c = statement[i];

						if (c == '"')
						{
							token += L"\"";

							break;
						}
					}
					else
					{
						token += c;
						token += L"\"";
						++i;

						break;
					}
				}
			} while (i < statementLength);

			addToken(tokens, token);

			break;
		}
		case L'&':
		{
			addToken(tokens, token);
			addTokenUnchecked(tokens, L"&");

			break;
		}
		case L'(':
		{
			addToken(tokens, token);
			addTokenUnchecked(tokens, L"(");

			break;
		}
		case L'|':
		{
			addToken(tokens, token);
			addTokenUnchecked(tokens, L"|");

			break;
		}
		case L'~':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"~=");
				++i;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"~");
			}

			break;
		}
		case L'%':
		{
			addToken(tokens, token);
			addTokenUnchecked(tokens, L"%");

			break;
		}
		case L')':
		{
			addToken(tokens, token);
			addTokenUnchecked(tokens, L")");

			break;
		}
		case L',':
		{
			addToken(tokens, token);

			break;
		}
		case L':':
		{
			addToken(tokens, token);

			break;
		}
		case L'<':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"<=");
				++i;
			}
			else if (peek(statement, statementLength, i, '<') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"<<");
				++i;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"<");
			}

			break;
		}
		case L'>':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L">=");
				++i;
			}
			else if (peek(statement, statementLength, i, '>') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L">>");
				++i;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L">");
			}

			break;
		}
		case L'+':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"+=");
				++i;

				isAssignment = true;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"+");
			}

			break;
		}
		case L'*':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"*=");
				++i;

				isAssignment = true;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"*");
			}

			break;
		}
		case L'/':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"/=");
				++i;

				isAssignment = true;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"/");
			}

			break;
		}
		case L'^':
		{
			addToken(tokens, token);
			addTokenUnchecked(tokens, L"^");

			break;
		}
		case L'-':
		{
			if (peek(statement, statementLength, i, '>') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"->");
				++i;
			}
			else if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"-=");
				++i;

				isAssignment = true;
			}
			else if (isAssignment == true)
			{
				token += c;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"-");
			}

			break;
		}
		case L'=':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"==");
				++i;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"=");

				isAssignment = true;
			}

			break;
		}
		case L'!':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"!=");
				++i;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, L"!");
			}

			break;
		}
		case L';':
		{
			addToken(tokens, token);

			newCodeStore->gStatements.push_back(tokens);
			tokens.clear();

			isAssignment = false;

			break;
		}
		default:
		{
			token += c;

			break;
		}
		}
	}
}

void replaceAll(std::wstring &s, const std::wstring &search, const std::wstring &replace)
{
	for (size_t pos = 0; ; pos += replace.length()) 
	{
		// Locate the substring to replace
		pos = s.find(search, pos);

		if (pos == std::wstring::npos)
		{
			break;
		}

		// Replace by erasing and inserting
		s.erase(pos, search.length());
		s.insert(pos, replace);
	}
}

void addExitTokenVectorIfNeeded()
{
	if (codeStore->gStatements.size() == 0) {
		return;
	}

	const std::vector<std::wstring> lastTokens = codeStore->gStatements.back();

	if (lastTokens.size() != 1) {
		if (lastTokens.size() == 0) {
			const std::vector<std::wstring> exitVector = { L"exit" };
			codeStore->gStatements.push_back(exitVector);
		}
		else {
			const std::wstring firstToken = lastTokens.at(0);
			std::locale loc;

			std::wstring tokenLowercase = L"";
			for (std::wstring::size_type i = 0; i < firstToken.length(); ++i)
			{
				tokenLowercase += std::tolower(firstToken[i], loc);
			}

			if (tokenLowercase != L"exit") {
				const std::vector<std::wstring> exitVector = { L"exit" };
				codeStore->gStatements.push_back(exitVector);
			}
		}
	}
}

void readStatementsFromFile(const std::wstring& filename)
{
	// Set up the locale to handle UTF-8 using Boost.Locale
	boost::locale::generator gen;
	std::locale utf8_locale = gen("en_US.UTF-8");

	// Imbue the global locale with the UTF-8 locale
	std::locale::global(utf8_locale);

	// Ensure wcout uses the UTF-8 locale
	std::wcout.imbue(utf8_locale);

	// Path to the UTF-8 encoded file
	boost::filesystem::path file_path(filename);

	// Open the file
	boost::filesystem::ifstream file(file_path);

	// Check if the file is open
	if (!file.is_open()) {
		std::wcerr << "Failed to open file: " << filename << std::endl;
		return;
	}

	// Apply the UTF-8 locale to the file stream
	file.imbue(utf8_locale);

	std::string line;
	std::vector<std::wstring> tokens;

	while (std::getline(file, line)) {
		// Convert to wstring
		std::wstring wline = utf8_to_wstring(line);

		tokenizeStatement3(wline, tokens);
	}

	// Close the file
	file.close();

	addExitTokenVectorIfNeeded();
}

bool readStatementsFromConsole()
{
	std::vector<std::wstring> lines;
	std::wstring line;
	/*
	do
	{
		std::cout << "> ";
		std::getline(std::cin, line);

		if (line.empty() == true)
		{
			break;
		}
		else if (line == L"exit")
		{
			return false;
		}
		else
		{
			lines.push_back(line);
		}
	} while (true);

	for (std::vector<std::wstring>::iterator it = lines.begin(); it != lines.end(); ++it)
	{
		line = *it;

		std::vector<std::wstring> tokens;
		tokenizeStatement3(line, tokens);
	}*/

	return true;
}

void readStatementsFromFile(const std::wstring &filename, CodeStore* codeStore)
{
	std::ifstream file(filename);
	std::string line;

	std::wstring source = L"";

	while (std::getline(file, line))
	{
		source += utf8_to_wstring(line);
		source += L" ";
	}

	std::vector<std::wstring> tokens;
	tokenizeStatement3(source, tokens);

	addExitTokenVectorIfNeeded();
}

void readStatementsIntoNewCodeStore2(int currentLine, CodeStore* existingCodeStore, CodeStore* codeStore)
{
	int l = 0;
	bool inFunc = false;
	bool finishedLastFunc = true;

	while (l < currentLine)
	{
		if (existingCodeStore->gStatements[l].empty() == true) 
		{
			codeStore->gStatements.push_back(existingCodeStore->gStatements[l]);

			l++;

			continue;
		}

		if (existingCodeStore->gStatements[l][0] == L"function") 
		{
			inFunc = true;
			finishedLastFunc = false;
		}

		if (inFunc == true) 
		{
			codeStore->gStatements.push_back(existingCodeStore->gStatements[l]);
		}
		else if (existingCodeStore->gStatements[l][0] == L"import")
		{
			codeStore->gStatements.push_back(existingCodeStore->gStatements[l]);
		}

		if (existingCodeStore->gStatements[l][0] == L"return") 
		{
			inFunc = false;
			finishedLastFunc = true;
		}

		l++;
	}

	if (finishedLastFunc == false)
	{
		while (codeStore->gStatements.back()[0] != L"function")
		{
			codeStore->gStatements.pop_back();
		}

		codeStore->gStatements.pop_back();
	}
}

#endif

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

#include "header.h"

extern void exec(int &line, bool detached = false, CodeStore* myCodeStore = nullptr, WorkspaceStore* myWorkspaceStore = nullptr, int jumpBackTo = 0);

void addFunctionToMap(const std::string &name, int line)
{
	mFunctionMap.insert({ name, line });
}

int getFunctionLineFromMap(const std::string &name)
{
	auto search = mFunctionMap.find(name);

	if (search != mFunctionMap.end())
	{
		return search->second;
	}

	return -1;
}

void addToken(std::vector<std::string> &tokens, std::string &token)
{
	if (token.empty() == false)
	{
		tokens.push_back(token);
	}

	token = "";
}

void addTokenUnchecked(std::vector<std::string> &tokens, std::string token)
{
	tokens.push_back(token);
}

void addTokenUncheckedByReference(std::vector<std::string> &tokens, std::string &token)
{
	tokens.push_back(token);
}

bool peek(const std::string &statement, const int &statementLength, const int index, const char compare)
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

void tokenizeStatement3(std::string &statement, std::vector<std::string> &tokens)
{
	std::string token = "";
	int statementLength = statement.length();
	bool isAssignment = false;
	bool isComparison = false;
	char c;

	for (int i = 0; i < statementLength; ++i)
	{
		c = statement[i];

		switch (c)
		{
		case '\n':
		{
			break;
		}
		case '\t':
		{
			break;
		}
		case '#':
		{
			return;
		}
		case ' ':
		{
			addToken(tokens, token);

			break;
		}
		case '"':
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
							token += "\"";

							break;
						}
					}
					else
					{
						token += c;
						token += "\"";
						++i;

						break;
					}
				}
			} while (i < statementLength);

			addToken(tokens, token);

			break;
		}
		case '&':
		{
			addToken(tokens, token);
			addTokenUnchecked(tokens, "&");

			break;
		}
		case '(':
		{
			addToken(tokens, token);
		    addTokenUnchecked(tokens, "(");

			break;
		}
		case '|':
		{
			addToken(tokens, token);
			addTokenUnchecked(tokens, "|");

			break;
		}
		case '~':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "~=");
				++i;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "~");
			}

			break;
		}
		case '%':
		{
			addToken(tokens, token);
			addTokenUnchecked(tokens, "%");

			break;
		}
		case ')':
		{
			addToken(tokens, token);
			addTokenUnchecked(tokens, ")");

			break;
		}
		case ',':
		{
			addToken(tokens, token);

			break;
		}
		case ':':
		{
			addToken(tokens, token);

			break;
		}
		case '<':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "<=");
				++i;

				isComparison = true;
			}
			else if (peek(statement, statementLength, i, '<') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "<<");
				++i;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "<");

				isComparison = true;
			}

			break;
		}
		case '>':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, ">=");
				++i;

				isComparison = true;
			}
			else if (peek(statement, statementLength, i, '>') == true)
			{
				if (peek(statement, statementLength, i + 1, '>') == true)
				{
					addToken(tokens, token);
					addTokenUnchecked(tokens, ">>>");
					i += 2;
				}
				else
				{
					addToken(tokens, token);
					addTokenUnchecked(tokens, ">>");
					++i;
				}
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, ">");

				isComparison = true;
			}

			break;
		}
		case '+':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "+=");
				++i;

				isAssignment = true;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "+");
			}

			break;
		}
		case '*':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "*=");
				++i;

				isAssignment = true;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "*");
			}

			break;
		}
		case '/':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "/=");
				++i;

				isAssignment = true;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "/");
			}

			break;
		}
		case '^':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "^=");
				++i;

				isAssignment = true;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "^");
			}

			break;
		}
		case '-':
		{
			if (peek(statement, statementLength, i, '>') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "->");
				++i;
			}
			else if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "-=");
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
				addTokenUnchecked(tokens, "-");
			}

			break;
		}
		case '=':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "==");
				++i;

				isComparison = true;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "=");

				isAssignment = true;
			}

			break;
		}
		case '!':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "!=");
				++i;

				isComparison = true;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "!");
			}

			break;
		}
		case ';':
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

void tokenizeStatement3(std::string &statement, std::vector<std::string> &tokens, CodeStore* newCodeStore)
{
	std::string token = "";
	int statementLength = statement.length();
	bool isAssignment = false;
	char c;

	for (int i = 0; i < statementLength; ++i)
	{
		c = statement[i];

		switch (c)
		{
		case '\n':
		{
			break;
		}
		case '\t':
		{
			break;
		}
		case '#':
		{
			return;
		}
		case ' ':
		{
			addToken(tokens, token);

			break;
		}
		case '"':
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
							token += "\"";

							break;
						}
					}
					else
					{
						token += c;
						token += "\"";
						++i;

						break;
					}
				}
			} while (i < statementLength);

			addToken(tokens, token);

			break;
		}
		case '&':
		{
			addToken(tokens, token);
			addTokenUnchecked(tokens, "&");

			break;
		}
		case '(':
		{
			addToken(tokens, token);
			addTokenUnchecked(tokens, "(");

			break;
		}
		case '|':
		{
			addToken(tokens, token);
			addTokenUnchecked(tokens, "|");

			break;
		}
		case '~':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "~=");
				++i;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "~");
			}

			break;
		}
		case '%':
		{
			addToken(tokens, token);
			addTokenUnchecked(tokens, "%");

			break;
		}
		case ')':
		{
			addToken(tokens, token);
			addTokenUnchecked(tokens, ")");

			break;
		}
		case ',':
		{
			addToken(tokens, token);

			break;
		}
		case ':':
		{
			addToken(tokens, token);

			break;
		}
		case '<':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "<=");
				++i;
			}
			else if (peek(statement, statementLength, i, '<') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "<<");
				++i;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "<");
			}

			break;
		}
		case '>':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, ">=");
				++i;
			}
			else if (peek(statement, statementLength, i, '>') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, ">>");
				++i;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, ">");
			}

			break;
		}
		case '+':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "+=");
				++i;

				isAssignment = true;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "+");
			}

			break;
		}
		case '*':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "*=");
				++i;

				isAssignment = true;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "*");
			}

			break;
		}
		case '/':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "/=");
				++i;

				isAssignment = true;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "/");
			}

			break;
		}
		case '^':
		{
			addToken(tokens, token);
			addTokenUnchecked(tokens, "^");

			break;
		}
		case '-':
		{
			if (peek(statement, statementLength, i, '>') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "->");
				++i;
			}
			else if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "-=");
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
				addTokenUnchecked(tokens, "-");
			}

			break;
		}
		case '=':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "==");
				++i;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "=");

				isAssignment = true;
			}

			break;
		}
		case '!':
		{
			if (peek(statement, statementLength, i, '=') == true)
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "!=");
				++i;
			}
			else
			{
				addToken(tokens, token);
				addTokenUnchecked(tokens, "!");
			}

			break;
		}
		case ';':
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

void replaceAll(std::string &s, const std::string &search, const std::string &replace)
{
	for (size_t pos = 0; ; pos += replace.length()) 
	{
		// Locate the substring to replace
		pos = s.find(search, pos);

		if (pos == std::string::npos)
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

	const std::vector<std::string> lastTokens = codeStore->gStatements.back();

	if (lastTokens.size() != 1) {
		if (lastTokens.size() == 0) {
			const std::vector<std::string> exitVector = { "exit" };
			codeStore->gStatements.push_back(exitVector);
		}
		else {
			const std::string firstToken = lastTokens.at(0);
			std::locale loc;

			std::string tokenLowercase = "";
			for (std::string::size_type i = 0; i < firstToken.length(); ++i)
			{
				tokenLowercase += std::tolower(firstToken[i], loc);
			}

			if (tokenLowercase != "exit") {
				const std::vector<std::string> exitVector = { "exit" };
				codeStore->gStatements.push_back(exitVector);
			}
		}
	}
}

void readStatementsFromFile(const std::string &filename)
{
	std::ifstream file(filename);
	std::string line;

	std::string source = "";
	std::vector<std::string> tokens;

	while (std::getline(file, line))
	{
		source = line;
		tokenizeStatement3(source, tokens);
	}

	addExitTokenVectorIfNeeded();
}

bool readStatementsFromConsole()
{
	std::vector<std::string> lines;
	std::string line;

	do
	{
		std::cout << "> ";
		std::getline(std::cin, line);

		if (line.empty() == true)
		{
			break;
		}
		else if (line == "exit")
		{
			return false;
		}
		else
		{
			lines.push_back(line);
		}
	} while (true);

	for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); ++it)
	{
		line = *it;

		std::vector<std::string> tokens;
		tokenizeStatement3(line, tokens);
	}

	return true;
}

void readStatementsFromFile(const std::string &filename, CodeStore* codeStore)
{
	std::ifstream file(filename);
	std::string line;

	std::string source = "";

	while (std::getline(file, line))
	{
		source += line;
		source += " ";
	}

	std::vector<std::string> tokens;
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

		if (existingCodeStore->gStatements[l][0] == "function") 
		{
			inFunc = true;
			finishedLastFunc = false;
		}

		if (inFunc == true) 
		{
			codeStore->gStatements.push_back(existingCodeStore->gStatements[l]);
		}
		else if (existingCodeStore->gStatements[l][0] == "import")
		{
			codeStore->gStatements.push_back(existingCodeStore->gStatements[l]);
		}

		if (existingCodeStore->gStatements[l][0] == "return") 
		{
			inFunc = false;
			finishedLastFunc = true;
		}

		l++;
	}

	if (finishedLastFunc == false)
	{
		while (codeStore->gStatements.back()[0] != "function")
		{
			codeStore->gStatements.pop_back();
		}

		codeStore->gStatements.pop_back();
	}
}

#endif

#ifndef KEYWORD_CALL_H
#define KEYWORD_CALL_H

#include <string>
#include <vector>

#include "sourceFunctions.h"
#include "VarStore.h"
#include "WorkspaceStore.h"
#include "Var.h"
#include "standardLibrary.h"
#include "stringLibrary.h"
#include "fileLibrary.h"
#include "mathLibrary.h"
#include "regexLibrary.h"
#include "threadLibrary.h"

void executeKeywordCall(const int &tokensSize, std::vector<std::wstring> &tokens)
{
	int currentLineCopy = currentLine;

	currentLine = getFunctionLineFromMap(tokens[1]);

	if (debugEnabled == true)
	{
		callNameMutex.lock();
		std::wostringstream ss;
		ss << std::this_thread::get_id();
		std::wstring idstr = ss.str();
		callNameStack.push_back(idstr + L"_" + tokens[1]);
		callNameMutex.unlock();
	}

	if (currentLine != -1)
	{
		std::wstring origWs = workspaceStack.back();

		////
		lastWorkspace = gWorkspaceStore->getStore();
		gWorkspaceStore->addStore(tokens[1], new VarStore());
		workspaceStack.push_back(tokens[1]);
		////

		bool hasReturn = false;

		for (int i = 2; i < tokensSize; ++i)
		{
			if (tokens[i] == L"->") 
			{
				hasReturn = true;

				break;
			}

			callStack.push_back(tokens[i]);
		}

		exec(currentLine);

		currentLine = currentLineCopy;

		while (workspaceStack.back() != origWs)
		{
			////
			gWorkspaceStore->removeStore();
			workspaceStack.pop_back();
			//lastWorkspace = gWorkspaceStore->getStore();
			gWorkspaceStore->setBack();
			////
		}

		if (hasReturn)
		{
			int r1;
			Var* v = gWorkspaceStore->getStore()->getVar(tokens[tokensSize - 1], r1);
			execAssignOperator(v, r1, returnVar, returnVarInt);
		}
	}
	else
	{
		LibraryFunction func = mLibraryMap.find(tokens[1])->second;

		currentLine = currentLineCopy;

		switch (func)
		{
		case STRING_SUBSTRING:
		{
			libraryStringSubstring(tokens, tokensSize);

			break;
		}
		case STRING_FIND:
		{
			libraryStringIndexOf(tokens, tokensSize);

			break;
		}
		case STRING_CONTAINS:
		{
			libraryStringContains(tokens, tokensSize);

			break;
		}
		case STRING_LENGTH:
		{
			libraryStringLength(tokens, tokensSize);

			break;
		}
		case STRING_TO_INT:
		{
			libraryStringToInt(tokens, tokensSize);

			break;
		}
		case STRING_TO_DOUBLE:
		{
			libraryStringToDouble(tokens, tokensSize);

			break;
		}
		case FILE_OPEN_FILE:
		{
			libraryOpenFile(tokens, tokensSize);

			break;
		}
		case FILE_OPEN_BYTE_FILE:
		{
			libraryOpenByteFile(tokens, tokensSize);

			break;
		}
		case FILE_CLOSE_FILE:
		{
			libraryCloseFile(tokens, tokensSize);

			break;
		}
		case FILE_WRITE_STRING:
		{
			libraryWriteString(tokens, tokensSize);

			break;
		}
		case FILE_GET_LINE:
		{
			libraryGetLine(tokens, tokensSize);

			break;
		}
		case FILE_IS_OPEN:
		{
			libraryIsOpen(tokens, tokensSize);

			break;
		}
		case FILE_IS_EOF:
		{
			libraryIsAtEndOfFile(tokens, tokensSize);

			break;
		}
		case FILE_IS_EXIST:
		{
			libraryIsFileExist(tokens, tokensSize);

			break;
		}
		case FILE_CREATE_FILE:
		{
			libraryCreateFile(tokens, tokensSize);

			break;
		}
		case FILE_GET_FILE_SIZE:
		{
			libraryGetFileSize(tokens, tokensSize);

			break;
		}
		case STRING_CHAR_AT:
		{
			libraryStringCharAt(tokens, tokensSize);

			break;
		}
		case MATH_SRAND:
		{
			libraryMathSeedRand(tokens, tokensSize);

			break;
		}
		case MATH_RAND:
		{
			libraryMathRand(tokens, tokensSize);

			break;
		}
		case FILE_SEEK:
		{
			librarySeek(tokens, tokensSize);

			break;
		}
		case FILE_READ:
		{
			libraryReadByte(tokens, tokensSize);

			break;
		}
		case FILE_READ_WCHAR:
		{
			libraryRead(tokens, tokensSize);

			break;
		}
		case FILE_WRITE:
		{
			libraryWriteByte(tokens, tokensSize);

			break;
		}
		case FILE_WRITE_WCHAR:
		{
			libraryWrite(tokens, tokensSize);

			break;
		}
		case FILE_REMOVE:
		{
			libraryRemoveFile(tokens, tokensSize);

			break;
		}
		case FILE_RENAME:
		{
			libraryRenameFile(tokens, tokensSize);

			break;
		}
		case FILE_TELLG:
		{
			libraryTell(tokens, tokensSize);

			break;
		}
		case STRING_CHAR_TO_STRING:
		{
			libraryCharToString(tokens, tokensSize);

			break;
		}
		case STRING_WCHAR_TO_STRING:
		{
			libraryWcharToString(tokens, tokensSize);

			break;
		}
		case STRING_INT_TO_STRING:
		{
			libraryIntToString(tokens, tokensSize);

			break;
		}
		case STRING_DOUBLE_TO_STRING:
		{
			libraryDoubleToString(tokens, tokensSize);

			break;
		}
		case MATH_INT_TO_DOUBLE:
		{
			libraryMathIntToDouble(tokens, tokensSize);

			break;
		}
		case MATH_DOUBLE_TO_INT:
		{
			libraryMathDoubleToInt(tokens, tokensSize);

			break;
		}
		case STRING_CHAR_TO_INT:
		{
			libraryCharToInt(tokens, tokensSize);

			break;
		}
		case MATH_INT_TO_LONG:
		{
			libraryMathIntToLong(tokens, tokensSize);

			break;
		}
		case STRING_TO_LOWER_CASE:
		{
			libraryStringLowerCase(tokens, tokensSize);

			break;
		}
		case STRING_TO_UPPER_CASE:
		{
			libraryStringUpperCase(tokens, tokensSize);

			break;
		}
		case FILE_CREATE_DIRECTORY: 
		{
			libraryCreateDirectory(tokens, tokensSize);

			break;
		}
		case MATH_LONG_TO_INT:
		{
			libraryMathLongToInt(tokens, tokensSize);

			break;
		}
		case MATH_DOUBLE_TO_LONG:
		{
			libraryMathDoubleToLong(tokens, tokensSize);

			break;
		}
		case MATH_LONG_TO_DOUBLE:
		{
			libraryMathLongToDouble(tokens, tokensSize);

			break;
		}
		case REGEX_SEARCH:
		{
			libraryRegexSearch(tokens, tokensSize);

			break;
		}
		case REGEX_MATCH: 
		{
			libraryRegexMatch(tokens, tokensSize);

			break;
		}
		case REGEX_REPLACE:
		{
			libraryRegexReplace(tokens, tokensSize);

			break;
		}
		case GET_THREAD_ID:
		{
			libraryThreadGetId(tokens, tokensSize);

			break;
		}
		case ABSOLUTE_VALUE:
		{
			libraryMathAbsoluteValue(tokens, tokensSize);

			break;
		}
		}
	}

	if (debugEnabled == true)
	{
		callNameMutex.lock();
		std::wostringstream ss;
		ss << std::this_thread::get_id();
		std::wstring idstr = ss.str();
		std::wstring currId;

		for (auto it = callNameStack.rbegin(); it != callNameStack.rend(); ++it)
		{
			currId = *it;

			if (currId.compare(0, idstr.size(), idstr) == false)
			{
				callNameStack.erase((it + 1).base());
				break;
			}
		}
		callNameMutex.unlock();
	}
}

#endif
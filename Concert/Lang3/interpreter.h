#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <map>
#include <thread>
#include <string>
#include <iostream>
#include <unordered_map>

#include "header.h"
#include "Var.h"
#include "CodeStore.h"
#include "variableFunctions.h"
#include "operatorFunctions.h"
#include "reservedWord.h"
#include "WorkspaceStore.h"
#include "printFunctions.h"
#include "intDeclaration.h"
#include "longDeclaration.h"
#include "doubleDeclaration.h"
#include "stringDeclaration.h"
#include "keywordIf.h"
#include "keywordWhile.h"
#include "keywordFunction.h"
#include "keywordImport.h"
#include "keywordInclude.h"
#include "keywordLock.h"
#include "keywordUnlock.h"
#include "keywordDetach.h"
#include "keywordCall.h"
#include "keywordBreak.h"
#include "keywordTry.h"
#include "keywordSizeof.h"
#include "keywordPrintln.h"
#include "keywordPrint.h"
#include "keywordReadln.h"
#include "keywordRead.h"
#include "keywordReturn.h"
#include "keywordEnd.h"
#include "keywordJoin.h"
#include "keywordDelete.h"
#include "keywordSystem.h"
#include "keywordExec.h"
#include "keywordElse.h"
#include "keywordInstanceof.h"
#include "keywordContinue.h"
#include "objectDeclaration.h"
#include "keywordKeys.h"
#include "keywordAlias.h"
#include "keywordReassign.h"
#include "keywordAddress.h"

void execLoop(std::vector<std::wstring> &tokens)
{
	std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<const std::wstring, const ReservedWord>>>> reservedWordCheck;
	ReservedWord reservedWord;
	int tokensSize;

	for (; currentLine < statementCount; ++currentLine)
	{
		tokens = codeStore->gStatements[currentLine];

		tokensSize = tokens.size();

		//std::cout << "\t\t\t\t";
		//for (auto s : tokens)
		//	std::wcout << s << " ";
		//std::cout << std::endl;
		reservedWordCheck = RESERVED_WORD_MAP.find(tokens[0]);

		// Keyword or datatype
		if (reservedWordCheck != RESERVED_WORD_MAP_END)
		{
			reservedWord = reservedWordCheck->second;

			switch (reservedWord)
			{
			case KEYWORD_MUTEX:
			{
				createMutex(tokens[1]);

				break;
			}
			case TYPE_INT:
			{
				declareIntVariable(tokensSize, tokens);

				break;
			}
			case TYPE_LONG:
			{
				declareLongVariable(tokensSize, tokens);

				break;
			}
			case TYPE_DOUBLE:
			{
				declareDoubleVariable(tokensSize, tokens);

				break;
			}
			case TYPE_STRING:
			{
				declareStringVariable(tokensSize, tokens);

				break;
			}
			case TYPE_OBJECT:
			{
				declareObjectVariable(tokensSize, tokens);

				break;
			}
			case KEYWORD_IF:
			{
				executeKeywordIf(tokens);

				break;
			}
			case KEYWORD_WHILE:
			{
				executeKeywordWhile(tokens);

				break;
			}
			case TYPE_FUNCTION:
			{
				executeKeywordFunction(tokensSize, tokens);

				break;
			}
			case KEYWORD_IMPORT:
			{
				executeKeywordImport(tokensSize, tokens);

				break;
			}
			case KEYWORD_INCLUDE:
			{
				executeKeywordInclude(tokens, currentLine);

				break;
			}
			case KEYWORD_LOCK:
			{
				executeKeywordLock(tokens);

				break;
			}
			case KEYWORD_UNLOCK:
			{
				executeKeywordUnlock(tokens);

				break;
			}
			case KEYWORD_DETACH:
			{
				executeKeywordDetach(tokensSize, tokens);

				break;
			}
			case KEYWORD_JOIN:
			{
				executeKeywordJoin(tokensSize, tokens);

				break;
			}
			case KEYWORD_CALL:
			{
				executeKeywordCall(tokensSize, tokens);

				break;
			}
			case KEYWORD_SIZEOF:
			{
				executeKeywordSizeof(tokensSize, tokens);

				break;
			}
			case KEYWORD_PRINTLN:
			{
				executeKeywordPrintln(tokensSize, tokens);

				break;
			}
			case KEYWORD_PRINT:
			{
				executeKeywordPrint(tokensSize, tokens);

				break;
			}
			case KEYWORD_READLN:
			{
				executeKeywordReadln(tokens);

				break;
			}
			case KEYWORD_READ:
			{
				executeKeywordRead(tokens);

				break;
			}
			case KEYWORD_DELETE:
			{
				executeKeywordDelete(tokens);

				break;
			}
			case KEYWORD_RETURN:
			{
				executeKeywordReturn(tokensSize, tokens);

				return;
			}
			case KEYWORD_END:
			{
				executeKeywordEnd(currentLine);

				//if /while fix/clean
				//currentLine--;

				break;
			}
			case KEYWORD_CATCH:
			{
				return;
			}
			case KEYWORD_TRY:
			{
				executeKeywordTry(currentLine, tokens);

				break;
			}
			case KEYWORD_BREAK:
			{
				executeKeywordBreak(currentLine, tokens);

				break;
			}
			case KEYWORD_SYSTEM:
			{
				executeKeywordSystem(tokensSize, tokens);

				break;
			}
			case KEYWORD_EXEC:
			{
				executeKeywordExec(tokens);

				//statementCount = codeStore->gStatements.size();

				break;
			}
			case KEYWORD_EXIT:
			{
				currentLine = statementCount;

				break;
			}
			case KEYWORD_ELSE:
			{
				executeKeywordElse(tokensSize, tokens, currentLine);

				break;
			}
			case KEYWORD_INSTANCEOF:
			{
				executeKeywordInstanceof(tokens);

				break;
			}
			case KEYWORD_CONTINUE:
			{
				executeKeywordContinue(currentLine, tokens);

				break;
			}
			case KEYWORD_KEYS:
			{
				executeKeywordKeys(tokensSize, tokens);

				break;
			}
			case KEYWORD_ALIAS:
			{
				executeKeywordAlias(tokens);

				break;
			}
			case KEYWORD_REASSIGN:
			{
				executeKeywordReassign(tokens);

				break;
			}
			case KEYWORD_ADDRESS:
			{
				executeKeywordAddress(tokens);

				break;
			}
			}
		}
		else
		{
			executeAssignment(tokensSize, tokens);
		}
	}
}

void exec(int &line, bool detached, CodeStore* myCodeStore, WorkspaceStore* myWorkspaceStore, int jumpBackTo, int newTryBlocks)
{
	if (detached)
	{
		codeStore = myCodeStore;

		currentLine = 0;

		gWorkspaceStore = myWorkspaceStore;
		workspaceStack.push_back(L"global");

		if (debugEnabled == true)
		{
			callNameMutex.lock();
			std::wostringstream ss;
			ss << std::this_thread::get_id();
			std::wstring idstr = ss.str();
			callNameStack.push_back(idstr + L"_main");
			callNameMutex.unlock();
		}
	}
	else
	{
		currentLine = line;
	}

	tryBlockCount += newTryBlocks;

	statementCount = codeStore->gStatements.size();
	std::vector<std::wstring> tokens;

	if (tryBlockCount == 0)
	{
		try
		{
			execLoop(tokens);
		}
		catch (const std::exception& exc) 
		{
			if (debugEnabled == true)
			{
				std::cout << std::endl;
				std::cout << "exception occurred: " << exc.what() << std::endl;
				std::cout << "current line: " << (currentLine + 1) << std::endl;
				for (std::wstring tok : tokens)
				{
					std::wcout << tok << " ";
				}
				std::cout << std::endl;
				std::cout << "current thread id: " << std::this_thread::get_id() << std::endl;
				std::cout << "main thread id: " << mainThreadId << std::endl;
				std::cout << "call stack: " << std::endl;
				for (auto it = callNameStack.rbegin(); it != callNameStack.rend(); ++it)
				{
					std::wcout << *it << std::endl;
				}
			}
		}
		catch (...)
		{
			if (debugEnabled == true)
			{
				std::cout << std::endl;
				std::cout << "unknown exception occurred" << std::endl;
				std::cout << "current line: " << (currentLine + 1) << std::endl;
				for (std::wstring tok : tokens)
				{
					std::wcout << tok << " ";
				}
				std::cout << std::endl;
				std::cout << "current thread id: " << std::this_thread::get_id() << std::endl;
				std::cout << "main thread id: " << mainThreadId << std::endl;
				std::cout << "call stack: " << std::endl;
				for (auto it = callNameStack.rbegin(); it != callNameStack.rend(); ++it)
				{
					std::wcout << *it << std::endl;
				}
			}
		}
	}
	else
	{
		execLoop(tokens);
	}

	if (detached)
	{
		delete myCodeStore;
		myCodeStore = nullptr;
		delete myWorkspaceStore;
		myWorkspaceStore = nullptr;
		threadCount--;
	}
}

#endif
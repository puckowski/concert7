
#ifndef FILE_LIBRARY_H
#define FILE_LIBRARY_H

#include <vector>
#include <string>

#include "header.h"
#include "Var.h"
#include "variableFunctions.h"

void libraryGetFileSize(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	int r1;
	bool createdString;
	Var* stringVar = getVar(arguments[2], r1, createdString);

	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

	std::wstring* pstr = static_cast<std::wstring*>(stringVar->data);
	int* returnData = static_cast<int*>(v->data);

	returnData[returnVarInt] = gHandleStore.getFileSize(pstr[r1]);

	if (createdString)
	{
		delete stringVar;
	}
}

void libraryIsFileExist(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	int r1;
	bool createdString;
	Var* stringVar = getVar(arguments[2], r1, createdString);

	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

	std::wstring* pstr = static_cast<std::wstring*>(stringVar->data);
	int* returnData = static_cast<int*>(v->data);

	returnData[returnVarInt] = gHandleStore.isFileExist(pstr[r1]);

	if (createdString)
	{
		delete stringVar;
	}
}

void libraryCreateFile(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	int r1;
	bool createdString;
	Var* stringVar = getVar(arguments[2], r1, createdString);

	std::wstring* pstr = static_cast<std::wstring*>(stringVar->data);

	gHandleStore.createFile(pstr[r1]);

	if (createdString)
	{
		delete stringVar;
	}
}

void libraryOpenFile(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	if (argumentsSize == 3)
	{
		int r1;
		bool createdString;
		Var* stringVar = getVar(arguments[2], r1, createdString);

		std::wstring* pstr = static_cast<std::wstring*>(stringVar->data);
		int flag = 0;

		gHandleStore.openFile(pstr[r1], flag);

		if (createdString) 
		{
			delete stringVar;
		}
	}
	else //if (argumentsSize == 4)
	{
		int r1;
		bool createdString;
		Var* stringVar = getVar(arguments[2], r1, createdString);

		int r2;
		bool createdOpenFlag;
		Var* openFlagVar = getVar(arguments[3], r2, createdOpenFlag);

		std::wstring* pstr = static_cast<std::wstring*>(stringVar->data);
		int* flagData = static_cast<int*>(openFlagVar->data);

		gHandleStore.openFile(pstr[r1], flagData[r2]);

		if (createdString)
		{
			delete stringVar;
		}

		if (createdOpenFlag)
		{
			delete openFlagVar;
		}
	}
}

void libraryCreateDirectory(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	int r1;
	bool createdString;
	Var* stringVar = getVar(arguments[2], r1, createdString);

	std::wstring* pstr = static_cast<std::wstring*>(stringVar->data);

	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

	int* returnData = static_cast<int*>(v->data);

	returnData[returnVarInt] = gHandleStore.createDirectory(pstr[r1]);

	if (createdString)
	{
		delete stringVar;
	}
}

void libraryCloseFile(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	int r1;
	bool createdString;
	Var* stringVar = getVar(arguments[2], r1, createdString);

	std::wstring* pstr = static_cast<std::wstring*>(stringVar->data);

	gHandleStore.closeFile(pstr[r1]);

	if (createdString)
	{
		delete stringVar;
	}
}

void libraryRemoveFile(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	int r1;
	bool createdString;
	Var* stringVar = getVar(arguments[2], r1, createdString);

	std::wstring* pstr = static_cast<std::wstring*>(stringVar->data);

	gHandleStore.removeFile(pstr[r1]);

	if (createdString)
	{
		delete stringVar;
	}
}

void libraryRenameFile(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	int r1;
	bool createdString;
	Var* stringVar = getVar(arguments[2], r1, createdString);

	int r2;
	bool createdNewName;
	Var* newNameVar = getVar(arguments[3], r2, createdNewName);

	std::wstring* pstr = static_cast<std::wstring*>(stringVar->data);
	std::wstring* newNameData = static_cast<std::wstring*>(newNameVar->data);

	gHandleStore.renameFile(pstr[r1], newNameData[r2]);

	if (createdString)
	{
		delete stringVar;
	}

	if (createdNewName)
	{
		delete newNameVar;
	}
}

void libraryWriteString(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	int r1;
	bool createdString;
	Var* stringVar = getVar(arguments[2], r1, createdString);

	int r1Text;
	bool createdStringText;
	Var* stringVarText = getVar(arguments[3], r1Text, createdStringText);

	std::wstring* pstr = static_cast<std::wstring*>(stringVar->data);
	std::wstring* pstrText = static_cast<std::wstring*>(stringVarText->data);

	gHandleStore.writeStringToFile(pstr[r1], pstrText[r1Text]);

	if (createdString)
	{
		delete stringVar;
	}

	if (createdStringText)
	{
		delete stringVarText;
	}
}

void libraryGetLine(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	int r1;
	bool createdString;
	Var* stringVar = getVar(arguments[2], r1, createdString);

	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar); 

	std::wstring* pstr = static_cast<std::wstring*>(stringVar->data);
	std::wstring* returnData = static_cast<std::wstring*>(v->data);

	returnData[returnVarInt] = gHandleStore.getLineFromFile(pstr[r1]);

	if (createdString)
	{
		delete stringVar;
	}
}

void libraryIsOpen(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	int r1;
	bool createdString;
	Var* stringVar = getVar(arguments[2], r1, createdString);

	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

	std::wstring* pstr = static_cast<std::wstring*>(stringVar->data);
	int* returnData = static_cast<int*>(v->data);

	returnData[returnVarInt] = gHandleStore.isOpen(pstr[r1]);

	if (createdString)
		delete stringVar;
}

void libraryIsAtEndOfFile(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	int r1;
	bool createdString;
	Var* stringVar = getVar(arguments[2], r1, createdString);

	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar); 

	std::wstring* pstr = static_cast<std::wstring*>(stringVar->data);
	int* returnData = static_cast<int*>(v->data);

	returnData[returnVarInt] = gHandleStore.isAtEndOfFile(pstr[r1]);

	if (createdString)
		delete stringVar;
}

void librarySeek(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	int r1;
	bool createdString;
	Var* stringVar = getVar(arguments[2], r1, createdString);

	int r2;
	bool createdSeek;
	Var* seekVar = getVar(arguments[3], r2, createdSeek);

	std::wstring* pstr = static_cast<std::wstring*>(stringVar->data);
	int* seekData = static_cast<int*>(seekVar->data);

	gHandleStore.seekg(pstr[r1], seekData[r2]);

	if (createdString)
		delete stringVar;

	if (createdSeek)
		delete seekVar;
}

void libraryRead(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	int r1;
	bool createdString;
	Var* stringVar = getVar(arguments[2], r1, createdString);

	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

	std::wstring* pstr = static_cast<std::wstring*>(stringVar->data);
	int* returnData = static_cast<int*>(v->data);

	returnData[returnVarInt] = gHandleStore.read(pstr[r1]);

	if (createdString)
		delete stringVar;
}

void libraryWrite(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	int r1;
	bool createdString;
	Var* stringVar = getVar(arguments[2], r1, createdString);

	int r2;
	bool createdWrite;
	Var* writeVar = getVar(arguments[3], r2, createdWrite);

	std::wstring* pstr = static_cast<std::wstring*>(stringVar->data);
	int* writeData = static_cast<int*>(writeVar->data);
	
	wchar_t data = writeData[0];
	gHandleStore.write(pstr[r1], data);

	if (createdString)
		delete stringVar;

	if (createdWrite)
		delete writeVar;
}

void libraryTell(std::vector<std::wstring> &arguments, const int &argumentsSize)
{
	int r1;
	bool createdString;
	Var* stringVar = getVar(arguments[2], r1, createdString);

	Var* v = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);

	std::wstring* pstr = static_cast<std::wstring*>(stringVar->data);
	int* returnData = static_cast<int*>(v->data);

	returnData[returnVarInt] = gHandleStore.tellg(pstr[r1]);

	if (createdString)
		delete stringVar;
}

#endif
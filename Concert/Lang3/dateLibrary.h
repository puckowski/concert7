
#ifndef DATE_LIBRARY_H
#define DATE_LIBRARY_H

#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>

#include "header.h"
#include "Var.h"
#include "variableFunctions.h"

void libraryDateLocaltime(std::vector<std::wstring>& arguments, const int& argumentsSize)
{
	int r1;
	bool createdVar;
	Var* formatVar = getVar(arguments[2], r1, createdVar);

	switch (formatVar->type)
	{
	case TYPE_STRING:
	{
		std::wstring* pstr = static_cast<std::wstring*>(formatVar->data);
		std::wstring format = pstr[r1];
		const wchar_t* formatCStr = format.c_str();

		auto now = std::chrono::system_clock::now();
		std::time_t now_time = std::chrono::system_clock::to_time_t(now);

		struct tm timeinfo;
		localtime_s(&timeinfo, &now_time);

		std::wstringstream wss;
		wss << std::put_time(&timeinfo, formatCStr);
		std::wstring formatted_datetime = wss.str();

		Var* returnVar = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);
		std::wstring* returnData = static_cast<std::wstring*>(returnVar->data);

		returnData[returnVarInt] = formatted_datetime;

		break;
	}
	}

	if (createdVar) {
		delete formatVar;
	}
}

#endif
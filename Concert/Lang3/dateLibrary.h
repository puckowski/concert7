
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
        formatVar = nullptr;
	}
}

void libraryDateLocaltimeNs(std::vector<std::wstring>& arguments, const int& argumentsSize)
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
        auto now_us = std::chrono::time_point_cast<std::chrono::microseconds>(now);
        auto now_ns = std::chrono::time_point_cast<std::chrono::nanoseconds>(now);

        struct tm timeinfo;
        localtime_s(&timeinfo, &now_time);

        std::wstringstream wss;
        wss << std::put_time(&timeinfo, formatCStr);

        auto duration_since_epoch = now.time_since_epoch();
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration_since_epoch) % 1000;
        auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration_since_epoch) % 1000;
        auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration_since_epoch) % 1000;

        wss << L'.' << std::setw(3) << std::setfill(L'0') << milliseconds.count()
            << L'.' << std::setw(3) << std::setfill(L'0') << microseconds.count()
            << L'.' << std::setw(3) << std::setfill(L'0') << nanoseconds.count();

        std::wstring formatted_datetime = wss.str();

        Var* returnVar = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);
        std::wstring* returnData = static_cast<std::wstring*>(returnVar->data);

        returnData[returnVarInt] = formatted_datetime;

        break;
    }
    }

    if (createdVar) {
        delete formatVar;
        formatVar = nullptr;
    }
}

#endif
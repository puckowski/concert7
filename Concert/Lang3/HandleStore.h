
#ifndef HANDLE_STORE_H
#define HANDLE_STORE_H

#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <filesystem>
#include <locale>
#include <boost/locale.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <locale>
#include <codecvt>
#include "utf8.h"

namespace ConcertHandleEnvironment
{
	class HandleStore
	{
	private:
		std::unordered_map<std::wstring, std::wfstream*> mHandleMap;

	protected:

	public:
		HandleStore();

		~HandleStore();

		void clearStore();
		std::wfstream* getHandle(const std::wstring& name);
		int createDirectory(const std::wstring& name);

		std::ifstream::pos_type getFileSize(const std::wstring& name);

		bool isFileExist(const std::wstring& name);

		void createFile(const std::wstring& name);

		void openFile(const std::wstring& name, int& openFileFlag);

		void closeFile(const std::wstring& name);

		void writeStringToFile(const std::wstring& name, const std::wstring& text);
		std::wstring getLineFromFile(const std::wstring& name);

		bool isOpen(const std::wstring& name);

		bool isAtEndOfFile(const std::wstring& name);

		int removeFile(const std::wstring& name);

		int renameFile(const std::wstring& name, std::wstring& newName);
		void seekg(const std::wstring& name, int& position);

		int tellg(const std::wstring& name);

		int read(const std::wstring& name);

		void write(const std::wstring& name, wchar_t& data);
	};
}

#endif
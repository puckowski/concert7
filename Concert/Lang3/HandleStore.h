
#ifndef HANDLE_STORE_H
#define HANDLE_STORE_H

#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <filesystem>

namespace ConcertHandleEnvironment
{
	class HandleStore
	{
	private:
		std::unordered_map<std::string, std::fstream*> mHandleMap;

	protected:

	public:
		HandleStore();

		~HandleStore();

		void clearStore();
		std::fstream* getHandle(const std::string& name);
		int createDirectory(const std::string& name);

		std::ifstream::pos_type getFileSize(const std::string& name);

		bool isFileExist(const std::string& name);

		void createFile(const std::string& name);

		void openFile(const std::string& name, int& openFileFlag);

		void closeFile(const std::string& name);

		void writeStringToFile(const std::string& name, const std::string& text);
		std::string getLineFromFile(const std::string& name);

		bool isOpen(const std::string& name);

		bool isAtEndOfFile(const std::string& name);

		int removeFile(const std::string& name);

		int renameFile(const std::string& name, std::string& newName);
		void seekg(const std::string& name, int& position);

		int tellg(const std::string& name);

		int read(const std::string& name);

		void write(const std::string& name, char& data);
	};
}

#endif
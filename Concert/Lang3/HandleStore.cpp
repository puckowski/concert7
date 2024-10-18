
#ifndef HANDLE_STORE_CPP
#define HANDLE_STORE_CPP

#include "HandleStore.h"

ConcertHandleEnvironment::HandleStore::HandleStore()
{
}

ConcertHandleEnvironment::HandleStore::~HandleStore()
{
	for (auto handleEntry : mHandleMap)
	{
		if (handleEntry.second != nullptr)
		{
			delete handleEntry.second;
			handleEntry.second = nullptr;
		}
	}

	for (auto handleEntry : mByteHandleMap)
	{
		if (handleEntry.second != nullptr)
		{
			delete handleEntry.second;
			handleEntry.second = nullptr;
		}
	}
}

void ConcertHandleEnvironment::HandleStore::clearStore() {
	for (auto handleEntry : mHandleMap)
	{
		if (handleEntry.second != nullptr)
		{
			delete handleEntry.second;
			handleEntry.second = nullptr;
		}
	}

	for (auto handleEntry : mByteHandleMap)
	{
		if (handleEntry.second != nullptr)
		{
			delete handleEntry.second;
			handleEntry.second = nullptr;
		}
	}
}

std::wfstream* ConcertHandleEnvironment::HandleStore::getHandle(const std::wstring &name)
{
	auto search = mHandleMap.find(name);

	if (search != mHandleMap.end())
	{
		return search->second;
	}

	return nullptr;
}

std::fstream* ConcertHandleEnvironment::HandleStore::getByteHandle(const std::wstring& name)
{
	auto searchByte = mByteHandleMap.find(name);

	if (searchByte != mByteHandleMap.end())
	{
		return searchByte->second;
	}

	return nullptr;
}

int ConcertHandleEnvironment::HandleStore::createDirectory(const std::wstring &name)
{
	return std::filesystem::create_directory(name);
}

std::ifstream::pos_type ConcertHandleEnvironment::HandleStore::getFileSize(const std::wstring &name)
{
	std::ifstream in(name, std::ifstream::ate | std::ifstream::binary);

	return in.tellg();
}

bool ConcertHandleEnvironment::HandleStore::isFileExist(const std::wstring &name)
{
	std::ifstream infile(name);

	return infile.good();
}

void ConcertHandleEnvironment::HandleStore::createFile(const std::wstring &name)
{
	std::fstream* fileStream = new std::fstream();
	fileStream->open(name, std::ios::out);
	fileStream->close();
}

void ConcertHandleEnvironment::HandleStore::openFile(const std::wstring& name, int& openFileFlag)
{
	std::wfstream* fileStream = getHandle(name);

	if (fileStream == nullptr)
	{
		fileStream = new std::wfstream();
	}

	if (openFileFlag == 0)
	{
		fileStream->open(name, std::fstream::in | std::fstream::out);
	}
	else if (openFileFlag == 1)
	{
		fileStream->open(name, std::fstream::in | std::fstream::out | std::fstream::binary);
	}

	auto it = mHandleMap.find(name);
	if (it != mHandleMap.end()) 
	{
		it->second->close();
		mHandleMap.erase(it->first);
		delete it->second;
		it->second = nullptr;
	}

	mHandleMap.insert({ name, fileStream });
}

void ConcertHandleEnvironment::HandleStore::openByteFile(const std::wstring& name, int& openFileFlag)
{
	std::fstream* fileStream = getByteHandle(name);

	if (fileStream == nullptr)
	{
		fileStream = new std::fstream();
	}

	if (openFileFlag == 0)
	{
		fileStream->open(name, std::fstream::in | std::fstream::out);
	}
	else if (openFileFlag == 1)
	{
		fileStream->open(name, std::fstream::in | std::fstream::out | std::fstream::binary);
	}

	auto it = mByteHandleMap.find(name);
	if (it != mByteHandleMap.end())
	{
		it->second->close();
		mByteHandleMap.erase(it->first);
		delete it->second;
		it->second = nullptr;
	}

	mByteHandleMap.insert({ name, fileStream });
}

void ConcertHandleEnvironment::HandleStore::closeFile(const std::wstring &name)
{
	std::wfstream* fileStream = getHandle(name);

	if (fileStream == nullptr)
	{
		std::fstream* byteFileStream = getByteHandle(name);

		if (byteFileStream != nullptr)
		{
			byteFileStream->flush();

			byteFileStream->close();
			mByteHandleMap.erase(name);
			delete byteFileStream;
			byteFileStream = nullptr;
		}
	}
	else
	{
		fileStream->flush();

		fileStream->close();
		mHandleMap.erase(name);
		delete fileStream;
		fileStream = nullptr;
	}
}

void ConcertHandleEnvironment::HandleStore::writeStringToFile(const std::wstring &name, const std::wstring &text)
{
	std::wfstream* handle = getHandle(name);

	if (handle != nullptr)
	{
		*handle << text;
	}
	else
	{
		std::fstream* byteHandle = getByteHandle(name);

		if (byteHandle != nullptr)
		{
			std::string str = boost::locale::conv::utf_to_utf<char>(text);
			*byteHandle << str;
		}

	}
}

std::wstring ConcertHandleEnvironment::HandleStore::getLineFromFile(const std::wstring &name)
{
	std::wstring line;

	auto handle = getHandle(name);

	if (handle != nullptr)
	{
		std::getline(*handle, line);
	}
	else
	{
		auto byteHandle = getByteHandle(name);

		std::string str;
		std::getline(*byteHandle, str);
		line = utf8_to_wstring(str);
	}

	return line;
}

bool ConcertHandleEnvironment::HandleStore::isOpen(const std::wstring &name)
{
	auto handle = getHandle(name);
	
	if (handle != nullptr)
	{
		return handle->is_open();
	}
	else
	{
		auto byteHandle = getByteHandle(name);

		if (byteHandle != nullptr)
		{
			return byteHandle->is_open();
		}
	}

	return false;
}

bool ConcertHandleEnvironment::HandleStore::isAtEndOfFile(const std::wstring &name)
{
	auto handle = getHandle(name);

	if (handle != nullptr)
	{
		return handle->eof();
	}
	else
	{
		auto byteHandle = getByteHandle(name);

		if (byteHandle != nullptr)
		{
			return byteHandle->eof();
		}
	}

	return true;
}

int ConcertHandleEnvironment::HandleStore::removeFile(const std::wstring &name)
{
	int result = std::remove(wstring_to_utf8(name).c_str());

	auto handle = getHandle(name);

	if (handle != nullptr)
	{
		handle->close();
		mHandleMap.erase(name);
		delete handle;
		handle = nullptr;
	}
	else
	{
		auto byteHandle = getByteHandle(name);

		if (byteHandle != nullptr)
		{
			byteHandle->close();
			mByteHandleMap.erase(name);
			delete byteHandle;
			byteHandle = nullptr;
		}
	}

	return result;
}

int ConcertHandleEnvironment::HandleStore::renameFile(const std::wstring &name, std::wstring &newName)
{
	int result = std::rename(wstring_to_utf8(name).c_str(), wstring_to_utf8(newName).c_str());

	return result;
}

void ConcertHandleEnvironment::HandleStore::seekg(const std::wstring &name, int &position)
{
	auto handle = getHandle(name);

	if (handle != nullptr)
	{
		handle->seekg(position);

		handle->seekp(position);
	}
	else
	{
		auto byteHandle = getByteHandle(name);

		if (byteHandle != nullptr)
		{
			byteHandle->seekg(position);

			byteHandle->seekp(position);
		}
	}
}

int ConcertHandleEnvironment::HandleStore::tellg(const std::wstring &name)
{
	auto handle = getHandle(name);

	if (handle != nullptr)
	{
		return handle->tellg();
	}
	else
	{
		auto byteHandle = getByteHandle(name);

		if (byteHandle != nullptr)
		{
			return byteHandle->tellg();
		}
	}

	return 0;
}

int ConcertHandleEnvironment::HandleStore::read(const std::wstring &name)
{
	wchar_t data;
	getHandle(name)->read(&data, 1);
	int returnValue = data;

	return returnValue;
}

int ConcertHandleEnvironment::HandleStore::readByte(const std::wstring& name)
{
	char data;
	getByteHandle(name)->read(&data, 1);
	int returnValue = data;

	return returnValue;
}

void ConcertHandleEnvironment::HandleStore::write(const std::wstring& name, wchar_t& data)
{
	getHandle(name)->write(reinterpret_cast<const wchar_t*>(&data), sizeof(wchar_t));
}

void ConcertHandleEnvironment::HandleStore::writeByte(const std::wstring& name, char& data)
{
	getByteHandle(name)->write(reinterpret_cast<const char*>(&data), sizeof(char));
}

#endif
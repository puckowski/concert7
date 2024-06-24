
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
		}
	}
}

void ConcertHandleEnvironment::HandleStore::clearStore() {
	for (auto handleEntry : mHandleMap)
	{
		if (handleEntry.second != nullptr)
		{
			delete handleEntry.second;
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

void ConcertHandleEnvironment::HandleStore::openFile(const std::wstring &name, int &openFileFlag)
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

	mHandleMap.insert({ name, fileStream });
}

void ConcertHandleEnvironment::HandleStore::closeFile(const std::wstring &name)
{
	std::wfstream* fileStream = getHandle(name);

	if (fileStream == nullptr)
	{
		return;
	}

	fileStream->flush();

	fileStream->close();
	mHandleMap.erase(name);
}

void ConcertHandleEnvironment::HandleStore::writeStringToFile(const std::wstring &name, const std::wstring &text)
{
	std::wfstream* handle = getHandle(name);

	*handle << text;
}

std::wstring ConcertHandleEnvironment::HandleStore::getLineFromFile(const std::wstring &name)
{
	std::wstring line;
	std::getline(*getHandle(name), line);

	return line;
}

bool ConcertHandleEnvironment::HandleStore::isOpen(const std::wstring &name)
{
	return getHandle(name)->is_open();
}

bool ConcertHandleEnvironment::HandleStore::isAtEndOfFile(const std::wstring &name)
{
	return getHandle(name)->eof();
}

int ConcertHandleEnvironment::HandleStore::removeFile(const std::wstring &name)
{
	int result = std::remove(wstring_to_utf8(name).c_str());
	mHandleMap.erase(name);

	return result;
}

int ConcertHandleEnvironment::HandleStore::renameFile(const std::wstring &name, std::wstring &newName)
{
	int result = std::rename(wstring_to_utf8(name).c_str(), wstring_to_utf8(newName).c_str());

	return result;
}

void ConcertHandleEnvironment::HandleStore::seekg(const std::wstring &name, int &position)
{
	getHandle(name)->seekg(position);

	getHandle(name)->seekp(position);
}

int ConcertHandleEnvironment::HandleStore::tellg(const std::wstring &name)
{
	return getHandle(name)->tellg();
}

int ConcertHandleEnvironment::HandleStore::read(const std::wstring &name)
{
	wchar_t data;
	getHandle(name)->read(&data, 1);
	int returnValue = data;

	return returnValue;
}

void ConcertHandleEnvironment::HandleStore::write(const std::wstring &name, wchar_t &data)
{
	getHandle(name)->write(reinterpret_cast<const wchar_t*>(&data), sizeof(char));
}

#endif
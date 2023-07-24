
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

std::fstream* ConcertHandleEnvironment::HandleStore::getHandle(const std::string &name)
{
	auto search = mHandleMap.find(name);

	if (search != mHandleMap.end())
	{
		return search->second;
	}

	return nullptr;
}

int ConcertHandleEnvironment::HandleStore::createDirectory(const std::string &name)
{
	return std::filesystem::create_directory(name);
}

std::ifstream::pos_type ConcertHandleEnvironment::HandleStore::getFileSize(const std::string &name)
{
	std::ifstream in(name, std::ifstream::ate | std::ifstream::binary);

	return in.tellg();
}

bool ConcertHandleEnvironment::HandleStore::isFileExist(const std::string &name)
{
	std::ifstream infile(name);

	return infile.good();
}

void ConcertHandleEnvironment::HandleStore::createFile(const std::string &name)
{
	std::fstream* fileStream = new std::fstream();
	fileStream->open(name, std::ios::out);
	fileStream->close();
}

void ConcertHandleEnvironment::HandleStore::openFile(const std::string &name, int &openFileFlag)
{
	std::fstream* fileStream = getHandle(name);

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

	mHandleMap.insert({ name, fileStream });
}

void ConcertHandleEnvironment::HandleStore::closeFile(const std::string &name)
{
	std::fstream* fileStream = getHandle(name);

	if (fileStream == nullptr)
	{
		return;
	}

	fileStream->flush();

	fileStream->close();
	mHandleMap.erase(name);
}

void ConcertHandleEnvironment::HandleStore::writeStringToFile(const std::string &name, const std::string &text)
{
	std::fstream* handle = getHandle(name);

	*handle << text;
}

std::string ConcertHandleEnvironment::HandleStore::getLineFromFile(const std::string &name)
{
	std::string line;
	std::getline(*getHandle(name), line);

	return line;
}

bool ConcertHandleEnvironment::HandleStore::isOpen(const std::string &name)
{
	return getHandle(name)->is_open();
}

bool ConcertHandleEnvironment::HandleStore::isAtEndOfFile(const std::string &name)
{
	return getHandle(name)->eof();
}

int ConcertHandleEnvironment::HandleStore::removeFile(const std::string &name)
{
	int result = std::remove(name.c_str());
	mHandleMap.erase(name);

	return result;
}

int ConcertHandleEnvironment::HandleStore::renameFile(const std::string &name, std::string &newName)
{
	int result = std::rename(name.c_str(), newName.c_str());

	return result;
}

void ConcertHandleEnvironment::HandleStore::seekg(const std::string &name, int &position)
{
	getHandle(name)->seekg(position);

	getHandle(name)->seekp(position);
}

int ConcertHandleEnvironment::HandleStore::tellg(const std::string &name)
{
	return getHandle(name)->tellg();
}

int ConcertHandleEnvironment::HandleStore::read(const std::string &name)
{
	char data;
	getHandle(name)->read(&data, 1);
	int returnValue = data;

	return returnValue;
}

void ConcertHandleEnvironment::HandleStore::write(const std::string &name, char &data)
{
	getHandle(name)->write(reinterpret_cast<const char*>(&data), sizeof(char));
}

#endif
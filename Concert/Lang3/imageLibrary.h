
#ifndef IMAGE_LIBRARY_H
#define IMAGE_LIBRARY_H

#include <iostream>
#include <string>
#include <iostream>

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_STATIC
#define STB_IMAGE_WRITE_IMPLEMENTATION
#pragma warning(disable:4996)
#include "stb_image_write.h"

#include "lodepng.h"

#include "header.h"
#include "Var.h"
#include "variableFunctions.h"

bool endsWith(const std::wstring& str, const std::wstring& suffix) {
	if (str.size() < suffix.size()) {
		return false;
	}
	return str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

std::wstring toLowercase(const std::wstring& str) {
	std::wstring result = str;
	std::transform(result.begin(), result.end(), result.begin(),
		[](unsigned char c) { return std::tolower(c); });
	return result;
}

void libraryImageWriteChannelData(std::vector<std::wstring>& arguments, const int& argumentsSize)
{
	int r1;
	bool createdVar = false;
	Var* v = getVar(arguments[3], r1, createdVar);
	std::wstring* pstr = static_cast<std::wstring*>(v->data);
	const std::wstring varName = pstr[r1];

	int quality = 100;

	if (argumentsSize >= 5 && arguments[4] != L"->")
	{
		int r3;
		bool createdQualityVar = false;
		Var* v3 = getVar(arguments[4], r3, createdQualityVar);
		int* pstr3 = static_cast<int*>(v3->data);
		quality = pstr3[r3];

		if (createdQualityVar)
		{
			delete v3;
			v3 = nullptr;
		}
	}

	r1 = 0;
	ObjectStore** var = static_cast<ObjectStore**>(gWorkspaceStore->getStore()->getVar(varName, r1)->data);
	ObjectStore* obj = var[r1];

	int r2;
	bool createdFileVar = false;
	Var* v2 = getVar(arguments[2], r2, createdFileVar);
	std::wstring* pstr2 = static_cast<std::wstring*>(v2->data);
	const std::wstring fileName = pstr2[r2];

	const std::wstring lowercaseFileName = toLowercase(fileName);

	if (endsWith(lowercaseFileName, L".jpg") || endsWith(lowercaseFileName, L".jpeg"))
	{
		std::string utf8Str = wstring_to_utf8(fileName);

		char* cstr = new char[utf8Str.size() + 1];

		strcpy_s(cstr, utf8Str.size() + 1, utf8Str.c_str());

		r1 = 0;
		int index;
		Var* dataVar = obj->getVar(L"red", r1);
		int* pstrData1 = static_cast<int*>(dataVar->data);
		const int channelSize = dataVar->size;

		r1 = 0;
		dataVar = obj->getVar(L"green", r1);
		int* pstrData2 = static_cast<int*>(dataVar->data);

		r1 = 0;
		dataVar = obj->getVar(L"blue", r1);
		int* pstrData3 = static_cast<int*>(dataVar->data);

		int r3 = 0;
		dataVar = obj->getVar(L"width", r3);
		int* pstrData4 = static_cast<int*>(dataVar->data);

		int r4 = 0;
		dataVar = obj->getVar(L"height", r4);
		int* pstrData5 = static_cast<int*>(dataVar->data);

		unsigned char* rgbImage = new unsigned char[channelSize * 3];

		for (index = 0; index < channelSize; ++index) {
			rgbImage[index * 3] = pstrData1[index];
			rgbImage[index * 3 + 1] = pstrData2[index];
			rgbImage[index * 3 + 2] = pstrData3[index];
		}

		Var* returnVar = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);
		int* returnData = static_cast<int*>(returnVar->data);

		if (stbi_write_jpg(cstr, pstrData4[r3], pstrData5[r4], 3, rgbImage, quality)) {
			returnData[returnVarInt] = 1;
		}
		else {
			returnData[returnVarInt] = 0;
		}

		delete[] rgbImage;
		rgbImage = nullptr;
		delete[] cstr;
		cstr = nullptr;
	}
	else if (endsWith(lowercaseFileName, L".png"))
	{
		std::string utf8Str = wstring_to_utf8(fileName);

		char* cstr = new char[utf8Str.size() + 1];

		strcpy_s(cstr, utf8Str.size() + 1, utf8Str.c_str());

		r1 = 0;
		int index;
		Var* dataVar = obj->getVar(L"red", r1);
		int* pstrData1 = static_cast<int*>(dataVar->data);
		const int channelSize = dataVar->size;

		r1 = 0;
		dataVar = obj->getVar(L"green", r1);
		int* pstrData2 = static_cast<int*>(dataVar->data);

		r1 = 0;
		dataVar = obj->getVar(L"blue", r1);
		int* pstrData3 = static_cast<int*>(dataVar->data);

		r1 = 0;
		dataVar = obj->getVar(L"alpha", r1);
		int* pstrData6 = static_cast<int*>(dataVar->data);

		int r3 = 0;
		dataVar = obj->getVar(L"width", r3);
		int* pstrData4 = static_cast<int*>(dataVar->data);

		int r4 = 0;
		dataVar = obj->getVar(L"height", r4);
		int* pstrData5 = static_cast<int*>(dataVar->data);

		unsigned char* rgbImage = new unsigned char[channelSize * 4];

		for (index = 0; index < channelSize; ++index) {
			rgbImage[index * 4] = pstrData1[index];
			rgbImage[index * 4 + 1] = pstrData2[index];
			rgbImage[index * 4 + 2] = pstrData3[index];
			rgbImage[index * 4 + 3] = pstrData6[index];
		}

		Var* returnVar = getVar(arguments[argumentsSize - 1], returnVarInt, createdRetVar);
		int* returnData = static_cast<int*>(returnVar->data);

		unsigned error = lodepng::encode(cstr, rgbImage, pstrData4[r3], pstrData5[r4]);

		if (!error) {
			returnData[returnVarInt] = 1;
		}
		else {
			returnData[returnVarInt] = 0;
		}

		delete[] rgbImage;
		rgbImage = nullptr;
		delete[] cstr;
		cstr = nullptr;
	}

	if (createdVar) {
		delete v;
		v = nullptr;
	}

	if (createdFileVar) {
		delete v2;
		v2 = nullptr;
	}
}

void libraryImageReadChannelData(std::vector<std::wstring>& arguments, const int& argumentsSize)
{
	int r1;
	bool createdVar = false;
	Var* v = getVar(arguments[3], r1, createdVar);
	std::wstring* pstr = static_cast<std::wstring*>(v->data);
	const std::wstring varName = pstr[r1];

	gWorkspaceStore->getStore()->addVar(new Var(varName, TYPE_OBJECT, 1));

	int r2;
	bool createdFileVar = false;
	Var* v2 = getVar(arguments[2], r2, createdFileVar);
	std::wstring* pstr2 = static_cast<std::wstring*>(v2->data);
	const std::wstring fileName = pstr2[r2];

	const std::wstring lowercaseFileName = toLowercase(fileName);

	if (endsWith(lowercaseFileName, L".jpg") || endsWith(lowercaseFileName, L".jpeg")) {
		std::string utf8Str = wstring_to_utf8(fileName);

		char* cstr = new char[utf8Str.size() + 1];

		strcpy_s(cstr, utf8Str.size() + 1, utf8Str.c_str());

		int width, height, channels;

		unsigned char* imgData = stbi_load(cstr, &width, &height, &channels, 3);

		r1 = 0;
		ObjectStore** var = static_cast<ObjectStore**>(gWorkspaceStore->getStore()->getVar(varName, r1)->data);
		ObjectStore* obj = var[r1];

		if (imgData == nullptr) {
			obj->addVar(L"red", TYPE_INT, 0);
			obj->addVar(L"green", TYPE_INT, 0);
			obj->addVar(L"blue", TYPE_INT, 0);
			obj->addVar(L"width", TYPE_INT, 0);
			obj->addVar(L"height", TYPE_INT, 0);
		}
		else {
			const int size = width * height;

			unsigned char* redChannel = new unsigned char[size];
			unsigned char* greenChannel = new unsigned char[size];
			unsigned char* blueChannel = new unsigned char[size];

			int index;

			for (index = 0; index < size; ++index) {
				redChannel[index] = imgData[index * 3];      // Red channel
				greenChannel[index] = imgData[index * 3 + 1];// Green channel
				blueChannel[index] = imgData[index * 3 + 2]; // Blue channel
			}

			stbi_image_free(imgData);

			obj->addVar(L"red", TYPE_INT, size);
			r1 = 0;
			Var* dataVar = obj->getVar(L"red", r1);
			int* pstrData = static_cast<int*>(dataVar->data);
			for (index = 0; index < size; ++index) {
				pstrData[index] = redChannel[index];
			}

			obj->addVar(L"green", TYPE_INT, size);
			r1 = 0;
			dataVar = obj->getVar(L"green", r1);
			pstrData = static_cast<int*>(dataVar->data);
			for (index = 0; index < size; ++index) {
				pstrData[index] = greenChannel[index];
			}

			obj->addVar(L"blue", TYPE_INT, size);
			r1 = 0;
			dataVar = obj->getVar(L"blue", r1);
			pstrData = static_cast<int*>(dataVar->data);
			for (index = 0; index < size; ++index) {
				pstrData[index] = blueChannel[index];
			}

			obj->addVar(L"width", TYPE_INT, 1);
			r1 = 0;
			dataVar = obj->getVar(L"width", r1);
			pstrData = static_cast<int*>(dataVar->data);
			pstrData[0] = width;

			obj->addVar(L"height", TYPE_INT, 1);
			r1 = 0;
			dataVar = obj->getVar(L"height", r1);
			pstrData = static_cast<int*>(dataVar->data);
			pstrData[0] = height;

			delete[] redChannel;
			redChannel = nullptr;
			delete[] greenChannel;
			greenChannel = nullptr;
			delete[] blueChannel;
			blueChannel = nullptr;

			delete[] cstr;
			cstr = nullptr;
		}
	}
	else if (endsWith(lowercaseFileName, L".png"))
	{
		std::string utf8Str = wstring_to_utf8(fileName);

		char* cstr = new char[utf8Str.size() + 1];

		strcpy_s(cstr, utf8Str.size() + 1, utf8Str.c_str());

		unsigned error;
		unsigned char* imgData = 0;
		unsigned width, height;

		error = lodepng_decode32_file(&imgData, &width, &height, cstr);

		r1 = 0;
		ObjectStore** var = static_cast<ObjectStore**>(gWorkspaceStore->getStore()->getVar(varName, r1)->data);
		ObjectStore* obj = var[r1];

		if (error)
		{
			obj->addVar(L"red", TYPE_INT, 0);
			obj->addVar(L"green", TYPE_INT, 0);
			obj->addVar(L"blue", TYPE_INT, 0);
			obj->addVar(L"width", TYPE_INT, 0);
			obj->addVar(L"height", TYPE_INT, 0);
		}
		else {
			const int size = width * height;

			unsigned char* redChannel = new unsigned char[size];
			unsigned char* greenChannel = new unsigned char[size];
			unsigned char* blueChannel = new unsigned char[size];
			unsigned char* alphaChannel = new unsigned char[size];

			int index;

			for (index = 0; index < size; ++index) {
				redChannel[index] = imgData[index * 4];
				greenChannel[index] = imgData[index * 4 + 1];
				blueChannel[index] = imgData[index * 4 + 2];
				alphaChannel[index] = imgData[index * 4 + 3];
			}

			stbi_image_free(imgData);

			obj->addVar(L"red", TYPE_INT, size);
			r1 = 0;
			Var* dataVar = obj->getVar(L"red", r1);
			int* pstrData = static_cast<int*>(dataVar->data);
			for (index = 0; index < size; ++index) {
				pstrData[index] = redChannel[index];
			}

			obj->addVar(L"green", TYPE_INT, size);
			r1 = 0;
			dataVar = obj->getVar(L"green", r1);
			pstrData = static_cast<int*>(dataVar->data);
			for (index = 0; index < size; ++index) {
				pstrData[index] = greenChannel[index];
			}

			obj->addVar(L"blue", TYPE_INT, size);
			r1 = 0;
			dataVar = obj->getVar(L"blue", r1);
			pstrData = static_cast<int*>(dataVar->data);
			for (index = 0; index < size; ++index) {
				pstrData[index] = blueChannel[index];
			}

			obj->addVar(L"alpha", TYPE_INT, size);
			r1 = 0;
			dataVar = obj->getVar(L"alpha", r1);
			pstrData = static_cast<int*>(dataVar->data);
			for (index = 0; index < size; ++index) {
				pstrData[index] = alphaChannel[index];
			}

			obj->addVar(L"width", TYPE_INT, 1);
			r1 = 0;
			dataVar = obj->getVar(L"width", r1);
			pstrData = static_cast<int*>(dataVar->data);
			pstrData[0] = width;

			obj->addVar(L"height", TYPE_INT, 1);
			r1 = 0;
			dataVar = obj->getVar(L"height", r1);
			pstrData = static_cast<int*>(dataVar->data);
			pstrData[0] = height;

			delete[] redChannel;
			redChannel = nullptr;
			delete[] greenChannel;
			greenChannel = nullptr;
			delete[] blueChannel;
			blueChannel = nullptr;
			delete[] alphaChannel;
			alphaChannel = nullptr;

			delete[] cstr;
			cstr = nullptr;
		}
	}

	if (createdVar) {
		delete v;
		v = nullptr;
	}

	if (createdFileVar) {
		delete v2;
		v2 = nullptr;
	}
}

#endif
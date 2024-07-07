
#ifndef STANDARD_LIBRARY_H
#define STANDARD_LIBRARY_H

#include <map>
#include <vector>
#include <string>

enum LibraryFunction
{
	STRING_SUBSTRING = 0,
	STRING_FIND = 1,
	STRING_CONTAINS = 2,
	STRING_LENGTH = 3,
	STRING_TO_INT = 4,
	STRING_TO_DOUBLE = 5,
	FILE_OPEN_FILE = 7,
	FILE_CLOSE_FILE = 8,
	FILE_WRITE_STRING = 9,
	FILE_GET_LINE = 11,
	FILE_IS_OPEN = 13,
	FILE_IS_EOF = 14,
	FILE_IS_EXIST = 15,
	FILE_CREATE_FILE = 16,
	FILE_GET_FILE_SIZE = 17,
	STRING_CHAR_AT = 18,
	MATH_SRAND = 19,
	MATH_RAND = 20,
	FILE_SEEK = 23,
	FILE_READ = 24,
	FILE_WRITE = 25,
	FILE_REMOVE = 26,
	FILE_RENAME = 27,
	FILE_TELLG = 28,
	STRING_CHAR_TO_STRING = 29,
	STRING_INT_TO_STRING = 30,
	STRING_DOUBLE_TO_STRING = 31,
	MATH_INT_TO_DOUBLE = 32,
	MATH_DOUBLE_TO_INT = 33,
	MATH_INT_TO_LONG = 35,
	STRING_TO_LOWER_CASE = 36,
	STRING_TO_UPPER_CASE = 37,
	FILE_CREATE_DIRECTORY = 38,
	MATH_LONG_TO_INT = 39,
	MATH_LONG_TO_DOUBLE = 40,
	MATH_DOUBLE_TO_LONG = 41,
	REGEX_SEARCH = 42,
	REGEX_MATCH = 43,
	REGEX_REPLACE = 44,
	THREAD_GET_THREAD_ID = 45,
	MATH_ABSOLUTE_VALUE = 46,
	STRING_WCHAR_TO_STRING = 47,
	FILE_OPEN_BYTE_FILE = 48,
	FILE_WRITE_WCHAR = 49,
	FILE_READ_WCHAR = 50,
	STRING_WCHAR_TO_INT = 51,
	STRING_WCHAR_AT = 52,
	MATH_LOG10 = 53,
	MATH_SQRT = 54,
	MATH_ROUND = 55,
	MATH_FLOOR = 56,
	MATH_CEIL = 57,
	MATH_SIN = 58,
	MATH_COS = 59,
	MATH_TAN = 60
};

std::vector<std::wstring>* stringLibraryFunctions = new std::vector<std::wstring>{ L"substring" , L"find", L"contains", L"length", L"to_int", L"to_double", L"char_at", L"wchar_at", L"char_to_string", L"wchar_to_string",
	L"int_to_string", L"double_to_string", L"wchar_to_int", L"to_lower_case", L"to_upper_case" };
std::vector<std::wstring>* fileLibraryFunctions = new std::vector<std::wstring>{ L"open_file",  L"open_byte_file", L"close_file", L"write_string", L"get_line", L"is_open", L"is_end",
	L"is_file_exist", L"create_file", L"get_file_size", L"seek_file_pointer", L"read_byte", L"write_byte", L"read_wchar", L"write_wchar", L"remove_file", L"rename_file", L"tell_file_pointer",
	L"create_directory" };
std::vector<std::wstring>* mathLibraryFunctions = new std::vector<std::wstring>{ L"seed_random", L"get_random", L"int_to_double", L"double_to_int", L"int_to_long", L"long_to_int",
	L"long_to_double", L"double_to_long", L"absolute_value", L"sqrt", L"log10", L"round", L"floor", L"ceil", L"sin", L"cos", L"tan" };
std::vector<std::wstring>* regexLibraryFunctions = new std::vector<std::wstring>{ L"regex_search", L"regex_match", L"regex_replace" };
std::vector<std::wstring>* threadLibraryFunctions = new std::vector<std::wstring>{ L"get_thread_id" };

thread_local const std::map<const std::wstring, std::vector<std::wstring>*> LIBRARY_IMPORT_MAP =
{
	{ L"string", stringLibraryFunctions },
	{ L"io", fileLibraryFunctions },
	{ L"math", mathLibraryFunctions },
	{ L"regex", regexLibraryFunctions },
	{ L"thread", threadLibraryFunctions }
};

const std::map<const std::wstring, const LibraryFunction> LIBRARY_FUNCTION_MAP =
{
	{ L"substring", STRING_SUBSTRING },
	{ L"find", STRING_FIND },
	{ L"contains", STRING_CONTAINS },
	{ L"length", STRING_LENGTH },
	{ L"to_int", STRING_TO_INT },
	{ L"to_double", STRING_TO_DOUBLE },
	{ L"open_file", FILE_OPEN_FILE },
	{ L"open_byte_file", FILE_OPEN_BYTE_FILE },
	{ L"close_file", FILE_CLOSE_FILE },
	{ L"write_string", FILE_WRITE_STRING },
	{ L"get_line", FILE_GET_LINE },
	{ L"is_open", FILE_IS_OPEN },
	{ L"is_end", FILE_IS_EOF },
	{ L"is_file_exist", FILE_IS_EXIST },
	{ L"create_file", FILE_CREATE_FILE },
	{ L"get_file_size", FILE_GET_FILE_SIZE },
	{ L"char_at", STRING_CHAR_AT },
	{ L"wchar_at", STRING_WCHAR_AT },
	{ L"seed_random", MATH_SRAND },
	{ L"get_random", MATH_RAND },
	{ L"seek_file_pointer", FILE_SEEK },
	{ L"read_byte", FILE_READ },
	{ L"write_byte", FILE_WRITE },
	{ L"read_wchar", FILE_READ_WCHAR },
	{ L"write_wchar", FILE_WRITE_WCHAR },
	{ L"remove_file", FILE_REMOVE },
	{ L"rename_file", FILE_RENAME },
	{ L"tell_file_pointer", FILE_TELLG },
	{ L"char_to_string", STRING_CHAR_TO_STRING },
	{ L"int_to_string", STRING_INT_TO_STRING},
	{ L"double_to_string", STRING_DOUBLE_TO_STRING },
	{ L"int_to_double", MATH_INT_TO_DOUBLE },
	{ L"double_to_int", MATH_DOUBLE_TO_INT },
	{ L"wchar_to_int", STRING_WCHAR_TO_INT },
	{ L"int_to_long", MATH_INT_TO_LONG },
	{ L"to_lower_case", STRING_TO_LOWER_CASE },
	{ L"to_upper_case", STRING_TO_UPPER_CASE },
	{ L"create_directory", FILE_CREATE_DIRECTORY },
	{ L"long_to_int", MATH_LONG_TO_INT },
	{ L"long_to_double", MATH_LONG_TO_DOUBLE },
	{ L"double_to_long", MATH_DOUBLE_TO_LONG },
	{ L"regex_search", REGEX_SEARCH },
	{ L"regex_match", REGEX_MATCH },
	{ L"regex_replace", REGEX_REPLACE },
	{ L"get_thread_id", THREAD_GET_THREAD_ID },
	{ L"absolute_value", MATH_ABSOLUTE_VALUE },
	{ L"wchar_to_string", STRING_WCHAR_TO_STRING },
	{ L"sqrt", MATH_SQRT },
	{ L"log10", MATH_LOG10 },
	{ L"round", MATH_ROUND },
	{ L"floor", MATH_FLOOR },
	{ L"ceil", MATH_CEIL },
	{ L"sin", MATH_SIN },
	{ L"cos", MATH_COS },
	{ L"tan", MATH_TAN }
};
const std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<const std::wstring, const LibraryFunction>>>> LIBRARY_FUNCTION_MAP_END = LIBRARY_FUNCTION_MAP.end();

#endif
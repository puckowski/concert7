
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
	STRING_CHAR_TO_INT = 34,
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
	GET_THREAD_ID = 45,
	ABSOLUTE_VALUE = 46
};

std::vector<std::string>* stringLibraryFunctions = new std::vector<std::string>{ "substring" , "find", "contains", "length", "to_int", "to_double", "char_at", "char_to_string", 
	"int_to_string", "double_to_string", "char_to_int", "to_lower_case", "to_upper_case" };
std::vector<std::string>* fileLibraryFunctions = new std::vector<std::string>{ "open_file", "close_file", "write_string", "get_line", "is_open", "is_end",
	"is_file_exist", "create_file", "get_file_size", "seek_file_pointer", "read_byte", "write_byte", "remove_file", "rename_file", "tell_file_pointer",
	"create_directory" };
std::vector<std::string>* mathLibraryFunctions = new std::vector<std::string>{ "seed_random", "get_random", "int_to_double", "double_to_int", "int_to_long", "long_to_int",
	"long_to_double", "double_to_long", "absolute_value" };
std::vector<std::string>* regexLibraryFunctions = new std::vector<std::string>{ "regex_search", "regex_match", "regex_replace" };
std::vector<std::string>* threadLibraryFunctions = new std::vector<std::string>{ "get_thread_id" };

thread_local const std::map<const std::string, std::vector<std::string>*> LIBRARY_IMPORT_MAP =
{
	{ "string", stringLibraryFunctions },
	{ "io", fileLibraryFunctions },
	{ "math", mathLibraryFunctions },
	{ "regex", regexLibraryFunctions },
	{ "thread", threadLibraryFunctions }
};

const std::map<const std::string, const LibraryFunction> LIBRARY_FUNCTION_MAP =
{
	{ "substring", STRING_SUBSTRING },
	{ "find", STRING_FIND },
	{ "contains", STRING_CONTAINS },
	{ "length", STRING_LENGTH },
	{ "to_int", STRING_TO_INT },
	{ "to_double", STRING_TO_DOUBLE },
	{ "open_file", FILE_OPEN_FILE },
	{ "close_file", FILE_CLOSE_FILE },
	{ "write_string", FILE_WRITE_STRING },
	{ "get_line", FILE_GET_LINE },
	{ "is_open", FILE_IS_OPEN },
	{ "is_end", FILE_IS_EOF },
	{ "is_file_exist", FILE_IS_EXIST },
	{ "create_file", FILE_CREATE_FILE },
	{ "get_file_size", FILE_GET_FILE_SIZE },
	{ "char_at", STRING_CHAR_AT },
	{ "seed_random", MATH_SRAND },
	{ "get_random", MATH_RAND },
	{ "seek_file_pointer", FILE_SEEK },
	{ "read_byte", FILE_READ },
	{ "write_byte", FILE_WRITE },
	{ "remove_file", FILE_REMOVE },
	{ "rename_file", FILE_RENAME },
	{ "tell_file_pointer", FILE_TELLG },
	{ "char_to_string", STRING_CHAR_TO_STRING },
	{ "int_to_string", STRING_INT_TO_STRING },
	{ "double_to_string", STRING_DOUBLE_TO_STRING },
	{ "int_to_double", MATH_INT_TO_DOUBLE },
	{ "double_to_int", MATH_DOUBLE_TO_INT },
	{ "char_to_int", STRING_CHAR_TO_INT },
	{ "int_to_long", MATH_INT_TO_LONG },
	{ "to_lower_case", STRING_TO_LOWER_CASE },
	{ "to_upper_case", STRING_TO_UPPER_CASE },
	{ "create_directory", FILE_CREATE_DIRECTORY },
	{ "long_to_int", MATH_LONG_TO_INT },
	{ "long_to_double", MATH_LONG_TO_DOUBLE },
	{ "double_to_long", MATH_DOUBLE_TO_LONG },
	{ "regex_search", REGEX_SEARCH },
	{ "regex_match", REGEX_MATCH },
	{ "regex_replace", REGEX_REPLACE },
	{ "get_thread_id", GET_THREAD_ID },
	{ "absolute_value", ABSOLUTE_VALUE }
};
const std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<const std::string, const LibraryFunction>>>> LIBRARY_FUNCTION_MAP_END = LIBRARY_FUNCTION_MAP.end();

#endif
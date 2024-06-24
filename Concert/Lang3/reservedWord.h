
#ifndef RESERVED_WORD_H
#define RESERVED_WORD_H

#include <map>

enum ReservedWord
{
	TYPE_INT = 0,
	TYPE_DOUBLE = 1,
	TYPE_LONG = 3,
	TYPE_STRING = 2,
	TYPE_FUNCTION = 5,
	KEYWORD_RETURN = 7,
	KEYWORD_CALL = 8,
	KEYWORD_END = 9,
	KEYWORD_IF = 10,
	KEYWORD_WHILE = 11,
	KEYWORD_SIZEOF = 12,
	KEYWORD_INCLUDE = 13,
	KEYWORD_IMPORT = 14,
	KEYWORD_DETACH = 15,
	KEYWORD_JOIN = 19,
	KEYWORD_PRINTLN = 20,
	KEYWORD_PRINT = 21,
	KEYWORD_READ = 22,
	KEYWORD_READLN = 23,
	KEYWORD_LOCK = 24,
	KEYWORD_UNLOCK = 25,
	KEYWORD_BREAK = 26,
	KEYWORD_TRY = 28,
	KEYWORD_CATCH = 29,
	KEYWORD_DELETE = 30,
	KEYWORD_MUTEX = 31,
	KEYWORD_ELSE = 33,
	KEYWORD_SYSTEM = 34,
	KEYWORD_EXEC = 35,
	KEYWORD_EXIT = 36,
	KEYWORD_INSTANCEOF = 37,
	KEYWORD_NEW = 39,
	KEYWORD_CONTINUE = 40,
	TYPE_OBJECT = 41,
	KEYWORD_KEYS = 42,
	KEYWORD_ALIAS = 43,
	KEYWORD_REASSIGN = 44
};

enum Operator
{
	OPERATOR_EQUALS = 0,
	OPERATOR_NOT_EQUALS = 1,
	OPERATOR_LESS_THAN = 2,
	OPERATOR_GREATER_THAN = 3,
	OPERATOR_LESS_THAN_EQUALS = 4,
	OPERATOR_GREATER_THAN_EQUALS = 5
};

const std::map<std::wstring, ReservedWord> RESERVED_WORD_IDENTIFIER_MAP =
{
	{ L"int",    TYPE_INT },
	{ L"long",   TYPE_LONG },
	{ L"double", TYPE_DOUBLE },
	{ L"string", TYPE_STRING },
	{ L"object", TYPE_OBJECT }
};

const std::map<const std::wstring, const ReservedWord> RESERVED_WORD_MAP =
{
	{ L"int",        TYPE_INT },
	{ L"double",     TYPE_DOUBLE },
	{ L"string",     TYPE_STRING },
	{ L"function",   TYPE_FUNCTION },
	{ L"return",     KEYWORD_RETURN },
	{ L"call",       KEYWORD_CALL },
	{ L"end",        KEYWORD_END },
	{ L"if",         KEYWORD_IF },
	{ L"while",      KEYWORD_WHILE },
	{ L"sizeof",     KEYWORD_SIZEOF },
	{ L"include",    KEYWORD_INCLUDE },
	{ L"import",     KEYWORD_IMPORT },
	{ L"detach",     KEYWORD_DETACH },
	{ L"join",       KEYWORD_JOIN },
	{ L"println",    KEYWORD_PRINTLN },
	{ L"print",      KEYWORD_PRINT },
	{ L"read",       KEYWORD_READ },
	{ L"readln",     KEYWORD_READLN },
	{ L"lock",       KEYWORD_LOCK },
	{ L"unlock",     KEYWORD_UNLOCK },
	{ L"break",      KEYWORD_BREAK },
	{ L"try",        KEYWORD_TRY },
	{ L"catch",      KEYWORD_CATCH },
	{ L"delete",     KEYWORD_DELETE },
	{ L"mutex",      KEYWORD_MUTEX },
	{ L"else",       KEYWORD_ELSE },
	{ L"system",     KEYWORD_SYSTEM },
	{ L"long",       TYPE_LONG },
	{ L"exec",       KEYWORD_EXEC },
	{ L"exit",       KEYWORD_EXIT },
	{ L"instanceof", KEYWORD_INSTANCEOF },
	{ L"new",        KEYWORD_NEW },
	{ L"continue",   KEYWORD_CONTINUE },
	{ L"object",     TYPE_OBJECT },
	{ L"keys",       KEYWORD_KEYS },
	{ L"alias",      KEYWORD_ALIAS },
	{ L"reassign",   KEYWORD_REASSIGN }
};
const std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<const std::wstring, const ReservedWord>>>> RESERVED_WORD_MAP_END = RESERVED_WORD_MAP.end();

const std::map<const std::wstring, const Operator> OPERATOR_MAP =
{
	{ L"==", OPERATOR_EQUALS },
	{ L"!=", OPERATOR_NOT_EQUALS },
	{ L"<",  OPERATOR_LESS_THAN },
	{ L">",  OPERATOR_GREATER_THAN },
	{ L"<=", OPERATOR_LESS_THAN_EQUALS },
	{ L">=", OPERATOR_GREATER_THAN_EQUALS }
};
const std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<const std::wstring, const Operator>>>> OPERATOR_MAP_END = OPERATOR_MAP.end();

#endif

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

const std::map<std::string, ReservedWord> RESERVED_WORD_IDENTIFIER_MAP =
{
	{ "int",    TYPE_INT },
	{ "long",   TYPE_LONG },
	{ "double", TYPE_DOUBLE },
	{ "string", TYPE_STRING },
	{ "object", TYPE_OBJECT }
};

const std::map<const std::string, const ReservedWord> RESERVED_WORD_MAP =
{
	{ "int",        TYPE_INT },
	{ "double",     TYPE_DOUBLE },
	{ "string",     TYPE_STRING },
	{ "function",   TYPE_FUNCTION },
	{ "return",     KEYWORD_RETURN },
	{ "call",       KEYWORD_CALL },
	{ "end",        KEYWORD_END },
	{ "if",         KEYWORD_IF },
	{ "while",      KEYWORD_WHILE },
	{ "sizeof",     KEYWORD_SIZEOF },
	{ "include",    KEYWORD_INCLUDE },
	{ "import",     KEYWORD_IMPORT },
	{ "detach",     KEYWORD_DETACH },
	{ "join",       KEYWORD_JOIN },
	{ "println",    KEYWORD_PRINTLN },
	{ "print",      KEYWORD_PRINT },
	{ "read",       KEYWORD_READ },
	{ "readln",     KEYWORD_READLN },
	{ "lock",       KEYWORD_LOCK },
	{ "unlock",     KEYWORD_UNLOCK },
	{ "break",      KEYWORD_BREAK },
	{ "try",        KEYWORD_TRY },
	{ "catch",      KEYWORD_CATCH },
	{ "delete",     KEYWORD_DELETE },
	{ "mutex",      KEYWORD_MUTEX },
	{ "else",       KEYWORD_ELSE },
	{ "system",     KEYWORD_SYSTEM },
	{ "long",       TYPE_LONG },
	{ "exec",       KEYWORD_EXEC },
	{ "exit",       KEYWORD_EXIT },
	{ "instanceof", KEYWORD_INSTANCEOF },
	{ "new",        KEYWORD_NEW },
	{ "continue",   KEYWORD_CONTINUE },
	{ "object",     TYPE_OBJECT },
	{ "keys",       KEYWORD_KEYS },
	{ "alias",      KEYWORD_ALIAS },
	{ "reassign",   KEYWORD_REASSIGN }
};
const std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<const std::string, const ReservedWord>>>> RESERVED_WORD_MAP_END = RESERVED_WORD_MAP.end();

const std::map<const std::string, const Operator> OPERATOR_MAP =
{
	{ "==", OPERATOR_EQUALS },
	{ "!=", OPERATOR_NOT_EQUALS },
	{ "<",  OPERATOR_LESS_THAN },
	{ ">",  OPERATOR_GREATER_THAN },
	{ "<=", OPERATOR_LESS_THAN_EQUALS },
	{ ">=", OPERATOR_GREATER_THAN_EQUALS }
};
const std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<const std::string, const Operator>>>> OPERATOR_MAP_END = OPERATOR_MAP.end();

#endif
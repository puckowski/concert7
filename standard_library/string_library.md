[Home](https://github.com/puckowski/concert7/blob/master) <span>&emsp;</span> [Standard library](https://github.com/puckowski/concert7/blob/master/standard_library/standard_library.md)

# String library

Provides standard string functions.

## Import

The following statement may be used to import the string library:

```cpp
import string;
```

## Functions

| Name              | Description                                            |
|:------------------|:-------------------------------------------------------|
| substring         | Return a substring                                     |
| find              | Find the index of a substring                          |
| contains          | Check the existence of a substring                     |
| length            | Return the length                                      |
| to_int            | Convert to an integer type                             |
| to_double         | Convert to a double type                               | 
| char_at           | Return the character at an index                       |
| char_to_string    | Convert a character, stored in an integer, to a string |
| wchar_to_string   | Convert a wchar, stored in an integer, to a string     |
| int_to_string     | Convert an integer to a string                         |
| double_to_string  | Convert a double to a string                           |
| char_to_int       | Convert a character to an integer                      |
| to_lower_case     | Convert a string to lower case                         |
| to_upper_case     | Convert a string to upper case                         |

## Examples

### substring

```cpp
string SUBSTRING_TEST_STRING = "This is a test string.";
string testSubstring;
call substring : SUBSTRING_TEST_STRING, 0, 4 -> testSubstring;
```

### find

```cpp
string FIND_TEST_STRING = "This is a test string.";
int findResult = -1;
call find : FIND_TEST_STRING, "a" -> findResult;
```

### contains

```cpp
string CONTAINS_TEST_STRING = "This is a test string.";
int containsResult;
call contains : CONTAINS_TEST_STRING, "This" -> containsResult;
```

### length

```cpp
string LENGTH_TEST_STRING = "This is a test string.";
int testStringLength = -1;
call length : LENGTH_TEST_STRING -> testStringLength;
```

### to_int

```cpp
string firstChar = "?";
int charInt = -1;
call char_to_int : firstChar -> charInt;
```

### to_double

```cpp
string sToD = "2.718";
tempDouble = -1.0;
call to_double : sToD -> tempDouble;
```

### char_at

```cpp
string CHAR_AT_TEST_STRING = "This is a test string.";
string firstChar = "?";
call char_at : CHAR_AT_TEST_STRING, 0 -> firstChar;
```

### char_to_string

```cpp
int byte;
string char;
call char_to_string : byte -> char;
```

### wchar_to_string

```cpp
int wchar;
string char;
call wchar_to_string : wchar -> char;
```

### int_to_string

```cpp
int iToS = 234;
string tempString = "?";
call int_to_string : iToS -> tempString;
```

### double_to_string

```cpp
double dToS = 3.14;
tempString = "?";
call double_to_string : dToS -> tempString;
```

### char_to_int

```cpp
string firstChar = "?";
int charInt = -1;
call char_to_int : firstChar -> charInt;
```

### to_lower_case

```cpp
string toLower = "ABCdefGHI";
call to_lower_case : toLower -> toLower;
```

### to_upper_case

```cpp
string toUpper = "abcDEFghi";
call to_upper_case : toUpper -> toUpper;
```
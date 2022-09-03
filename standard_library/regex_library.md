[Home](https://github.com/puckowski/concert7) <span>&emsp;</span> [Standard library](https://puckowski.github.io/concert7/standard_library/standard_library.html)

# Regex library

Provides standard regular expression functions.

## Import

The following statement may be used to import the math library:

```cpp
import regex;
```

## Functions

| Name           | Description                                        |
|:---------------|:---------------------------------------------------|
| regex_search   | Search for all matches of a regular expression in a string. |
| regex_match    | Check if string matches regular expression.                              |
| regex_replace  | Replace all occurrences of regular expression in string.                    |

## Examples

### regex_search

```cpp
string data = "(Speed:366 Mass:35 Speed:378 Mass:32";
string regex = "(Speed:\d*)";

call regex_search : "result", data, regex;

println result.length;
println result.data[0], result.data[1], " done.";

int x = 0;

while x < result.length[0];
	println result.data[x];
	x += 1;
end;
```

### regex_match

```cpp
int match;
string data2 = "subject";
string regex2 = "(sub)(.*)";

call regex_match : data2, regex2 -> match;
```

### regex_replace

```cpp
string r1 = "there is a subsequence in the string\n";
string r2 = "\b(sub)([^ ]*)";
string r3;
string r4 = "sub-$2";

call regex_replace : r1, r2, r4 -> r3;

println r3;
```

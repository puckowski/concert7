[Home](https://github.com/puckowski/concert7/blob/master/) <span>&emsp;</span> [Standard library](https://github.com/puckowski/concert7/blob/master/standard_library/standard_library.md)

# Date library

Provides date and time utility functions.

## Import

The following statement may be used to import the date library:

```cpp
import date;
```

## Functions

| Name                 | Description                                                                    |
|:---------------------|:-------------------------------------------------------------------------------|
| localtime            | Get the system localtime according to provided format string.                  |
| localtime_ns         | Get the system localtime with nanoseconds according to provided format string. |

## Examples

### localtime

```cpp
string timeFormatted = "";
call localtime : "%Y-%m-%d %H:%M:%S" -> timeFormatted;

println timeFormatted;
```

### localtime_ns

```cpp
string timeFormatted = "";
call localtime_ns : "%Y-%m-%d %H:%M:%S" -> timeFormatted;

println timeFormatted;
```

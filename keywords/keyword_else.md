[Home](https://github.com/puckowski/concert7) <span>&emsp;</span> [Keywords](https://github.com/puckowski/concert7/keywords.html)

# Keyword else

## Description

Declares the alternative branch to an if statement. This branch is executed if its corresponding if statement fails.

## Example

```cpp
double E_TRUNCATED = 2.71;
double PI_TRUNCATED = 3.14;

if E_TRUNCATED > PI_TRUNCATED;
    println "This print will never execute.";
else;
    println "Statements in this block will be executed as the above if statement fails.";
end;
```

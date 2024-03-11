[Home](https://github.com/puckowski/concert7/blob/master/) <span>&emsp;</span> [Keywords](https://github.com/puckowski/concert7/blob/master/keywords.md)

# Keyword delete

## Description

Delete a declared variable from current scope and free allocated memory.

## Example

```cpp
int globalScopeVar = 0;

delete "globalScopeVar";
# int globalScopeVar no longer exists and no longer uses memory
```

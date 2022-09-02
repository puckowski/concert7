[Home](https://github.com/puckowski/concert7) <span>&emsp;</span> [Keywords](https://github.com/puckowski/concert7/keywords.html)

# Keyword instanceof

## Description

Returns the type of a variable.

## Example

```cpp
mutex lock;
string varType;

# varType will be set to "mutex"
instanceof lock varType;

# varType will be set to "int"
int testInt = 5;
instanceof testInt varType;
```

## Result table

| Variable type   | instanceof result                                                |
|:----------|:------------------------------------------------------------|
|int          |int                                                  |
|long         |long                                                 |
|string       |string                                               |
|double       |double                                               |

[Home](https://github.com/puckowski/concert7/blob/master/)

# Types

## Primitive types

- int
- long
- double
- string
- mutex

## Null values

There are no null values in Concert. The following table defines default values.

|Type   |Default value    |
|:------|:----------------|
|int    |undefined 32-bit |
|long   |undefined 64-bit |
|double |undefined 64-bit |
|string |Empty string ""  |
|mutex  |Not applicable   |

## Properties

|Type   |Width in bits |
|:------|:-------------|
|int    |at least 32   |
|long   |at least 64   |
|double |at least 64   |

## Implicit casts

The following may be implicitly cast without a library call. Note that overflows may occur.

|From type|To type|
|:--------|:------|
|int      |long   |
|long     |int    |

## Declaration

int declaration examples:

```cpp
int x;
int y = 0;
int z = 5 + y;
```

long declaration examples:

```cpp
long l;
long m = 0;
long n = 5 + m;
```

double declaration examples:

```cpp
double d;
double pi = 3.14;
double tenth = 1.0 / 10.0;
```

string declaration examples:

```cpp
string s;
string partialWelcome = "Hello";
string fullWelcome = partialWelcome + ", world!";
```

mutex declaration examples:

```cpp
mutex m;
mutex lock;
```

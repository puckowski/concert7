[Home](https://puckowski.github.io/concert/)

# Arrays

Arrays are declared similarly to variables. Arrays of all primitive types, except for mutex, may be created. Arrays may be const.

## Mutex arrays

Arrays of all primitive types except for mutexes are allowed.

## Multidimensional arrays

Currently Concert does not allow for creation multidimensional arrays.

## Declaration

### int array declaration examples

```cpp
# Declare array "xArr", size 5
int xArr 5;

# Declare array "xArr", size 5, and initialize all values to 0
int xArr 5 = 0;

int size = 10;
int secondArr size;
```

### long array declaration examples

```cpp
# Declare array "lArr", size 5
long lArr 5;

# Declare array "lArr", size 5, and initialize all values to 0
long lArr 5 = 0;

int size = 10;
long secondArr size;
```

### double array declaration examples

```cpp
# Declare array "dArr", size 5
double dArr 5;

# Declare array "dArr", size 5, and initialize all values to 0.0
double dArr 5 = 0.0;

int size = 10;
double secondArr size;
```

### string array declaration examples

```cpp
# Declare array "sArr", size 5
string sArr 5;

# Declare array "sArr", size 5, and initialize all values to ""
string sArr 5 = "";

int size = 10;
string secondArr size;
```

## Assignment

### int array assignment examples

```cpp
# Declare array "xArr", size 5
int xArr 5;

int size = 10;
int secondArr size;

xArr[1] = 10;
secondArr[0] = 1;

int i = xArr[1];
int n = xArr[secondArr[0]];
```

### double array assignment examples

```cpp
# Declare array "dArr", size 5
double dArr 5;

int size = 10;
double secondArr size;

dArr[1] = 10.0;
secondArr[0] = 1.0;

double d = dArr[1];
double b = dArr[secondArr[0]];
```

### string array assignment examples

```cpp
# Declare array "sArr", size 5
string sArr 5;

int size = 10;
string secondArr size;

sArr[1] = "10";
secondArr[0] = "1";

string s = sArr[1];
string t = sArr[secondArr[0]];
```

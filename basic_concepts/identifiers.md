[Home](https://puckowski.github.io/concert/)

# Identifiers

Identifiers are any sequence of uninterrupted characters separated by space characters. An identifier should not be a keyword.

## const identifiers

Concert stores const identifiers in a location separate from all other identifiers. By default, Concert does not verify that an identifier is unique upon declaration. Therefore, it is possible to have duplicate identifiers in the same scope. For example, the same identifier could reference a value and reference a const value.

## Identifier examples

```cpp
int x;
int range2;

long l;
long largeInteger;

double _distance;
double totalArea;

string myName;
string welcome_message;
```

## const identifier examples

```cpp
const int DEFAULT_ITERATIONS = 10;
const long ITERATIONS_MAX = 5000000000;
const double PI = 3.14;
const string DEFAULT_WELCOME = "Hello, world!";
```

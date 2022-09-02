[Home](https://github.com/puckowski/concert7) <span>&emsp;</span> [Keywords](https://github.com/puckowski/concert7/keywords.html)

# Keyword function

## Description

Declare a function.

## Example

```cpp
function helloWorldWithName : using NAME;
    println "Hello, ", NAME, "!";
return;

string NAME = "John Doe";

call helloWorldWithName : NAME;
```

## Arguments with using

Any variable may be specified using the ```using``` keyword.

```cpp
function printCoordinates : using coordObj;
    print coordObj.x, ", ", coordObj.y;
return;
```

## Arguments with as

Only ```int```, ```double```, ```string```, and ```long``` variables may be specified with the ```as``` keyword.

```cpp
function printMessage : message as string;
    println message;
return;
```

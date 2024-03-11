[Home](https://github.com/puckowski/concert7/blob/master/) <span>&emsp;</span> [Keywords](https://github.com/puckowski/concert7/blob/master/keywords.md)

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

Only ```object```, ```int```, ```double```, ```string```, and ```long``` variables may be specified with the ```as``` keyword.

```cpp
function printMessage : string as message;
    println message;
return;
```

## Arguments with as by reference

Adding a ```&``` character before the variable name in the ```as``` clause will copy the variable by reference into scope. Modifying the ```as``` variable modifies the original argument variable as well.

```cpp
function printMessage : string as &message;
    println message;
    message = "The argument variable will now contain this text.";
return;
```

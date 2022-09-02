[Home](https://github.com/puckowski/concert7) <span>&emsp;</span> [Keywords](https://github.com/puckowski/concert7/keywords.html)

# Keyword call

## Description

Used to execute a declared function, providing appropriate parameters when necessary.

## Example

```cpp
function fancyPrint : with string as toPrint;
    println "---------------------------------"
    println "> ", toPrint;
return;

string message = "Hello. How are you?";

call fancyPrint : message;
```

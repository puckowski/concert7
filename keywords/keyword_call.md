[Home](https://puckowski.github.io/concert/) <span>&emsp;</span> [Keywords](https://puckowski.github.io/concert/keywords.html)

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

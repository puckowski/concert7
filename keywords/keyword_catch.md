[Home](https://puckowski.github.io/concert/) <span>&emsp;</span> [Keywords](https://puckowski.github.io/concert/keywords.html)

# Keyword catch

## Description

Declares the block of code to execute should an exception be thrown from a try-block statement.

## Example

```cpp
# Declare a 5 integer array with default values of 0.
int valArray 5 = 0;

try;
    # An out of bounds exception will occur.
    int sixthValue = valArray[5];
catch;
    println "This print statement will be executed as the try-block statement above will throw an error.";
end;
```

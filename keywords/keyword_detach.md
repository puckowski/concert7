[Home](https://puckowski.github.io/concert/) <span>&emsp;</span> [Keywords](https://puckowski.github.io/concert/keywords.html)

# Keyword detach

## Description

Separates the thread of execution from the current thread, allowing execution to continue independently. A declared function must be provided as a parameter.

## Example

```cpp
function calculateSumAndPrint : using valArray, int as startIndex, int as finalIndex;
    int sum = 0;
  
    while startIndex < finalIndex;
        sum += valArray[startIndex];  
        startIndex += 1;
    end;
  
    println "Sum for range [", startIndex, ",", finalIndex, "] is: ", sum;
return;

# Declare array of 10 integers with default value of 5.
int valArray 10 = 5;

int start = 0;
int end = 5;

while end <= 10;
    detach "calculateSumAndPrint" : valArray, start, end;
  
    start += 5;
    end += 5;
end;
```

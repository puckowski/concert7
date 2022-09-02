[Home](https://github.com/puckowski/concert7) <span>&emsp;</span> [Keywords](https://github.com/puckowski/concert7/keywords.html)

# Keyword join

## Description

Blocks the current thread until the thread created by join finishes its execution. Requires a declared function as a parameter.

## Example

```cpp
function simpleLoopFunction;
    int start = 0;
    int end = 100;
  
    while start < end;
      start += 1;
    end;
return;

function detachLoopFunctions;
    detach simpleLoopFunction;
    detach simpleLoopFunction;
return;

# Wait for the threads detached in "detachLoopFunctions" to finish their execution.
join detachLoopFunctions;
```

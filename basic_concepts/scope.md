[Home](https://puckowski.github.io/concert/)

# Scope

Each function receives a unique scope. 

## Global scope

Declarations outside of any function exist in the global scope. 

## Structs

All structs, regardless of where they are created, exist in the global scope.

## Example

```cpp
# The int "globalInt" exists in the global scope
int globalInt = 100;

function printSum : int as left, int as right;
    # The int "sum" exists within the scope of function "printSum"
    int sum = left + right;
  
    println sum;
return;
```

[Home](https://github.com/puckowski/concert7/blob/master/)

# Scope

Each function receives a unique scope. 

## Global scope

- Declarations outside of any function exist in the global scope. 
- All mutex objects are in global scope.

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

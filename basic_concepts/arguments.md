[Home](https://github.com/puckowski/concert7)

# Arguments

Arguments, if specified, exist in the global scope of the main thread. Arguments are stored in a string array called "argv". The number of arguments specified exists in an integer variable called "argc".

## Specifying program arguments

Note: A debugging state, 0 for false and 1 for true, must be specified if using program arguments.

Example with two arguments and debugging disabled:

Concert.exe filename 0 first_argument second_argument

## Accessing program arguments

```cpp
println "First program argument: ", argv[0];
println "Number of program arguments: ", argc;
```
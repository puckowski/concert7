[Home](https://github.com/puckowski/concert7/blob/master/)

# Functions

## Return value

Note: there must be only one return statement per function. The return statement must be at the end of the function.

## Generics

Note: if the provided parameter definition is not a valid datatype, it is assumed to be a generic. Generic names can be any valid identifier.

## Mutex parameters

Note: a parameter can be any datatype except for a mutex.

## Examples

Example "hello" function declaration:

```cpp
function hello;
```

Example "hello" function:

```cp
function hello;
    print "Hello";
return;
```

Example "simpleRet" function declaration:

```cpp
function simpleRet;
```

Example "simpleRet" function. Function returns the value 5.

```cpp
function simpleRet;
return 5;
```

Example "formattedPrint" function declaration. Function accepts a string type parameter. The string parameter is pass by value. The string parameter is assigned the identifer "msg" for the scope of the function.

```cpp
function formattedPrint : string as msg;
```

Example "formattedPrint" function:

```cpp
function formattedPrint : string as msg;
    println "Hello, " msg;
return;
```

Example "incrementVar" function declaration. Function accepts an int type parameter. The int parameter is pass by reference. The int parameter is assigned the identifier "toInc" for the scope of the function. 

```cpp
function incrementVar : using toInc;
```

Example "incrementVar" function:

```cpp
function incrementVar : using toInc;
    toInc += 1;
return;
```

Example "sum" function declaration. Function accepts two int type parameters. The first int parameter is passed by reference. The second int parameter is passed by value and assigned the identifier "toAdd" for the scope of the function.

```cpp
function sum : using count, int as toAdd;
```

Example "sum" function. The function returns the value count.

```cpp
function sum : using count, int as toAdd;
    count += toAdd;
return count;
```

## Example generic functions

Example generic "sumArray" function. The function returns array sum, whether it be an array of integers, longs, doubles, or strings.

```cpp
function sumArray : array as toSum, int as length, value as toInc;	
	string type;
	instanceof toSum type;
		
	if type == "int";
		int i = 0;
		while i < length;
			toInc += toSum[i];
			i += 1;
		end;
	end;
	
	if type == "long";
		int i = 0;
		while i < length;
			toInc += toSum[i];
			i += 1;
		end;
	end;
	
	if type == "double";
		int i = 0;
		while i < length;
			toInc += toSum[i];
			i += 1;
		end;
	end;
	
	if type == "string";
		int i = 0;
		while i < length;
			toInc += toSum[i];
			i += 1;
		end;
	end;
return toInc;
```

As the above function does the same operation for each datatype, the function can be simplified to the following.

```cpp
function sumArray : genericArray as toSum, int as length, genericValue as toInc;	
	int i = 0;
	while i < length;
		toInc += toSum[i];
		i += 1;
	end;
return toInc;
```
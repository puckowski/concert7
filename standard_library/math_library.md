[Home](https://github.com/puckowski/concert7/blob/master/) <span>&emsp;</span> [Standard library](https://github.com/puckowski/concert7/blob/master/standard_library/standard_library.md)

# Math library

Provides standard math functions.

## Import

The following statement may be used to import the math library:

```cpp
import math;
```

## Functions

| Name           | Description                                                          |
|:---------------|:---------------------------------------------------------------------|
| seed_random    | Seed the random number generator using system time                   |
| get_random     | Get a random integer                                                 |
| int_to_double  | Convert an integer to a double                                       |
| double_to_int  | Convert a double to an integer                                       |
| int_to_long    | Convert an integer to a long                                         |
| long_to_int    | Convert a long to an integer                                         |
| long_to_double | Convert a long to a double                                           |
| double_to_long | Convert a double to a long                                           |
| absolute_value | Convert an integer, long, or double to its absolute value            |
| sqrt           | Get the square root of an integer, long, or double                   |
| log10          | Get the common logarithm an integer, long, or double                 |
| ceil           | Get the least value not less than an integer, long, or double        |
| round          | Get the nearest integer, long, or double                             |
| floor          | Get theleast of an integer, long, or double                          |
| sin            | Compute the sine of an integer, long, or double                      |
| cos            | Compute the cosine of an integer, long, or double                    |
| tan            | Compute the tangent of an integer, long, or double                   |
| get_pi         | Returns pi approximation 3.141592653589793                           |
| set_precision  | Set the fixed standard output precision                              |
| exp            | Computes Euler's number raised to the given integer, long, or double |

## Examples

### seed_random

```cpp
call seed_random;
```

### get_random

```cpp
int rand;
call get_random -> rand;
```

### int_to_double

```cpp
int iToD = 5;
double tempDouble;

call int_to_double : iToD -> tempDouble;
```

### double_to_int

```cpp
int dToI = -1;
double tempDouble;

call double_to_int : tempDouble -> dToI;
```

### int_to_long

```cpp
int toLong = 12345;
long l;

call int_to_long : toLong -> l;
```

### long_to_int

```cpp
long toInt = 349674032692;
int i;

call long_to_int : toInt -> i;
```

### long_to_double

```cpp
long toDouble = 122334;
double d;

call long_to_double : toDouble -> d;
```

### double_to_long

```cpp
double toLong = 3.14;
long l;

call double_to_long : toLong -> l;
```

### absolute_value

```cpp
double toLong = -3.14;
long l;

call absolute_value : toLong -> l;
```

### sqrt

```cpp
double value = 4;
double l;

call sqrt : value -> l;
```

### log10

```cpp
double value = 100;
double l;

call log10 : value -> l;
```

### ceil

```cpp
double value = 100.5;
double l;

call ceil : value -> l;
```

### round

```cpp
double value = 100.5;
double l;

call round : value -> l;
```

### floor

```cpp
double value = 100.5;
double l;

call floor : value -> l;
```

### sin

```cpp
double value = 100;
double l;

call sin : value -> l;
```

### cos

```cpp
double value = 100;
double l;

call cos : value -> l;
```

### tan

```cpp
double value = 100;
double l;

call tan : value -> l;
```

### get_pi 

```cpp
double pi_val = 0;
call get_pi -> pi_val;
```

### set_precision

```cpp
int precision = 17;
call set_precision : precision;
```

### exp

```cpp
double val = 1.6;
call exp : val -> val;
```

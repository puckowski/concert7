[Home](https://github.com/puckowski/concert7)

# Operator precedence
  
| Precedence | Operator | Description                 |
|:-----------|:---------|:----------------------------|
|1           |.         |Scope                        |
|1           |[]        |Subscript                    |
|2           |<<        |Bitwise left shift           |
|2           |>>        |Bitwise right shift          |
|3           |*         |Multiplication               |
|3           |/         |Division                     |
|3           |%         |Remainder                    |
|4           |+         |Addition                     |
|4           |-         |Subtraction                  |
|5           |\|        |Bitwise OR                   |
|5           |&         |Bitwise AND                  |
|5           |^         |Bitwise XOR                  |
|5           |~         |Binary ones complement       |
|5           |>>>       |Unsigned right shift         |

## Scope example

```cpp
object animal 5;

int animal.x 1;
animal.x = 100;
```

## Subscript example

```cpp
int array 10 = 0;
int currentIndex = 0;
int currentValue = 5;

# Value of array at index 0 will equal 5 after assignment.
array[0] = array[currentIndex] + currentValue;
```

## Bitwise left shift example

```cpp
int MULTIPLIER = 200 << 24;
int shiftResult = (16 * 8) << 4;
```

## Bitwise right shift example

```cpp
int RIGHT_MULTIPLIER = -200 >> 24;
int secondShift = (32 / 2) >> 16;
```

## Multiplication example

```cpp
int area = 5 * 5;
```

## Division example

```cpp
int perimeter = 250 / 25;
```

## Remainder example

```cpp
int remainder = 1050 % 6;
```

## Addition example

```cpp
int sum = 5 + 25 + 125;
```

## Subtraction example

```cpp
int difference = 1000 - 100 - 10;
```

## Bitwise OR example

```cpp
# orResult equals 248 after assignment.
int orResult = 72 | 184;
```

## Bitwise AND example

```cpp
# andResult equals 8 after assignment.
int andResult = 72 & 184;
```

## Bitwise XOR example

```cpp
# xorResult equals 159 after assignment.
int xorResult = 31 ^ 128;
```

## Binary ones complement example

```cpp
# onesComplementResult equals -51 after assignment.
int onesComplementResult = 0 ~ 50;
```

## Unsigned right shift example

```cpp
# unsignedRightShiftResult equals 30 after assignment.
int unsignedRightShiftResult = 123 >>> 2;
```

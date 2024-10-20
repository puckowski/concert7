[Home](https://github.com/puckowski/concert7/blob/master/)

# Objects

## Default value

The default value of a Concert object is an empty dictionary {}.

|Type   |Default value    |
|:------|:----------------|
|object |{}               |

## Storable properties

The following property types may be stored in an object:

- int
- long
- double
- string

## Declaration

object declaration examples:

```cpp
object cat;
object dog;
object car;
object car.engine;
object farm;

int cat.age = 10;
double dog.weight = 55.54;
string car.brand = "Mazda";
int car.engine.horsepower = 200;
string farm.animals 10;
farm.animals[0] = "Cow";

# Declare an array of objects of size 10
object foo 10;

string barName = "bar";
object foo.'barName';

int foo.'barName'.baz;
foo.'barName'.baz = 123;

string bazName = "baz";
println foo.'barName'.'bazName';
```

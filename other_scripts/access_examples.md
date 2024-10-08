[Home](https://github.com/puckowski/concert7/blob/master/)

# Variable Access Examples

Below are various examples of variable access using the dot ```.``` syntax.

## Code

```cpp
int x;
x = 5;
println x;

int x 5;
x[1] = 6;
println x[1];

object foo;
int foo.bar;
foo.bar = 7;
println foo.bar;

object foo.baz;
int foo.baz.qux;
foo.baz.qux = 8;
println foo.baz.qux;

object corge 5;
int corge[2].x;
corge[2].x = 9;
println corge[2].x;
#println corge[0].x;

object corge[2].bat;
int corge[2].bat.y;
corge[2].bat.y = 10;
println corge[2].bat.y;
corge[2].bat.y += 1;
println corge[2].bat.y[0];

int size = 0;
keys foo "fooKeys";
sizeof fooKeys size;
int i = 0;
while i < size;
	println fooKeys[i];
	i += 1;
end;

int ySize = 10;
int y ySize = 0;
y[1] = 12;
int first 1 = 1;
println y[first[0]];

object animal;
object animal.health;
int animal.health.age;
animal.health.age = 13;
println animal[0].health[0].age;

object dog 5;
string dogName = "dogName";
object dog.'dogName';
int dog.'dogName'.length;
dog.'dogName'.length = 14;
string dogNameLength = "length";
println dog.'dogName'.'dogNameLength';

object cat 5;
string catName = "catName";
object cat.'catName';
int cat.'catName'.length 5;
cat.'catName'.length[2] = 15;
string catNameLength = "length";
println cat.'catName'.'catNameLength'[0];
println cat.'catName'.'catNameLength'[1];
println cat.'catName'.'catNameLength'[2];
println cat.'catName'.'catNameLength'[3];
println cat.'catName'.'catNameLength'[4];

object cow 5;
object cow.legs 4;
int cow.legs[1].first;
cow.legs[1].first[0] = 16;
println cow.legs[1].first[0];

object multiDim 5;
string secondDimName = "dim";
int dimSize;
sizeof multiDim dimSize;
int n = 0;
while n < dimSize;
	object multiDim.'secondDimName';
	int multiDim.'secondDimName'.x 5;
	int t = 0;
	while t < 5;
		multiDim.'secondDimName'.x[t] = t;
		t += 1;
	end;
	n += 1;
end;
n = 0;
while n < dimSize;
	int t = 0;
	while t < 5;
		println multiDim.'secondDimName'.x[t];
		t += 1;
	end;
	n += 1;
end;
```

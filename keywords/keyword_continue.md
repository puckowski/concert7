[Home](https://github.com/puckowski/concert7/blob/master/) <span>&emsp;</span> [Keywords](https://github.com/puckowski/concert7/blob/master/keywords.md)

# Keyword continue

## Description

Jump to start of enclosing loop.

## Example

```cpp
call seed_random;

while 1 == 1;
    int rand;
	call get_random -> rand;
	rand = rand % 100;
	
	if rand < 50;
		# Jump to while 1 == 1;
		continue;
	else;
		break;
	end;
end;
```

[Home](https://github.com/puckowski/concert7/blob/master/) <span>&emsp;</span> [Keywords](https://github.com/puckowski/concert7/blob/master/keywords.md)

# Keyword exit

## Description

Exit the current script. Has effect of terminating program if run in main script.

As of Concert 8.0, there is an implicit ```exit``` call added to each script, so specifying ```exit``` at the end of a script is not required.

## Example

```cpp
import string;
import math;
import io;

int count = 0;
mutex m;

function joinedCount : using count;
	while count < 1000000;
		lock m;
		
		if count < 1000000;
			count += 1;
		end;
		
		unlock m;
	end;
return;

join joinedCount;

# Return to main script
exit; 
```

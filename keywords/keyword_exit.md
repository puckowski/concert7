[Home](https://github.com/puckowski/concert7) <span>&emsp;</span> [Keywords](https://github.com/puckowski/concert7/keywords.html)

# Keyword exit

## Description

Exit the current script. Has effect of terminating program if run in main script.

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

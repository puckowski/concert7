[Home](https://github.com/puckowski/concert7/blob/master/)

# CRC-16 implementation

Cyclic redundancy check (CRC-16).

## Code

```cpp
import string;

function crc16 : string as message, int as length;
	int crc = 65535;
	int j = 0;
	string char;
	int charValue;
	
	while j < length;
		crc = ((crc >>> 8) | (crc << 8)) & 65535;
		
		call char_at : message, j -> char;
		call char_to_int : char -> charValue;
		
		int tmp = charValue & 255;
		crc ^= tmp;
		
		tmp = ((crc & 255) >> 4);
		crc ^= tmp;
		
		tmp = (crc << 12) & 65535;
		crc ^= tmp;
		
		tmp = ((crc & 255) << 5) & 65535;
		crc ^= tmp;
	
		j += 1;
	end;
	
	crc = crc & 65535;
	
return crc;

string message = "hello, world!";
int messageLength;
call length : message -> messageLength;

int checksum;

call crc16 : message, messageLength -> checksum;

println checksum;
```

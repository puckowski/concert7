import string;

string WELCOME = "Hello, world!";

# Adler-32 is a checksum algorithm invented by Mark Adler in 1995.
function adler32 : string as message, int as messageLength;
    int DIVISOR = 65521;

    string char;
    int charValue;
  
    int s1 = 1;
    int s2 = 0;
    int n = 0;
  
    while n < messageLength;
        call wchar_at : message, n -> char;
        call wchar_to_int : char -> charValue;
    
        s1 = (s1 + charValue) % DIVISOR;
        s2 = (s2 + s1) % DIVISOR;
    
        n += 1;
    end;
  
    s2 = (s2 << 16) | s1;
return s2;

int iteration = 0;

while iteration < 10000;
	int welcomeLength;
	call length : WELCOME -> welcomeLength;

	int hash;

	call adler32 : WELCOME, welcomeLength -> hash;

	iteration += 1;
end;

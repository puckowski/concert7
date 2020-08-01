[Home](https://puckowski.github.io/concert/)

# Performance: Concert vs. C++

## Test

Average Adler-32 hash time, averaged over 10,000,000 hashes. Ten test runs were completed.

## Results

![Concert vs. C++ Graph](https://raw.githubusercontent.com/puckowski/concert/master/Performance%20Concert%20vs%20C%2B%2B.png)

## C++ implementation

```cpp
const std::string WELCOME = "Hello, world!";

// Adler-32 is a checksum algorithm invented by Mark Adler in 1995.
uint32_t adler32(const void* buf, size_t bufLength) {
     const uint8_t* buffer = (const uint8_t*) buf;

     uint32_t s1 = 1;
     uint32_t s2 = 0;

     for (size_t n = 0; n < bufLength; n++) {
        s1 = (s1 + buffer[n]) % 65521;
        s2 = (s2 + s1) % 65521;
     }  
     
     return (s2 << 16) | s1;
}

void main() {
    int hashAddress = adler32(WELCOME.c_str(), WELCOME.length());
}
```

## Concert implementation

```cpp
import string;

const string WELCOME = "Hello, world!";

# Adler-32 is a checksum algorithm invented by Mark Adler in 1995.
function adler32 : string as message, int as messageLength;
    const int DIVISOR = 65521;

    string char;
    int charValue;
  
    int s1 = 1;
    int s2 = 0;
    int n = 0;
  
    while n < messageLength;
        call char_at : message, n -> char;
        call to_int : char -> charValue;
    
        s1 = (s1 + charValue) % DIVISOR;
        s2 = (s2 + s1) % DIVISOR;
    
        n += 1;
    end;
  
    s2 = (s2 << 16) | s1;
return s2;

int welcomeLength;
call length : WELCOME -> welcomeLength;

int hash;

call adler32 : WELCOME, welcomeLength -> hash;
```

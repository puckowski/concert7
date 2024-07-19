[Home](https://github.com/puckowski/concert7/blob/master/)

# Performance: Concert vs. C++

## Test

Average Adler-32 hash time, averaged over 10,000,000 hashes. Ten test runs were completed.

## Results

|Language  |Time       |
|:---------|:----------|
|C++       |0.0001ms   |
|Concert   |1680ms     |

## C++ implementation

```cpp
#include <chrono>
#include <string>
#include <iostream>

const std::string WELCOME = "Hello, world!";

inline std::chrono::high_resolution_clock::time_point getTime()
{
    return std::chrono::high_resolution_clock::now();
}

inline void printTimeDifferenceMillis(const std::chrono::high_resolution_clock::time_point& t1, const std::chrono::high_resolution_clock::time_point& t2)
{
    std::cout << "Delta: " << std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()) << " ms" << std::endl;
}

inline void printTimeDifferenceAll(const std::chrono::high_resolution_clock::time_point& t1, const std::chrono::high_resolution_clock::time_point& t2)
{
    std::cout << "Delta: "
        << std::to_string(std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count()) << "s "
        << std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()) << "ms "
        << std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()) << "ns"
        << std::endl;
}

// Adler-32 is a checksum algorithm invented by Mark Adler in 1995.
uint32_t adler32(const void* buf, size_t bufLength) {
    const uint8_t* buffer = (const uint8_t*)buf;

    uint32_t s1 = 1;
    uint32_t s2 = 0;

    for (size_t n = 0; n < bufLength; n++) {
        s1 = (s1 + buffer[n]) % 65521;
        s2 = (s2 + s1) % 65521;
    }

    return (s2 << 16) | s1;
}

void main() {
    auto t1 = getTime();
    int iteration = 0;
    while (iteration < 10000) {
        int hashAddress = adler32(WELCOME.c_str(), WELCOME.length());
        iteration++;
    }
    auto t2 = getTime();
    printTimeDifferenceAll(t1, t2);
}
```

## Concert implementation

```cpp
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
```

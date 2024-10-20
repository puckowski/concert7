![Concert Header Image](https://raw.githubusercontent.com/puckowski/concert7/master/Concert_Header.png)

### [Jump to reference](#referenceStart)

```cpp
import string;

string WELCOME = "Hello, world!";

# Adler-32 is a checksum algorithm invented by Mark Adler in 1995.
function adler32 : string as message, int as messageLength;
    int MOD_ADLER = 65521;

    string char;
    int charValue;
  
    int s1 = 1;
    int s2 = 0;
    int n = 0;
  
    while n < messageLength;
        call wchar_at : message, n -> char;
        call wchar_to_int : char -> charValue;
    
        s1 = (s1 + charValue) % MOD_ADLER;
        s2 = (s2 + s1) % MOD_ADLER;
    
        n += 1;
    end;
  
    s2 = (s2 << 16) | s1;
return s2;

int welcomeLength;
call length : WELCOME -> welcomeLength;

int hash;

call adler32 : WELCOME, welcomeLength -> hash;
```

# <a id="referenceStart"></a>Reference

## Basic concepts

[Types](basic_concepts/types.md)

[Objects](basic_concepts/objects.md)

[Arrays](basic_concepts/arrays.md)

[Escape sequences](basic_concepts/escape_sequences.md)

[Comments](basic_concepts/comments.md)

[Identifiers](basic_concepts/identifiers.md)

[Scope](basic_concepts/scope.md)

[Arguments](basic_concepts/arguments.md)

## Keywords

[Keywords](keywords.md)

## Expressions

[Assignment](expressions/assignment.md)

[Operators](expressions/operators.md)

[Operator precedence](expressions/operator_precedence.md)

[Comparison](expressions/comparison.md)

## Functions

[Functions](functions.md)

## Standard library

[Standard library](standard_library/standard_library.md)

[String library](standard_library/string_library.md)

[Input output library](standard_library/io_library.md)

[Math library](standard_library/math_library.md)

[Regex library](standard_library/regex_library.md)

[Thread library](standard_library/thread_library.md)

[Date library](standard_library/date_library.md)

[Image library](standard_library/image_library.md)

## Examples

[Code examples](code_examples.md)

## Interpreter

[Usage](interpreter_usage.md)

## Performance

[Concert vs. C++](performance_cpp.md)

## Testing

[Test script](test_script.md)

## Other scripts

[Basic linter](other_scripts/basic_linter.md)
[CRC-16](other_scripts/crc16.md)
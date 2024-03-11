[Home](https://github.com/puckowski/concert7/blob/master/)

# Interpreter usage

### Default usage

Concert.exe filename

### With debugging enabled

Concert.exe filename 1

Note: debugging may reduce performance by as much as 300%.

Sample debugging output:

```
unknown exception occurred
current line: 85
current thread id: 10148
main thread id: 10148
call stack:
10148_convertIntToHex
10148_main
```

Note: debugging execution line excludes empty lines.

### With debugging disabled

Concert.exe filename 0

### With program arguments

Concert.exe filename 0 input.json 1024
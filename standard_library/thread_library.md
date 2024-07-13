[Home](https://github.com/puckowski/concert7/blob/master/) <span>&emsp;</span> [Standard library](https://github.com/puckowski/concert7/blob/master/standard_library/standard_library.md)

# Thread library

Provides standard regular expression functions. For Concert versions 8.0+.

## Import

The following statement may be used to import the thread library:

```cpp
import thread;
```

## Functions

| Name                 | Description                                            |
|:---------------------|:-------------------------------------------------------|
| get_thread_id        | Get the current thread's ID.                           |
| hardware_concurrency | Try to get system hardware thread count. May report 0. |
| sleep                | Sleep for argument milliseconds.                       |

## Examples

### get_thread_id

Returns a sttring representing the current thread's ID.

```cpp
string data;

call get_thread_id -> data;
```

### hardware_concurrency

```cpp
int threadCount = 0;
call hardware_concurrency -> threadCount;
```

### sleep

```cpp
int millis = 500;
println "Sleeping for ", millis, " millis";
call sleep : millis;
```

[Home](https://github.com/puckowski/concert7) <span>&emsp;</span> [Standard library](https://puckowski.github.io/concert7/standard_library/standard_library.html)

# Thread library

Provides standard regular expression functions. For Concert versions 8.0+.

## Import

The following statement may be used to import the thread library:

```cpp
import thread;
```

## Functions

| Name           | Description                                        |
|:---------------|:---------------------------------------------------|
| get_thread_id  | Get the current thread's ID. |

## Examples

### get_thread_id

Returns a sttring representing the current thread's ID.

```cpp
string data;

call get_thread_id -> data;
```

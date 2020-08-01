[Home](https://puckowski.github.io/concert/)

# Test script

```cpp
import string;
import math;
import io;

int count = 0;
mutex m;

function c2 : using count;
	while count < 1000000;
		lock m;
		
		if count < 1000000;
			count += 1;
		end;
		
		unlock m;
	end;
return;

function c3 : using count;
	import io;
	detach c2 : count;
	detach c2 : count;
	detach c2 : count;
	detach c2 : count;

	while count < 1000000;
	#	println "wait ", count;
	end;
return;

join c3 : count;

#detach c2 : count;

println "count: " count;

int musicManagerExist;
call is_file_exist : "musicmanagerinstaller.exe" -> musicManagerExist;
println "is_file_exist result: musicmanagerinstaller.exe query returned ", musicManagerExist, ".";

call create_file : "create_file_test.txt";
println "called create_file... created \"create_file_test.txt\".";

int createdFileExist;
call is_file_exist : "create_file_test.txt" -> createdFileExist;
println "is_file_exist result: create_file_test.txt query returned ", createdFileExist, ".";

int musicManagerSize;
call get_file_size : "musicmanagerinstaller.exe" -> musicManagerSize;
println "get_file_size result: musicmanagerinstaller.exe is ", musicManagerSize, " bytes large.";

call open_file : "create_file_test.txt";
println "called open_file on: \"create_file_test.txt\".";

call close_file : "create_file_test.txt";
println "called close_file on: \"create_file_test.txt\".";

call remove_file : "create_file_test.txt";
println "called remove_file on: \"create_file_test.txt\".";

# int createdFileExist;
call is_file_exist : "create_file_test.txt" -> createdFileExist;
println "is_file_exist result: create_file_test.txt query returned ", createdFileExist, ".";

call create_file : "create_file_test.txt";
println "called create_file... created \"create_file_test.txt\".";

call open_file : "create_file_test.txt";
println "called open_file on: \"create_file_test.txt\".";

int isFileOpen;
call is_open : "create_file_test.txt" -> isFileOpen;
println "called is_open on \"create_file_test.txt\".";
println "is_open result: ", isFileOpen, ".";

int isFileAtEnd;
call is_end : "create_file_test.txt" -> isFileAtEnd;
println "called is_end on \"create_file_test.txt\".";
println "is_end result: ", isFileAtEnd, ".";

call write_string : "create_file_test.txt", "Hello, world!";
println "called write_string on: \"create_file_test.txt\".";
println "wrote: \"Hello, world!\".";

call close_file : "create_file_test.txt";
println "called close_file on: \"create_file_test.txt\".";
 
call open_file : "create_file_test.txt";
println "called open_file on: \"create_file_test.txt\".";

string getLineResult;
call get_line : "create_file_test.txt" -> getLineResult;
println "get_line result: ", getLineResult;

call close_file : "create_file_test.txt";
println "called close_file on: \"create_file_test.txt\".";

call rename_file : "create_file_test.txt", "create_file_test_2.txt";
println "called rename_file on : \"create_file_test.txt\".";
println "renamed to: \"create_file_test_2.txt\".";

call remove_file : "create_file_test_2.txt";
println "called remove_file on: \"create_file_test_2.txt\".";

# int createdFileExist;
call is_file_exist : "create_file_test_2.txt" -> createdFileExist;
println "is_file_exist result: create_file_test_2.txt query returned ", createdFileExist, ".";

call create_file : "create_file_test.txt";
println "called create_file... created \"create_file_test.txt\".";

call open_file : "create_file_test.txt";
println "called open_file on: \"create_file_test.txt\".";

call write_string : "create_file_test.txt", "Hello, world!";
println "called write_string on: \"create_file_test.txt\".";
println "wrote: \"Hello, world!\".";

call close_file : "create_file_test.txt";
println "called close_file on: \"create_file_test.txt\".";

call open_file : "create_file_test.txt", 1;
println "called open_file on: \"create_file_test.txt\".";

isFileAtEnd = 0;
int filePointer = 0;
int byte;
string char;

while isFileAtEnd == 0;
	call is_end : "create_file_test.txt" -> isFileAtEnd;
	println "called is_end on \"create_file_test.txt\".";
	println "is_end result: ", isFileAtEnd, ".";

	call tell_file_pointer : "create_file_test.txt" -> filePointer;
	println "called tell_file_pointer on \"create_file_test.txt\".";
	println "tell_file_pointer result: ", filePointer, ".";

	#filePointer += 1;

	call seek_file_pointer : "create_file_test.txt", filePointer;
	println "called seek_file_pointer on \"create_file_test.txt\".";

	call read_byte : "create_file_test.txt" -> byte;
	println "called read_byte on \"create_file_test.txt\".";
	println "read_byte result: ", byte, ".";

	call char_to_string : byte -> char;
	println "called char_to_string on ", byte, ".";
	println "char_to_string result: ", char, ".";
end;

call close_file : "create_file_test.txt";
println "called close_file on: \"create_file_test.txt\".";

call open_file : "create_file_test.txt", 1;
println "called open_file on: \"create_file_test.txt\".";

call seek_file_pointer : "create_file_test.txt", 0;
call write_byte : "create_file_test.txt", 63;

call seek_file_pointer : "create_file_test.txt", 1;
call write_byte : "create_file_test.txt", 63;

call close_file : "create_file_test.txt";
println "called close_file on: \"create_file_test.txt\".";

call remove_file : "create_file_test.txt";
println "called remove_file on: \"create_file_test.txt\".";

call seed_random;
println "called seed_random.";

int rand;
int currentRand = 0;
const int numberOfRandInterations = 20;

while currentRand < numberOfRandInterations;
	call get_random -> rand;
	println "called get_random.";
	println "get_random result: ", rand, ".";

	currentRand += 1;
end;

int iToD = 5;
double tempDouble;

call int_to_double : iToD -> tempDouble;
println "called int_to_double.";
println "int_to_double result: ", tempDouble, ".";

int dToI = -1;
call double_to_int : tempDouble -> dToI;
println "called double_to_int.";
println "double_to_int result: ", dToI, ".";

int iToL = 1000;
long tempLong;
call int_to_long : iToL -> tempLong;
println "called int_to_long.";
println "int_to_long result: ", tempLong, ".";

const string CONTAINS_TEST_STRING = "This is a test string.";

int containsResult;
call contains : CONTAINS_TEST_STRING, "This" -> containsResult;
println "called contains on \"", CONTAINS_TEST_STRING, "\".";
println "contains check for \"This\" result: ", containsResult, ".";

int testStringLength = -1;
call length : CONTAINS_TEST_STRING -> testStringLength;
println "called length on \"", CONTAINS_TEST_STRING, "\".";
println "length result: ", testStringLength, ".";

int findResult = -1;
call find : CONTAINS_TEST_STRING, "a" -> findResult;
println "called find on \"", CONTAINS_TEST_STRING, "\".";
println "find check for \"a\" result: ", findResult, ".";

string testSubstring;
call substring : CONTAINS_TEST_STRING, 0, 4 -> testSubstring;
println "called substring on \"", CONTAINS_TEST_STRING, "\".";
println "substring from 0 to 4 result: \"", testSubstring, "\".";

string firstChar = "?";
call char_at : CONTAINS_TEST_STRING, 0 -> firstChar;
println "called char_at on \"", CONTAINS_TEST_STRING, "\".";
println "char_at result for 0: ", firstChar, ".";

int charInt = -1;
call char_to_int : firstChar -> charInt;
println "called char_to_int on \"T\".";
println "char_to_int result: ", charInt, ".";

int iToS = 234;
double dToS = 3.14;
string sToI = "987";
string sToD = "2.718";

int tempInt = -1;
call to_int : sToI -> tempInt;
println "called to_int on ", sToI, ".";
println "to_int result: ", tempInt, ".";

tempDouble = -1.0;
call to_double : sToD -> tempDouble;
println "called to_double on ", sToD, ".";
println "to_double result: ", tempDouble, ".";

string tempString = "?";
call int_to_string : iToS -> tempString;
println "called int_to_string on ", iToS, ".";
println "int_to_string result: ", tempString, ".";

tempString = "?";
call double_to_string : dToS -> tempString;
println "called double_to_string on ", dToS, ".";
println "double_to_string result: ", tempString, ".";
```

# Test script output

```
Concert
Version: 0.0.4.1
Author: Daniel Puckowski
count: 1000000
is_file_exist result: musicmanagerinstaller.exe query returned 1.
called create_file... created "create_file_test.txt".
is_file_exist result: create_file_test.txt query returned 1.
get_file_size result: musicmanagerinstaller.exe is 1129376 bytes large.
called open_file on: "create_file_test.txt".
called close_file on: "create_file_test.txt".
called remove_file on: "create_file_test.txt".
is_file_exist result: create_file_test.txt query returned 0.
called create_file... created "create_file_test.txt".
called open_file on: "create_file_test.txt".
called is_open on "create_file_test.txt".
is_open result: 1.
called is_end on "create_file_test.txt".
is_end result: 0.
called write_string on: "create_file_test.txt".
wrote: "Hello, world!".
called close_file on: "create_file_test.txt".
called open_file on: "create_file_test.txt".
get_line result: Hello, world!
called close_file on: "create_file_test.txt".
called rename_file on : "create_file_test.txt".
renamed to: "create_file_test_2.txt".
called remove_file on: "create_file_test_2.txt".
is_file_exist result: create_file_test_2.txt query returned 0.
called create_file... created "create_file_test.txt".
called open_file on: "create_file_test.txt".
called write_string on: "create_file_test.txt".
wrote: "Hello, world!".
called close_file on: "create_file_test.txt".
called open_file on: "create_file_test.txt".
called is_end on "create_file_test.txt".
is_end result: 0.
called tell_file_pointer on "create_file_test.txt".
tell_file_pointer result: 0.
called seek_file_pointer on "create_file_test.txt".
called read_byte on "create_file_test.txt".
read_byte result: 72.
called char_to_string on 72.
char_to_string result: H.
called is_end on "create_file_test.txt".
is_end result: 0.
called tell_file_pointer on "create_file_test.txt".
tell_file_pointer result: 1.
called seek_file_pointer on "create_file_test.txt".
called read_byte on "create_file_test.txt".
read_byte result: 101.
called char_to_string on 101.
char_to_string result: e.
called is_end on "create_file_test.txt".
is_end result: 0.
called tell_file_pointer on "create_file_test.txt".
tell_file_pointer result: 2.
called seek_file_pointer on "create_file_test.txt".
called read_byte on "create_file_test.txt".
read_byte result: 108.
called char_to_string on 108.
char_to_string result: l.
called is_end on "create_file_test.txt".
is_end result: 0.
called tell_file_pointer on "create_file_test.txt".
tell_file_pointer result: 3.
called seek_file_pointer on "create_file_test.txt".
called read_byte on "create_file_test.txt".
read_byte result: 108.
called char_to_string on 108.
char_to_string result: l.
called is_end on "create_file_test.txt".
is_end result: 0.
called tell_file_pointer on "create_file_test.txt".
tell_file_pointer result: 4.
called seek_file_pointer on "create_file_test.txt".
called read_byte on "create_file_test.txt".
read_byte result: 111.
called char_to_string on 111.
char_to_string result: o.
called is_end on "create_file_test.txt".
is_end result: 0.
called tell_file_pointer on "create_file_test.txt".
tell_file_pointer result: 5.
called seek_file_pointer on "create_file_test.txt".
called read_byte on "create_file_test.txt".
read_byte result: 44.
called char_to_string on 44.
char_to_string result: ,.
called is_end on "create_file_test.txt".
is_end result: 0.
called tell_file_pointer on "create_file_test.txt".
tell_file_pointer result: 6.
called seek_file_pointer on "create_file_test.txt".
called read_byte on "create_file_test.txt".
read_byte result: 32.
called char_to_string on 32.
char_to_string result:  .
called is_end on "create_file_test.txt".
is_end result: 0.
called tell_file_pointer on "create_file_test.txt".
tell_file_pointer result: 7.
called seek_file_pointer on "create_file_test.txt".
called read_byte on "create_file_test.txt".
read_byte result: 119.
called char_to_string on 119.
char_to_string result: w.
called is_end on "create_file_test.txt".
is_end result: 0.
called tell_file_pointer on "create_file_test.txt".
tell_file_pointer result: 8.
called seek_file_pointer on "create_file_test.txt".
called read_byte on "create_file_test.txt".
read_byte result: 111.
called char_to_string on 111.
char_to_string result: o.
called is_end on "create_file_test.txt".
is_end result: 0.
called tell_file_pointer on "create_file_test.txt".
tell_file_pointer result: 9.
called seek_file_pointer on "create_file_test.txt".
called read_byte on "create_file_test.txt".
read_byte result: 114.
called char_to_string on 114.
char_to_string result: r.
called is_end on "create_file_test.txt".
is_end result: 0.
called tell_file_pointer on "create_file_test.txt".
tell_file_pointer result: 10.
called seek_file_pointer on "create_file_test.txt".
called read_byte on "create_file_test.txt".
read_byte result: 108.
called char_to_string on 108.
char_to_string result: l.
called is_end on "create_file_test.txt".
is_end result: 0.
called tell_file_pointer on "create_file_test.txt".
tell_file_pointer result: 11.
called seek_file_pointer on "create_file_test.txt".
called read_byte on "create_file_test.txt".
read_byte result: 100.
called char_to_string on 100.
char_to_string result: d.
called is_end on "create_file_test.txt".
is_end result: 0.
called tell_file_pointer on "create_file_test.txt".
tell_file_pointer result: 12.
called seek_file_pointer on "create_file_test.txt".
called read_byte on "create_file_test.txt".
read_byte result: 33.
called char_to_string on 33.
char_to_string result: !.
called is_end on "create_file_test.txt".
is_end result: 0.
called tell_file_pointer on "create_file_test.txt".
tell_file_pointer result: 13.
called seek_file_pointer on "create_file_test.txt".
called read_byte on "create_file_test.txt".
read_byte result: -57.
called char_to_string on -57.
char_to_string result: ╟.
called is_end on "create_file_test.txt".
is_end result: 1.
called tell_file_pointer on "create_file_test.txt".
tell_file_pointer result: -1.
called seek_file_pointer on "create_file_test.txt".
called read_byte on "create_file_test.txt".
read_byte result: -57.
called char_to_string on -57.
char_to_string result: ╟.
called close_file on: "create_file_test.txt".
called open_file on: "create_file_test.txt".
called close_file on: "create_file_test.txt".
called remove_file on: "create_file_test.txt".
called seed_random.
called get_random.
get_random result: 718.
called get_random.
get_random result: 27133.
called get_random.
get_random result: 13276.
called get_random.
get_random result: 6701.
called get_random.
get_random result: 5340.
called get_random.
get_random result: 28572.
called get_random.
get_random result: 17383.
called get_random.
get_random result: 2709.
called get_random.
get_random result: 22603.
called get_random.
get_random result: 1180.
called get_random.
get_random result: 3902.
called get_random.
get_random result: 4294.
called get_random.
get_random result: 30552.
called get_random.
get_random result: 21463.
called get_random.
get_random result: 22695.
called get_random.
get_random result: 23164.
called get_random.
get_random result: 18075.
called get_random.
get_random result: 1555.
called get_random.
get_random result: 29214.
called get_random.
get_random result: 19671.
called int_to_double.
int_to_double result: 5.000000.
called double_to_int.
double_to_int result: 5.
called int_to_long.
int_to_long result: 1000.
called contains on "This is a test string.".
contains check for "This" result: 1.
called length on "This is a test string.".
length result: 22.
called find on "This is a test string.".
find check for "a" result: 8.
called substring on "This".
substring from 0 to 4 result: "This".
called char_at on "This".
char_at result for 0: T.
called char_to_int on "T".
char_to_int result: 84.
called to_int on 987.
to_int result: 987.
called to_double on 2.718.
to_double result: 2.718000.
called int_to_string on 234.
int_to_string result: 234.
called double_to_string on 3.140000.
double_to_string result: 3.140000.
Delta: 6s 6213ms 6213117281ns
```

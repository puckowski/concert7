[Home](https://github.com/puckowski/concert7/blob/master/)

# Test script

```cpp
import string;
import math;
import io;
import regex;
import thread;

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

	call wchar_to_string : byte -> char;
	println "called wchar_to_string on ", byte, ".";
	println "wchar_to_string result: ", char, ".";
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
int numberOfRandInterations = 20;

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

string CONTAINS_TEST_STRING = "This is a test string.";

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
call wchar_to_int : firstChar -> charInt;
println "called wchar_to_int on \"T\".";
println "wchar_to_int result: ", charInt, ".";

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

import string;
import math;

function crc16 : string as message, int as length;
	int crc = 65535;
	int j = 0;
	string char;
	int charValue;
	
	while j < length;
		crc = ((crc >>> 8) | (crc << 8)) & 65535;
		
		call char_at : message, j -> char;
        call wchar_to_int : char -> charValue;
		
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

int y = -5;
double z = -3.14;
int yy;
call absolute_value : y -> yy;
double zz;
call absolute_value : z -> zz;
println yy, " ", zz;
int oc = 0 ~ 50;
println oc;
oc = 0;
oc ~= 50;
println oc;

object maze 5;
int index = 0;
while index < 5;
    int maze[index].x 5;
    int initIndex = 0;
    while initIndex < 5;
        maze[index].x[initIndex] = initIndex + 1;
        initIndex += 1;
    end;
    index += 1;
end;

index = 0;
while index < 5;
    int innerIndex = 0;
    while innerIndex < 5;
        #print maze[index].x[innerIndex];
		innerIndex += 1;
    end;
    #println " ";
	index += 1;
end;

string data = "(Speed:366 Mass:35 Speed:378 Mass:32";
string regex = "(Speed:\d*)";

call regex_search : "result", data, regex;

println result.length;
println result.data[0], result.data[1], " done.";

int x = 0;

while x < result.length[0]; println "in in loop"; int y = 5; println y; y ~= 123; println y;
	println result.data[x];
	x += 1;
end;

int match;
string data2 = "subject";
string regex2 = "(sub)(.*)";

call regex_match : data2, regex2 -> match;

println match;

string r1 = "there is a subsequence in the string\n";
string r2 = "\b(sub)([^ ]*)";
string r3;
string r4 = "sub-$2";

call regex_replace : r1, r2, r4 -> r3;

println r3;

string threadName;
call get_thread_id -> threadName;
println "thread name: ", threadName;
```

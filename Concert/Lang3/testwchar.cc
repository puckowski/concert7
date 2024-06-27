import io;
import string;

call open_file : "testchinese.txt", 1;
println "called open_file on: \"testchinese.txt\".";

int isFileAtEnd = 0;
int filePointer = 0;
int wchar;
string char;

while isFileAtEnd == 0;
	call tell_file_pointer : "testchinese.txt" -> filePointer;
	println "called tell_file_pointer on \"testchinese.txt\".";
	println "tell_file_pointer result: ", filePointer, ".";
		
	call seek_file_pointer : "testchinese.txt", filePointer;
	println "called seek_file_pointer on \"testchinese.txt\".";

	call read_wchar : "testchinese.txt" -> wchar;
	println "called read_wchar on \"testchinese.txt\".";
	println "read_byte result: ", wchar, ".";
		
	call is_end : "testchinese.txt" -> isFileAtEnd;
	println "called is_end on \"testchinese.txt\".";
	println "is_end result: ", isFileAtEnd, ".";
		
	if isFileAtEnd != 1;
		call wchar_to_string : wchar -> char;
		println "called wchar_to_string on ", wchar, ".";
		println "wchar_to_string result: ", char, ".";
		
		call wchar_to_int : char -> wchar;
		println "called wchar_to_int on ", char, ".";
		println "wchar_to_int result: ", wchar, ".";
		
		call tell_file_pointer : "testchinese.txt" -> filePointer;
		println "called tell_file_pointer on \"testchinese.txt\".";
		println "tell_file_pointer result: ", filePointer, ".";
	end;
end;

call close_file : "testchinese.txt";
println "called close_file on: \"testchinese.txt\".";

call open_byte_file : "testchinese.txt", 1;
println "called open_file on: \"testchinese.txt\".";

isFileAtEnd = 0;
filePointer = 0;
int byte;
string char;

while isFileAtEnd == 0;
	call tell_file_pointer : "testchinese.txt" -> filePointer;
	println "called tell_file_pointer on \"testchinese.txt\".";
	println "tell_file_pointer result: ", filePointer, ".";
		
	call seek_file_pointer : "testchinese.txt", filePointer;
	println "called seek_file_pointer on \"testchinese.txt\".";

	call read_byte : "testchinese.txt" -> byte;
	println "called read_byte on \"testchinese.txt\".";
	println "read_byte result: ", byte, ".";
		
	call is_end : "testchinese.txt" -> isFileAtEnd;
	println "called is_end on \"testchinese.txt\".";
	println "is_end result: ", isFileAtEnd, ".";
		
	if isFileAtEnd != 1;
		call char_to_string : byte -> char;
		println "called char_to_string on ", byte, ".";
		println "char_to_string result: ", char, ".";
		
		call wchar_to_int : char -> byte;
		println "called wchar_to_int on ", char, ".";
		println "wchar_to_int result: ", byte, ".";
		
		call tell_file_pointer : "testchinese.txt" -> filePointer;
		println "called tell_file_pointer on \"testchinese.txt\".";
		println "tell_file_pointer result: ", filePointer, ".";
	end;
end;

call close_file : "testchinese.txt";
println "called close_file on: \"testchinese.txt\".";

call open_file : "testchinese.txt", 1;
println "called open_file on: \"testchinese.txt\".";

isFileAtEnd = 0;
filePointer = 0;
string line;

while isFileAtEnd == 0;
	call get_line : "testchinese.txt" -> line;
	println "called get_line on \"testchinese.txt\".";
	println "get_line result: ", line, ".";
	
	call is_end : "testchinese.txt" -> isFileAtEnd;
	println "called is_end on \"testchinese.txt\".";
	println "is_end result: ", isFileAtEnd, ".";
end;

call close_file : "testchinese.txt";
println "called close_file on: \"testchinese.txt\".";

call open_byte_file : "testchinese.txt", 1;
println "called open_file on: \"testchinese.txt\".";

isFileAtEnd = 0;
filePointer = 0;
line = "";

while isFileAtEnd == 0;
	call get_line : "testchinese.txt" -> line;
	println "called get_line on \"testchinese.txt\".";
	println "get_line result: ", line, ".";
		
	call is_end : "testchinese.txt" -> isFileAtEnd;
	println "called is_end on \"testchinese.txt\".";
	println "is_end result: ", isFileAtEnd, ".";
end;

call close_file : "testchinese.txt";
println "called close_file on: \"testchinese.txt\".";

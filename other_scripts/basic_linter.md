[Home](https://github.com/puckowski/concert7)

# Basic linter

Basic Concert Programming Language linter which may be expanded upon.

## Code

```cpp
import io;
import string;
import math;

string filename;
println "Enter name of file to run linter on.";
print "> ";
readln filename;

call open_file : filename;

int isOpen;
call is_open : filename -> isOpen;

int lineCount = 0;

if isOpen == 1;
	println "File opened.";

	string line;
	int isEnd;
	call is_end : filename -> isEnd;
	while isEnd == 0;
		call get_line : filename -> line;
		lineCount += 1;
		
		call is_end : filename -> isEnd;
	end;
	
	println "File has ", lineCount, " lines.";
	call close_file : filename;
else;
	println "Failed to open file: ", filename;
	
	exit;
end;

string sourceLines lineCount;

call open_file : filename;
call is_open : filename -> isOpen;

if isOpen == 1;
	println "File opened.";

	int index = 0;
	call is_end : filename -> isEnd;
	while isEnd == 0;
		call get_line : filename -> line;
		println line;
		
		sourceLines[index] = line;
		index += 1;
		
		call is_end : filename -> isEnd;
	end;
	
	println "Done reading lines.";
	call close_file : filename;
end;

function trimString : string as toTrim;
	string trimmed;
	
	string char;
	int i = 0;
	int leadingSpaces = 0;
	
	call char_at : toTrim, i -> char;
	
	while char == " ";
		leadingSpaces += 1;
		i += 1;
		
		call char_at : toTrim, i -> char;
	end;
	
	if leadingSpaces > 0;
		leadingSpaces -= 1;
	end;
	
	int len;
	call length : toTrim -> len;

	call substring : toTrim, leadingSpaces, len -> trimmed;
	
	call length : trimmed -> i;
	i -= 1;
	
	call char_at : trimmed, i -> char;
		
	while char == " ";
		i -= 1;
		
		call char_at : trimmed, i -> char;
	end;
	
	i += 1;
	
	call substring : trimmed, 0, i -> trimmed;
return trimmed;

function clearTokens : using tokens, using TOKENS_SIZE;
	int i = 0;
	
	while i < TOKENS_SIZE;
		tokens[i] = "";
		i += 1;
	end;
return;

function printTokens : using tokens, using TOKENS_SIZE;
	int i = 0;
	
	while i < TOKENS_SIZE;
		if tokens[i] != "";
			println tokens[i];
		end;
		
		i += 1;
	end;
return;

function tokenizeLine : using LINT_FILENAME, using tokens, using TOKENS_SIZE, using sourceLines, int as index;
	string line = sourceLines[index];
	
	println "Tokenizing line: ", line, ".";
	
	int tokenIndex = 0;
	
	int hasSpace;
	call contains : line, " " -> hasSpace;
	
	string token;
	int i;
	int len;
	
	while hasSpace == 1;
		call find : line, " " -> i;
		call substring : line, 0, i -> token;
		
		tokens[tokenIndex] = token;
		tokenIndex += 1;
		
		if tokenIndex == TOKENS_SIZE;
			string indexMessage = "Index: ";
			string indexString;
			call int_to_string : index -> indexString;
			indexMessage += indexString;
			
			call write_string : LINT_FILENAME, "Long line. Consider refactoring.";
			call write_string : LINT_FILENAME, "\n";
			call write_string : LINT_FILENAME, indexMessage;
			call write_string : LINT_FILENAME, "\n";
			
			break;
		end;
		
		i += 1;
		
		call length : line -> len;
		call substring : line, i, len -> line;
		
		call contains : line, " " -> hasSpace;
	end;
	
	tokens[tokenIndex] = line;
return;

function hasSemicolon : using LINT_FILENAME, using tokens, using TOKENS_SIZE, int as index;
	int i = 0;
	
	int foundSemicolon = 0;
	
	while i < TOKENS_SIZE;
		if tokens[i] == "";
			i += 1;
		
			continue;
		end;
		
		call contains : tokens[i], ";" -> foundSemicolon;
		
		if foundSemicolon == 1;
			break;
		end;
		
		i += 1;
	end;

	if foundSemicolon == 0;
		string indexMessage = "Index: ";
		string indexString;
		call int_to_string : index -> indexString;
		indexMessage += indexString;
			
		call write_string : LINT_FILENAME, "Line has no semicolon.";
		call write_string : LINT_FILENAME, "\n";
		call write_string : LINT_FILENAME, indexMessage;
		call write_string : LINT_FILENAME, "\n";
	end;
return;

function ifEqualsCheck : using LINT_FILENAME, using tokens, using TOKENS_SIZE, int as index;
	int i = 0;
		
	int checkNext = 0;
	
	while i < TOKENS_SIZE;
		if tokens[i] == "";
			i += 1;
		
			continue;
		end;
		
		if tokens[i] == "if";
			checkNext = 2;
		else;
			if checkNext == 1;
				if tokens[i] == "=";
					string indexMessage = "Index: ";
					string indexString;
					call int_to_string : index -> indexString;
					indexMessage += indexString;
			
					call write_string : LINT_FILENAME, "Invalid if statement comparison. Is assignment.";
					call write_string : LINT_FILENAME, "\n";
					call write_string : LINT_FILENAME, indexMessage;
					call write_string : LINT_FILENAME, "\n";
				end;
			end;
			
			checkNext -= 1;
		end;
		
		i += 1;
	end;	
return;

int TOKENS_SIZE = 200;
string tokens TOKENS_SIZE;

string LINT_FILENAME = "lint_out.cc";

call create_file : LINT_FILENAME;
call open_file : LINT_FILENAME;

index = 0;

while index < lineCount;
	call clearTokens : tokens, TOKENS_SIZE;
	call tokenizeLine : LINT_FILENAME, tokens, TOKENS_SIZE, sourceLines, index;
	#call printTokens : tokens, TOKENS_SIZE;
	
	# Lint functions
	call hasSemicolon : LINT_FILENAME, tokens, TOKENS_SIZE, index;
	call ifEqualsCheck : LINT_FILENAME, tokens, TOKENS_SIZE, index;
	
	index += 1;
end;

call close_file : LINT_FILENAME;

println "Linter done running.";
```
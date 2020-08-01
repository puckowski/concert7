[Home](https://puckowski.github.io/concert/)

# Code examples

```cpp
function reverseString : string as input;
	string reversed = "";
	string strTmp;
	int len;

	call length : input -> len;
	len -= 1;

	while len >= 0;
		call char_at : input, len -> strTmp;
		reversed += strTmp;
		len -= 1;
	end;
return reversed;

function startsWith : string as input, string as startStr;
	string firstChars;
	int len;
	string strTmp;
	int index = 0;
	
	call length : startStr -> len;
	
	while len > 0;
		call char_at : input, index -> strTmp;
		firstChars += strTmp;
		len -= 1;
		index += 1;
	end;
	
	int toReturn;
	
	if firstChars == startStr;
		toReturn = 1;
	else;
		toReturn = 0;
	end;
return toReturn;

function endsWith : string as input, string as startStr;
	string firstChars;
	int lenStr;
	int lenInput;
	int start;
	string strTmp;
	
	call length : startStr -> lenStr;
	call length : input -> lenInput;
	
	lenInput -= lenStr;
	
	start = lenInput;
	call length : input -> lenInput;
	
	while start < lenInput;
		call char_at : input, start -> strTmp;
		firstChars += strTmp;
		start += 1;
	end;
	
	int toReturn;
	
	if firstChars == startStr;
		toReturn = 1;
	else;
		toReturn = 0;
	end;
return toReturn;

function substring : string as input, int as start, int as endIndex;
	string substr = "";
	string strTmp;

	while start < endIndex;
		call char_at : input, start -> strTmp;
		substr += strTmp;
		start += 1;
	end;
return substr;

function indexOf : string as input, string as substr;
	int index = -1;
	int len;
	int inputLen;
	string tmp;
	
	call length : substr -> len;
	call length : input -> inputLen;
	
	int startIndex = 0;
	int endIndex = len;

	inputLen -= len;

	while endIndex <= inputLen;
		call substring : input, startIndex, endIndex -> tmp;

		if tmp == substr;
			index = startIndex;
			index -= 1;
			
			break 2;
		end;
		
		startIndex += 1;
		endIndex += 1;
	end;
return index;

function lastIndexOf : string as input, string as substr;
	int index = -1;
	int len;
	int inputLen;
	string tmp;
	
	call length : substr -> len;
	call length : input -> inputLen;
	
	int startIndex = 0;
	int endIndex = len;

	inputLen -= len;

	while endIndex <= inputLen;
		call substring : input, startIndex, endIndex -> tmp;

		if tmp == substr;
			index = startIndex;
			index -= 1;
		end;
		
		startIndex += 1;
		endIndex += 1;
	end;
return index;

function replaceAll : string as input, string as substr, string as toReplace;
	int lenSubstr;
	int len;
	
	call length : substr -> lenSubstr;
	call length : input -> len;
	
	int start = 0;
	int endIndex = lenSubstr;
	
	string replaced = "";
	string tmp;

	int replacedLast = 0;
	int lastIndex = 0;
	int replacedLastIndex = len;
	replacedLastIndex -= lenSubstr;
	
	while endIndex <= len;
		call substring : input, start, endIndex -> tmp;
		lastIndex = start;
		
		if tmp == substr;
			start += lenSubstr;
			endIndex += lenSubstr;
			
			replaced += toReplace;
			
			if lastIndex == replacedLastIndex;
				replacedLast = 1;
			end;
		else;
			call char_at : input, start -> tmp;
			replaced += tmp;
			
			start += 1;
			endIndex += 1;
		end;
	end;
	
	if replacedLast == 0;
		start = lastIndex;
	end;
	
	while start < len;
		call char_at : input, start -> tmp;
		replaced += tmp;
			
		start += 1;
	end;
return replaced;

function replaceFirst : string as input, string as substr, string as toReplace;
	int lenSubstr;
	int len;
	
	call length : substr -> lenSubstr;
	call length : input -> len;
	
	int start = 0;
	int endIndex = lenSubstr;
	
	string replaced = "";
	string tmp;

	int replacedFirst = 0;
	
	int replacedLast = 0;
	int lastIndex = 0;
	int replacedLastIndex = len;
	replacedLastIndex -= lenSubstr;
	
	while endIndex <= len;
		call substring : input, start, endIndex -> tmp;
		lastIndex = start;
		
		if tmp == substr;
			start += lenSubstr;
			endIndex += lenSubstr;
			
			if replacedFirst == 0;
				replaced += toReplace;
				replacedFirst = 1;
				
				break 3;
			end;
		else;
			call char_at : input, start -> tmp;
			replaced += tmp;
			
			start += 1;
			endIndex += 1;
		end;
	end;
	
	if replacedLast == 0;
		start = lastIndex;
	end;
	
	while start < len;
		call char_at : input, start -> tmp;
		replaced += tmp;
			
		start += 1;
	end;
return replaced;

function convertIntToBase : int as input, int as newBase;
	string strValue = "";
	string strTmp;
	
	int inputCopy = input;
	
	while input > 0;
		inputCopy = input % newBase;
		input /= newBase;
		
		call int_to_string : inputCopy -> strTmp;
		strValue += strTmp;
		
		inputCopy = input;
	end;
	
	string reversed;
	call reverseString : strValue -> reversed;
return reversed;

function convertIntToHex : int as input, int as newBase;
	string strValue = "";
	string strTmp;
	
	int inputCopy = input;
	
	while input > 0;
		inputCopy = input % newBase;
		input /= newBase;
		
		call int_to_string : inputCopy -> strTmp;
			
		int tmpInt;
		call to_int : strTmp -> tmpInt;
								
		if tmpInt < 10;
			strValue += strTmp;
		else;						
			if strTmp == "10";
				strValue += "a";
			else;
				if strTmp == "11";
					strValue += "b";
				else;
					if strTmp == "12";
						strValue += "c";
					else;
						if strTmp == "13";
							strValue += "d";
						else;
							if strTmp == "14";
								strValue += "e";
							else;
								if strTmp == "15";
									strValue += "f";
								else;								
									
								end;
							end;
						end;
					end;
				end;
			end;
		end;
		
		inputCopy = input;
	end;
	
	string reversed;
	call reverseString : strValue -> reversed;
return reversed;
```
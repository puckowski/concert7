[Home](https://github.com/puckowski/concert7/blob/master/)

# Reference Set implementation

Basic Concert Programming Language Set implementation which may be expanded upon.

## Code

```
import string;
import math;

function murmurHash32 : string as key, int as seed;
	int m = 1540483477;
	int r = 24;
	
	int keyLength;
	call length : key -> keyLength;
	
	int h = seed;
	h = h ^ keyLength;
		
	int i = 0;
	
	while i < keyLength;
		int k = 0;
		string char;
		call char_at : key, i -> char;
		call char_to_int : char -> k;
		
		k *= m;
		int tmp = k;
		tmp = tmp >> r;
		k = k ^ tmp;
		
		k *= m;
		
		h *= m;
		h = h ^ k;
		
		i = i + 1;
	end;
	
	int tmp = h;
	tmp = tmp >> 13;
	h = h ^ tmp;
	
	h *= m;
	tmp = h;
	tmp = tmp >> 15;
	h = h ^ tmp;
	
return h;

function doubleArraySize : using standard_vector;
	int size = 0;
	sizeof standard_vector size;
	
	int doubleSize = size * 2;
	
	string type;
	instanceof standard_vector type;
			
	if type == "int";
		int newArray doubleSize;
		int i = 0;
		while i < size;
			newArray[i] = standard_vector[i];
			i += 1;
		end;
		while i < doubleSize;
			newArray[i] = 0;
			i += 1;
		end;
		reassign standard_vector newArray;
	end;
	
	if type == "long";
		long newArray doubleSize;
		int i = 0;
		while i < size;
			newArray[i] = standard_vector[i];
			i += 1;
		end;
		while i < doubleSize;
			newArray[i] = 0;
			i += 1;
		end;
		reassign standard_vector newArray;
	end;
		
	if type == "double";
		double newArray doubleSize;
		int i = 0;
		while i < size;
			newArray[i] = standard_vector[i];
			i += 1;
		end;
		while i < doubleSize;
			newArray[i] = 0.0;
			i += 1;
		end;
		reassign standard_vector newArray;
	end;
		
	if type == "string";
		string newArray doubleSize;
		int i = 0;
		while i < size;
			newArray[i] = standard_vector[i];
			i += 1;
		end;
		while i < doubleSize;
			newArray[i] = "";
			i += 1;
		end;
		reassign standard_vector newArray;
	end;
return;

int BUCKET_COUNT = 32;
int BUCKET_LIST_SIZE = 10;

object buckets BUCKET_COUNT;

function initalizeSet : using buckets, int as BUCKET_COUNT, int as BUCKET_LIST_SIZE;
	int index = 0;
	while index < BUCKET_COUNT;
		string buckets[index].list BUCKET_LIST_SIZE;
		int buckets[index].listIndex;
		int buckets[index].size;
		
		int initIndex = 0;
		while initIndex < BUCKET_LIST_SIZE;
			buckets[index].list[initIndex] = "";
			initIndex += 1;
		end;
		
		int buckets[index].listIndex = 0;
		int buckets[index].size = BUCKET_LIST_SIZE;
		
		index += 1;
	end;
return;

function getBucketIndex : string as key, int as BUCKET_COUNT;
	int hashCode = 0;
	call murmurHash32 : key, 0 -> hashCode;
	
	int index = hashCode % BUCKET_COUNT;
	
return index;

function addToSet : string as keyValue, using buckets, int as BUCKET_COUNT, int as BUCKET_LIST_SIZE;
	if keyValue == "";
		keyValue = "\"\"";
	end;
	
	int bucketIndex = 0;
	call getBucketIndex : keyValue, BUCKET_COUNT -> bucketIndex;
	
	int index = 0;
	int hasKeyValue = 0;
	while index < BUCKET_LIST_SIZE;
		if buckets[bucketIndex].list[index] == keyValue;
			hasKeyValue = 1;
			index = BUCKET_LIST_SIZE;
		end;
		
		index += 1;
	end;
	
	if hasKeyValue == 0;
		int insertIndex = buckets[bucketIndex].listIndex;
		
		if insertIndex == buckets[bucketIndex].size;
			alias buckets[bucketIndex].list "standard_vector";
			int doubleSize = buckets[bucketIndex].size;
			doubleSize *= 2;
			call doubleArraySize : standard_vector;
			buckets[bucketIndex].size = doubleSize;

			reassign buckets[bucketIndex].list standard_vector;
		end;
		
		buckets[bucketIndex].list[insertIndex] = keyValue;
		buckets[bucketIndex].listIndex = buckets[bucketIndex].listIndex + 1;
	end;
return;

function removeFromSet : string as keyValue, using buckets, int as BUCKET_COUNT, int as BUCKET_LIST_SIZE;
	if keyValue == "";
		keyValue = "\"\"";
	end;
	
	int bucketIndex = 0;
	call getBucketIndex : keyValue, BUCKET_COUNT -> bucketIndex;
	
	int index = 0;
	int hasKeyValue = 0;
	int keyValueIndex = -1;
	
	while index < BUCKET_LIST_SIZE;
		if buckets[bucketIndex].list[index] == keyValue;
			hasKeyValue = 1;
			keyValueIndex = index;
			index = BUCKET_LIST_SIZE;
		end;
		
		index += 1;
	end;
	
	if hasKeyValue == 1;
		buckets[bucketIndex].list[keyValueIndex] = "";
	end;
return;

function setContains : string as keyValue, using buckets, int as BUCKET_COUNT, int as BUCKET_LIST_SIZE;
	if keyValue == "";
		keyValue = "\"\"";
	end;
	
	int bucketIndex = 0;
	call getBucketIndex : keyValue, BUCKET_COUNT -> bucketIndex;
	
	int index = 0;
	int hasKeyValue = 0;
	
	while index < BUCKET_LIST_SIZE;
		if buckets[bucketIndex].list[index] == keyValue;
			hasKeyValue = 1;
			index = BUCKET_LIST_SIZE;
		end;
		
		index += 1;
	end;
return hasKeyValue;

function getSetSize : using buckets, int as BUCKET_COUNT, int as BUCKET_LIST_SIZE;
	int size = 0;
	int index = 0;
	
	while index < BUCKET_COUNT;
		size += buckets[index].listIndex;
	
		index += 1;
	end;
	
return size;

call initalizeSet : buckets, BUCKET_COUNT, BUCKET_LIST_SIZE;

int containsValue = 0;
call setContains : "abc", buckets, BUCKET_COUNT, BUCKET_LIST_SIZE -> containsValue;

println "Contains: ", containsValue;

call addToSet : "abc", buckets, BUCKET_COUNT, BUCKET_LIST_SIZE;

call setContains : "abc", buckets, BUCKET_COUNT, BUCKET_LIST_SIZE -> containsValue;

println "Contains: ", containsValue;

call removeFromSet : "abc", buckets, BUCKET_COUNT, BUCKET_LIST_SIZE;

call setContains : "abc", buckets, BUCKET_COUNT, BUCKET_LIST_SIZE -> containsValue;

println "Contains: ", containsValue;

int addIndex = 0;
while addIndex < 2000;
	string data = "abc";
	string numStr = "";
	call int_to_string : addIndex -> numStr;
	data += numStr;
	
	call addToSet : data, buckets, BUCKET_COUNT, BUCKET_LIST_SIZE;
	
	addIndex += 1;
end;

int setSize = 0;
call getSetSize : buckets, BUCKET_COUNT, BUCKET_LIST_SIZE -> setSize;

println "Set size: ", setSize;

call setContains : "abc113", buckets, BUCKET_COUNT, BUCKET_LIST_SIZE -> containsValue;

println "Contains: ", containsValue;

call setContains : "abc113n", buckets, BUCKET_COUNT, BUCKET_LIST_SIZE -> containsValue;

println "Contains: ", containsValue;
```
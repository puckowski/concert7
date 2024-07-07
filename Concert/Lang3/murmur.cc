import string;
import math;

function murmurHash32 : string as key, int as seed;
	int m = 1540483477;
	int r = 24;
	
	int keyLength;
	call length : key -> keyLength;
	
	int h = seed;
	h = h ^ keyLength;
	
	println m;
	println h;
	
	int i = 0;
	
	while i < keyLength;
		int k = 0;
		string char;
		call char_at : key, i -> char;
		call char_to_int : char -> k;
		
		
		k *= m;
		println k;
		int tmp = k;
		tmp = tmp >> r;
		k = k ^ tmp;
		println k;
		
		k *= m;
		println k;
		
		h *= m;
		h = h ^ k;
		println h;
		
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

string text = "Hello";

int hash;

call murmurHash32 : text, 0 -> hash;

println hash;

import string;

function murmurHash32 : string as key, int as seed;
	int m = 1540483477;
	int r = 24;
	
	int keyLength;
	call length : key -> keyLength;
	
	int h = seed;
	h = h ^ keyLength;
	
	println h;
	
	int i = 0;
	
	while i < keyLength;
		int k;
		string char;
		call char_at : key, i -> char;
		call char_to_int : char -> k;
		
		h = k * m;
		int shift = k;
		shift = shift >>> r;
		k = k ^ shift;
		k = k * m;
		
		h = h * m;
		h = h ^ k;
		
		i = i + 1;
	end;
	
	println h;
	
	int shift = h;
	shift = shift >>> 13;
	h = h ^ shift;
	h = h * m;
	shift = h;
	shift = shift >>> 15;
	h = h ^ shift;
	
	int result = h;
	result = result >>> 0;
	
return result;

string text = "Hello, world!";

int hash;

call murmurHash32 : text, 0 -> hash;

println hash;

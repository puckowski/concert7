import regex;

string data = "(Speed:366 Mass:35 Speed:378 Mass:32";
string regex = "(Speed:\d*)";

call regex_search : "result", data, regex;

println "len :", result.length;
println result.data[0], result.data[1], " done.";

int x = 0;

while x < result.length[0]; println "in in loop"; int y = 5; println y; y ~= 123; println y;
	println result.data[x];
	x += 1;
end;
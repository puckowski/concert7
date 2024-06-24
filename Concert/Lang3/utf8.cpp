
#include "utf8.h"

// Function to convert UTF-8 string to wstring
std::wstring utf8_to_wstring(const std::string& str) {
	return boost::locale::conv::to_utf<wchar_t>(str, "UTF-8");
}

// Function to convert wstring to UTF-8 string
std::string wstring_to_utf8(const std::wstring& wstr) {
	const std::string result = boost::locale::conv::utf_to_utf<char>(wstr);
	return result;
}

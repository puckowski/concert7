
#ifndef UTF_H
#define UTF_H

#include <string>
#include <vector>
#include <stack>
#include <thread>
#include <sstream>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <mutex>
#include <locale>
#include <boost/locale.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <locale>
#include <codecvt>

// Function to convert UTF-8 string to wstring
std::wstring utf8_to_wstring(const std::string& str);

// Function to convert wstring to UTF-8 string
std::string wstring_to_utf8(const std::wstring& wstr);

#endif

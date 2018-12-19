#pragma once

#include <string>

using std::string;

class StringDecompressor 
{
public:
	static string decompress(string compressed) {
		for (size_t i = 0; i < compressed.size(); ++i) {
			compressed[i] = 'z' - compressed[i];
		}
	}
};
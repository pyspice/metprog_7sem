#pragma once

#include <string>

using std::string;

template <class T>
class IDecompressor 
{
};

class StringDecompressor : public IDecompressor<string> {
public:
	static string decompress(string comp_value) {
		return comp_value + comp_value + comp_value;
	}
};
#pragma once

#include <string>
#include <functional>
#include "decompressable.h"

using std::string;
using std::hash;

class CompressedInt : public IDecompressable<int> 
{
public:
	CompressedInt(string compressed) 
	{
		this->compressed = compressed;
	}

	int decompress() const override
	{
		return (int)this->hasher(this->compressed);
	}

private:
	string compressed;
	static const hash<string> hasher;
};
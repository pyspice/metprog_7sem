#pragma once

template <class T>
class IDecompressable
{
public:
	virtual T decompress() const = 0;
};
#pragma once

#include <fstream>
#include <string>
#include <cstring>
#include <type_traits>
#include "typelist.h"

using std::ifstream;
using std::string;

using NoDecompressor = NullType;

template <typename List, typename Decompressables, typename Decompressors>
void ReadLine(ifstream& input, char* buffer);

template <>
void ReadLine<EmptyList, EmptyList, EmptyList>(ifstream& input, char* buffer) {}

template <typename List, typename Decompressables, typename Decompressors>
void ReadLine<List, Decompressables, Decompressors>
	(ifstream& input, char* buffer)
{
	string compressed;
	input >> compressed;

	using H = typename List::Head;
	H decompressed;

	using HDecompressor = typename Decompressors::Head;
	if (std::is_same<NoDecompressor, HDecompressor>::value) {
		using HDecompressable = typename Decompressables::Head;
		HDecompressable decompressable(compressed);
		decompressed = decompressable.decompress();
	}
	else {
		decompressed = HDecompressor::decompress(compressed);
	}

	size_t bufsiz = strlen(buffer);
	buffer = (char*)realloc(buffer, bufsiz + sizeof(H));
	*(buffer + bufsiz) = decompressed;

	ReadLine<typename List::Tail, typename Decompressables::Tail, typename Decompressors::Tail>(input, buffer);
};

template <typename List, typename Decompressables, typename Decompressors>
class Reader {
public:
	Reader(string filename) : input(filename) {}
	~Reader() { input.close(); }

	void* readNextLine() 
	{
		if (input.eof() || !input.is_open()) {
			return NULL;
		}

		char* buffer = (char*)malloc(1);
		buffer[0] = 0;

		ReadLine<List, Decompressables, Decompressors>(input, buffer);

		return (void*)buffer;
	}

private:
	ifstream input;
};
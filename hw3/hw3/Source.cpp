#include <fstream>
#include <iostream>
#include <string>
#include "typelist.h"
#include "Reader.h"
#include "int.h"
#include "decompressors.h"

using namespace std;

int main() {
	using List = TypeList<int, std::string>;
	using Decompressables = TypeList<CompressedInt, NullType>;
	using Decompressors = TypeList<NoDecompressor, StringDecompressor>;

	Reader<List, Decompressables, Decompressors> Reader("input.txt");
	void* buffer = Reader.readNextLine();
	while (buffer != NULL) {
		Write<List>((char*)buffer);
		buffer = Reader.readNextLine();
	}

	free(buffer);
}

template <typename List>
void Write(char* buffer) {
	using H = typename List::Head;
	cout << *((H*)buffer) << " ";
	buffer += sizeof(H);
	Write<typename List::Tail>(buffer);
}

template <>
void Write<EmptyList>(char* buffer) {
	cout << endl;
}
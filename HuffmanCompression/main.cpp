#pragma once
#include "TextToEncode.h"
#include "TextToDecode.h"

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		cout << "Invalid command, use -c <source> [dest] to compress and -d <source> [dest] to decompress" << endl;
	}
	else if (string(argv[1]) == string("-d"))
	{
		TextToDecode text(argv[2]);
		text.decodeText();
		if (argc == 4)
			text.writeDecodedText(argv[3]);
		else
			text.writeDecodedText("decompressed.txt");

	}
	else if (string(argv[1]) == string("-c"))
	{
		TextToEncode text(argv[2]);
		if (argc == 4)
			text.compressText(argv[3]);
		else
			text.compressText("compressed.txt");
	}
	else
	{
		cout << "Invalid command, use -c [source] [dest] to compress and -d [source] [dest] to decompress" << endl;
	}

	getchar();

	return 0;
}
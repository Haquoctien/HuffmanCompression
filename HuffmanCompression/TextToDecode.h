#pragma once
#include "Text.h"
#include "Node.h"
#include <string>
#include<bitset>

class TextToDecode :
	public Text
{
	unsigned headerSize;
	unsigned textSize;
	unsigned paddingSize;
	Node *HuffmanTree;
	string encodedData;
	string encodedHuffmanTree;
	string encodedText;
	string decodedText;
public:
	TextToDecode();
	TextToDecode(const char* file);
	~TextToDecode();
	void generateHuffmanTree(Node *tree);
	void decodeText();
	char decodeChar(Node *tree);
	void writeDecodedText(const char * file);
	void printHuffmanTree(Node *tree, string code = "")
	{
		if (!tree)
			return;
		if (tree->c != '\0')
			cout << tree->c << " : " << code << endl;
		printHuffmanTree(tree->left, code + "0");
		printHuffmanTree(tree->right, code + "1");
	}

};


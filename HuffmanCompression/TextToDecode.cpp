#include "TextToDecode.h"



TextToDecode::TextToDecode()
{
	textSize = paddingSize = headerSize = 0;
	HuffmanTree = NULL;
}

TextToDecode::TextToDecode(const char * file):Text(file)
{
	HuffmanTree = new Node();
	encodedData = "";
	for (auto c = data.begin(); c != data.end(); c++)
	{
		bitset<8> bitSequence(*c);
		encodedData += bitSequence.to_string();
	}

	headerSize = bitSequenceToChar(encodedData.substr(0, 8))* 10 -1;
	encodedData.erase(0, 8);
	paddingSize = bitSequenceToChar(encodedData.substr(0, 8));
	encodedData.erase(0, 8);

	encodedData.erase(0, paddingSize);

	textSize = encodedData.size() - headerSize - paddingSize;

	encodedHuffmanTree = encodedData.substr(0, headerSize);

	cout << "Huffman Tree: " << endl << encodedHuffmanTree << endl;
	cout << paddingSize << endl << headerSize <<endl<< textSize << endl;
	encodedData.erase(0, headerSize);

	encodedText = encodedData;
}

TextToDecode::~TextToDecode()
{
}

void TextToDecode::generateHuffmanTree(Node * tree)
{
	while (encodedHuffmanTree.length() > 0)
	{
		if (tree->left != NULL && tree->right != NULL) return;

		Node* node = new Node();
		if (encodedHuffmanTree[0] == '0')
		{
			encodedHuffmanTree.erase(0, 1);
			if (tree->left == NULL)
			{
				tree->left = node;
				generateHuffmanTree(tree->left);
			}
			else
			{
				tree->right = node;
				generateHuffmanTree(tree->right);
			}
		}

		else
		{
			string temp = encodedHuffmanTree.substr(1, 8);
			encodedHuffmanTree.erase(0, 9);

			node->c = bitSequenceToChar(temp);
			if (tree->left == NULL) tree->left = node;
			else tree->right = node;
		}
	}
}

void TextToDecode::decodeText()
{
	decodedText = "";
	generateHuffmanTree(HuffmanTree);
	printHuffmanTree(HuffmanTree);
	HuffmanTree = HuffmanTree->left;
	while (!encodedText.empty())
		decodedText += decodeChar(HuffmanTree);
}

char TextToDecode::decodeChar(Node * tree)
{
	if (!tree)
		return NULL;

	if (tree->left == NULL && tree->right == NULL)
		return tree->c;
	if (encodedText[0] == '0')
	{
		encodedText.erase(0, 1);
		decodeChar(tree->left);
	}
	else
	{
		encodedText.erase(0, 1);
		decodeChar(tree->right);
	}
}

void TextToDecode::writeDecodedText(const char * file)
{
	ofstream fileOut(file, ios::out| ios::binary);
	fileOut << decodedText;
	fileOut.close();
}
#pragma once
#include "Text.h"
#include "Node.h"
#include <vector>
#include <queue>
#include <map>
#include <bitset>
#include <fstream>
#include <utility>
#include <algorithm>

typedef pair<char, string> CodeEntry;
typedef pair<char, int> FrequencyEntry;
typedef map<char, int> FrequencyMap;
typedef map<char, string> EncodeMap;

class TextToEncode :
	public Text
{
private:
	EncodeMap encodeTable;
	Node *HuffmanTree;
	FrequencyMap frequencyTable;
	vector<Node*> FreqNodeQueue;
	string encodedHuffmanTree;
	string encodedText;
public:
	TextToEncode();
	TextToEncode(const char* file) :Text(file)
	{
		encodedText = "";
		encodedHuffmanTree = "";
	}
	virtual ~TextToEncode();
	void generateFreqTable();
	void generateOrderedFreqNodeQueue();
	void generateHuffmanTree();
	void generateEncodeTable(Node *, string);
	void encodeHuffmanTree(Node *);
	void encodeText();
	void compressText(string);
	void printHuffmanTree(Node* , string);

};


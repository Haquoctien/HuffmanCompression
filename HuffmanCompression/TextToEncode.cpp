#include "TextToEncode.h"


TextToEncode::TextToEncode()
{
	data = "";
	encodedText = "";
	encodedHuffmanTree = "";
}

TextToEncode::~TextToEncode()
{
}

void TextToEncode::generateFreqTable()
{
	CodeEntry code;

	for (auto i = data.begin(); i != data.end(); i++)
	{
		FrequencyMap::iterator freqEntry = frequencyTable.find(*i);
		if (freqEntry != frequencyTable.end())
			freqEntry->second += 1;
		else
			frequencyTable.insert(FrequencyEntry(*i, 1));
	}
}

void TextToEncode::generateOrderedFreqNodeQueue()
{
	for (auto i = frequencyTable.begin(); i != frequencyTable.end(); i++)
	{
		FreqNodeQueue.push_back(new Node(i->first, i->second));
	}
	sort(FreqNodeQueue.begin(), FreqNodeQueue.end(), compare);
}

void TextToEncode::generateHuffmanTree()
{
	while (true)
	{
		Node* tmp = new Node();
		tmp->left = FreqNodeQueue[0];
		tmp->right = FreqNodeQueue[1];
		tmp->fre = tmp->left->fre + tmp->right->fre;

		FreqNodeQueue.erase(FreqNodeQueue.begin(), FreqNodeQueue.begin() + 2);
		FreqNodeQueue.resize(FreqNodeQueue.size() + 1);

		if (FreqNodeQueue.size() == 1)
		{
			FreqNodeQueue[0] = tmp;
			break;
		}
		else
		{
			for (int j = 0; j < FreqNodeQueue.size() - 1; j++)
			{
				bool isMax = true;
				if (FreqNodeQueue[j]->fre > tmp->fre)
				{
					for (int k = FreqNodeQueue.size() - 1; k > j; k--)
					{
						FreqNodeQueue[k] = FreqNodeQueue[k - 1];
					}
					FreqNodeQueue[j] = tmp;
					isMax = false;
					break;
				}
				if (isMax) FreqNodeQueue[FreqNodeQueue.size() - 1] = tmp;
			}
		}
	}

	HuffmanTree = FreqNodeQueue[0];
}

void TextToEncode::generateEncodeTable(Node * tree, string code = "")
{
	if (tree != NULL)
	{
		if (tree->left == NULL || tree->right == NULL)
		{
			encodeTable.insert(CodeEntry(tree->c, code));
		}
		else
		{
			generateEncodeTable(tree->left, code + "0");
			generateEncodeTable(tree->right, code + "1");
		}
	}
}

void TextToEncode::encodeHuffmanTree(Node * curr)
{
	if (curr != NULL)
	{
		if (curr->left == NULL && curr->right == NULL)
		{
			encodedHuffmanTree += '1';
			bitset<8> bitSq(curr->c);
			encodedHuffmanTree += bitSq.to_string();
		}
		else
		{
			encodedHuffmanTree += '0';
			encodeHuffmanTree(curr->left);
			encodeHuffmanTree(curr->right);
		}
	}
}

void TextToEncode::encodeText()
{
	for (auto i = data.begin(); i != data.end(); i++)
	{
		auto entry = encodeTable.find(*i);
		if (entry != encodeTable.end())
			encodedText += entry->second;
	}
}

void TextToEncode::compressText(string file)
{
	this->generateFreqTable();
	this->generateOrderedFreqNodeQueue();
	this->generateHuffmanTree();
	this->encodeHuffmanTree(HuffmanTree);
	this->generateEncodeTable(HuffmanTree);
	this->encodeText();

	string charEncodedDataToWrite = bitStringToCharString(encodedHuffmanTree + encodedText);

	unsigned bitTextSize = encodedText.length();
	unsigned bitHeaderSize = encodedHuffmanTree.length();
	unsigned bitDataSize = bitHeaderSize + bitTextSize;
	unsigned bitPaddingSize = (8 - bitDataSize % 8) % 8;
	unsigned numberOfChar = encodeTable.size();

	ofstream fout(file, ios::out | ios::binary);
	fout << (char)numberOfChar << (char)bitPaddingSize << charEncodedDataToWrite;
	fout.close();

}

void TextToEncode::printHuffmanTree(Node *tree, string code = "")
{
	if (!tree)
		return;
	if (tree->c != '\0')
		cout << tree->c << " : " << code << endl;
	printHuffmanTree(tree->left, code + "0");
	printHuffmanTree(tree->right, code + "1");
}


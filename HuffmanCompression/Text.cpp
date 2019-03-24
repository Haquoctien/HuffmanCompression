#include "Text.h"



Text::Text()
{
	data = "";
}

Text::Text(const char * file)
{
	ifstream fileIn;
	fileIn.open(file, ios::in | ios::binary);
	if (fileIn.is_open() == false)
		cout << "File not open";
	char tempC;
	data = "";
	while (fileIn >> noskipws >> tempC)
	{
		data += tempC;
	}
	fileIn.close();
}

Text::~Text()
{
}

char bitSequenceToChar(string input)
{
	char c = 0;
	for (int i = 0; i < input.length(); i++)
	{
		c = (c << 1) | (input[i] - 48);
	}
	return c;
}

string bitStringToCharString(string input)
{
	string result = "";
	while (input.length() > 0)
	{
		string temp;
		if (input.length() > 8)
		{
			temp = input.substr(input.length() - 8, 8);
			input = input.erase(input.length() - 8, 8);
		}
		else
		{
			temp = input;
			if (temp.length() > 8) temp = "0" + temp;
			input = "";
		}
		result = bitSequenceToChar(temp) + result;
	}
	return result;
}
#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class Text
{
protected:
	string data;
public:
	Text();
	Text(const char* c);
	virtual ~Text();
	string getData() {
		return data;
	}
};

string bitStringToCharString(string input);
char bitSequenceToChar(string input);
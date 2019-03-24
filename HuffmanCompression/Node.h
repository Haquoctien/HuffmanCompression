#pragma once
#include <iostream>

struct Node {
	char c;
	int fre;
	Node *left, *right;
	Node();
	~Node();
	Node(char c, int fre)
	{
		left = right = NULL;
		this->c = c;
		this->fre = fre;
	}
};
bool compare(Node* a, Node* b);

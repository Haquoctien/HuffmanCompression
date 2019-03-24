#include "Node.h"



Node::Node()
{
	c = '\0';
	fre = -1;
	left = right = NULL;
}

Node::~Node() {}


bool compare(Node* a, Node* b)
{
	return (a->fre) < (b->fre);
}

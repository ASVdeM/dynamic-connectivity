#ifndef __NODE_H__
#define __NODE_H__
#include <stdbool.h>

typedef struct node *Node;
struct node {
	int value;
	Node leftChild;
	Node rightChild;
	Node parent;
	Node pathParent;
	bool bit;
	unsigned int size;
	bool isSplayTreeRoot;
};

Node makeNode ();
void setSplayTreeRoot (Node n);

#endif /* __NODE_H__ */

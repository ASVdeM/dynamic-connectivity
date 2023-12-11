#ifndef __NODE_H__
#define __NODE_H__

typedef struct node *Node;
struct node {
	int value;
	Node leftChild;
	Node rightChild;
	Node parent;
	Node pathParent;
	int bit;
	unsigned int size;
	int isSplayTreeRoot;
};

Node makeNode ();
void setSplayTreeRoot (Node n);

#endif /* __NODE_H__ */

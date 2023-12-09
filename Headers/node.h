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
};
Node makeNode();

#endif /* __NODE_H__ */

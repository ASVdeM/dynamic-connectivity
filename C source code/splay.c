#include <stdlib.h>
#include "splay.h"

// v becomes the right child of w
void join (Node v, Node w) {
	v->rightChild = w;
	w->parent = v;
	v->size += w->size;
}


static void pushBitDown (Node x) {
	if (x == NULL) return;
	if (x->bit == 1) {
		//swap children
		Node aux = x->leftChild;
		x->leftChild = x->rightChild;
		x->rightChild = aux;
		
		x->bit = 0;
			Node cLeft = x->leftChild;
		if (cLeft != NULL) {
			cLeft->bit = 1 - cLeft->bit;
		}
			Node cRight = x->rightChild;
		if (cRight != NULL) {
			cRight->bit = 1 - cRight->bit;
		}
	}
}

static void rotate (Node x) {
	Node father = x->parent;
	Node grandfather = father->parent;
	int sizeChild = 0;
	x->pathParent = father->pathParent;
	father->pathParent = NULL;
	if (father->leftChild == x) {
		father->leftChild = x->rightChild;
		if (x->rightChild != NULL) {
			x->rightChild->parent = father;
			sizeChild = x->rightChild->size;
		}
		x->rightChild = father;
	}
	else {
		father->rightChild = x->leftChild;
		if (x->leftChild != NULL) {
			x->leftChild->parent = father;
			sizeChild = x->leftChild->size;
		}
		x->leftChild = father;
	}
	x->bit = father->bit;
	father->bit = 0;
	father->parent = x;
	x->parent = grandfather;
	if (grandfather != NULL) {
		if (father == grandfather->leftChild) grandfather->leftChild = x;
		else grandfather->rightChild = x;
	}
	father->size = father->size - x->size + sizeChild;
	x->size = x->size - sizeChild + father->size; 
}

//creates a splay tree with x being its root
void splay (Node x) {
	while (x->parent != NULL) {
		Node father = x->parent;
			if (father->parent == NULL) {
			pushBitDown (father);
			pushBitDown (x);
			rotate (x);
		} else {
			Node grandfather = father->parent;
			// Order matters here
			pushBitDown (grandfather);
			pushBitDown (father);
			pushBitDown (x);
			// Zig-Zig ou Zag-Zag
			if (( father == grandfather->leftChild && x == father->leftChild ) ||
			( father == grandfather->rightChild && x == father->rightChild )) {
				rotate (father);
				rotate (x);
			}
			// Zig-Zag ou Zag-Zig
			else {
				rotate (x);
				rotate (x);
			}
		}
	}
	//ensure that x->bit == 0
	pushBitDown (x);
	setSplayTreeRoot (x);
}

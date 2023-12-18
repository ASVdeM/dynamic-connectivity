#include <stdio.h>
#include <stdlib.h>
#include "splay.h"

// v becomes the right child of w
void joinSplay (Node v, Node w) {
	v->rightChild = w;
	w->parent = v;
	v->size += w->size;
}

static bool flipBit (bool b){
	return 1 - b;
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
			cLeft->bit = flipBit (cLeft->bit);
		}
			Node cRight = x->rightChild;
		if (cRight != NULL) {
			cRight->bit = flipBit (cRight->bit);
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
void createSplay (Node x) {
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

void reflectSplay (Node v){
	v->bit = flipBit (v->bit);
	pushBitDown(v);
}

static Node selectChild (Node n){
	if (n->bit == false)
		return n->rightChild;
	else
		return n->leftChild;
	}

static Node maximum(Node x) {
	if (x == NULL) {
		fprintf (stderr, "You have passed a null pointer to the maximum function!\n");
		exit (EXIT_FAILURE);
	}
	//if there is a true bit in the subtrees, it needs to be pushed down in order to know how to proceed
	pushBitDown (x);
	
	if (selectChild (x) == NULL)
		return x;
		
	return maximum (selectChild (x));
}

Node maxSplay(Node x) {
	Node m = maximum (x);
	createSplay (m);
	return m;
}

void splitSplay (Node x) {
	if (x->bit==1){
		fprintf (stderr, "splitSplay error: the bit had value 1.\n");
	}
	
	Node greaterThanX = selectChild (x);
	
	if (greaterThanX != NULL) {
		greaterThanX->parent = NULL;
		x->size = x->size - greaterThanX->size;
		greaterThanX->bit ^= x->bit;
	}
	if (x->bit == false)
		x->rightChild = NULL;
	else
		x->leftChild = NULL;
}

static Node minimum(Node x) {
	//if there is a true bit in the subtrees, it needs to be pushed down in order to know how to proceed
	pushBitDown (x);
	if (selectChild (x) == NULL) return x;
	return minimum (selectChild (x));
}

Node minSplay(Node x) {
	Node m = minimum (x);
	createSplay (m);
	return m;
}

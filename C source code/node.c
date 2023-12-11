#include <stdlib.h>
#include "node.h"
#include "mallocSafe.h"

static int assignValue (){
	static int value = 0;
	value++;
	return value;
}

Node makeNode(){
	Node p = mallocSafe (sizeof (*p));
	p->value = assignValue ();
	p->rightChild = NULL;
	p->leftChild = NULL;
	p->parent = NULL;
	p->pathParent = NULL;
	p->bit = 1;
	p->size = 0;
	p->isSplayTreeRoot = 0;
	return p;
}

void setSplayTreeRoot (Node n){
	n->isSplayTreeRoot = 1;
}

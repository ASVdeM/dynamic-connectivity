#include <stdio.h>
#include "mallocSafe.h"
#include "dynamicForest.h"
#include "splay.h"

//creates an unconnected dynamic forest
Node *makeDynamicForest (int n){
	Node *dynamicForest = mallocSafe (n*sizeof(Node));

	for (int x = 0; x < n; x += 1){
		dynamicForest[x] = makeNode ();
	}
	return dynamicForest;
}

//Accesses the node v, creating the preferred path from the LCT root to the node v.
//By the end of the function, v is the root of its Splay Tree.
//In other words, v.rightChild == NULL because v is the node whose value is the greatest in the Splay,
//and so, it is the node with the biggest depth in the LCT.
static void accessNode (Node v) {
	Node w;
	createSplay (v);
	if (v->rightChild != NULL) {
		v->rightChild->pathParent = v;
		v->rightChild->parent = NULL;
	}
	v->rightChild = NULL;
	while (v->pathParent != NULL) {
		w = v->pathParent;
		createSplay (w);
		
		if (w->rightChild != NULL) {
			w->rightChild->pathParent = w;
			w->rightChild->parent = NULL;
		}
		
		joinSplay (w, v);
		v->pathParent = NULL;
		createSplay (v);
	}
}

static void evert (Node v) {
	accessNode (v);
	reflectSplay (v);
}

//adds an edge going from i to j
void addEdge (Node *dynamicForest, int i, int j){
	if (dynamicForest == NULL){
		fprintf (stderr, "addEdge error: You have called this function with a null pointer!\n");
		return;
	}
	evert (dynamicForest[i]);

	accessNode (dynamicForest[i]);
	accessNode (dynamicForest[j]);
	// i becomes the right child of j
	joinSplay (dynamicForest[i], dynamicForest[j]);
}

//adds the edge going from i to j
void deleteEdge (Node *dynamicForest, int i, int j) {
	evert (dynamicForest[i]);
	accessNode(dynamicForest[j]);

	if (dynamicForest[j]->leftChild == NULL) {
		fprintf (stderr, "deleteEdge error: dynamicForest[%d]->leftChild is NULL!\n", j);
		exit (EXIT_FAILURE);
	}
	splitSplay (maxSplay (dynamicForest[j]->leftChild));
}

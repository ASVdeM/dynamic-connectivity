#include "node.h"
#include "mallocSafe.h"

Node *makeDynamicForest (int n){
	Node *dynamicForest = mallocSafe (n*sizeof(Node));

	for (int x = 0; x < n; x += 1){
		dynamicForest[x] = makeNode ();
	}
	return dynamicForest;
}

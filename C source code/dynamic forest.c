#include "node.h"
#include "mallocSafe.h"

Node *makeDynamicForest (int n){
	Node *nodeList = mallocSafe (n*sizeof(Node));

	for (int x = 0; x < n; x += 1){
		nodeList[x] = makeNode ();
	}
	return nodeList;
}

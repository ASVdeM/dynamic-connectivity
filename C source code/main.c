#include <stdlib.h>
#include <stdio.h>
#include "dynamicForest.h"

int main (int argc, char *argv[]) {
	int n;
	if (argc == 2)
		n = atoi (argv[1]);
	else {
		puts ("Please type the number of nodes that you want in your dynamic forest.");
		printf ("You can also pass this on the command line, like this: %s <number of nodes>\n", argv[0]);
		char numberBuffer[10];
		if (fgets (numberBuffer, sizeof (numberBuffer), stdin) == NULL){
			perror ("fgets error");
		}
		n = atoi (numberBuffer);
	}
	Node *dynamicForest = makeDynamicForest (n);
	if (n > 1){
		puts ("The nodes will now be connected randomly.");
		for (int x = rand () % n; x > 0; x--){
			addEdge (dynamicForest, rand () % n, rand () % n);
		}
	}
	return 0;
}

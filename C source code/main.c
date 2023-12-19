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
	for (int x = 0; x < n; x += 1){
		for (int y = x; y < n; y += 1){
			printf ("%d and %d are ", x, y);
			if (connected (dynamicForest, x, y) == false)
				printf ("not ");
			puts ("connected");
		}
	}
	for (int x = 0; x < n; x += 1){
		printf ("size of %d: %u\n", x, size (dynamicForest, x));
	}
	
	return 0;
}

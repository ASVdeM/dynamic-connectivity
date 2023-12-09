#include <stdlib.h>
#include <stdio.h>
#include "mallocSafe.h"

void *mallocSafe(size_t nbytes) {
	void *p = malloc(nbytes);
	if (p == NULL) {
		fprintf(stderr, "Erro: alocação de memória falhou no módulo node.\n");
		exit(EXIT_FAILURE);
	}
	return p;
}

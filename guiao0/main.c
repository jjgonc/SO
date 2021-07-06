#include "vector.h"
#include <stdlib.h>
#include <stdio.h>

int vector_global[5] = {0,1,2,3,4}; // global

int main(){
	int i;
	int *vector_automatic  = malloc (sizeof(int) * 5); //vetor automatico
	fill (vector_automatic, 5, 5);

	int vector_dynamic[5]; //vetor dinamico
	for (i=0; i != 5; i++) {
		vector_dynamic[i] = 1;
	}

	find (vector_dynamic, 5, 1);
	
	return 0;
}


/*
QUESTAO 3:
Para fazer a pesquisa neste segmento passava como argumento vetor+1000 e dava como size 1000, para que andasse apenas 1000 elementos apos o indice que passei como inicial

QUESTAO 4:
Na funçao fill faz .... e na funçao find acontece que ....

*/
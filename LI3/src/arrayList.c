#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arrayList.h"

void initArrayList (HEAD_LIST h, int initial_size) {

	h = (HEAD_LIST) malloc (sizeof(struct elementos) * initial_size);
	h->sp   = (int*) malloc(sizeof(int));
	h->size = (int*) malloc(sizeof(int));

	int i;
	for (i = 0; i < initial_size; i++)
		h->content[i] = NULL;

	*(h -> sp) = 0;
	*(h -> size) = initial_size;	
}

int isEmptyArrayList (HEAD_LIST h) {	
	return *(h->sp) == 0;
}

void pushArrayList (HEAD_LIST h, char *new_entry, int filial, int new_quant) {
	
/*	if (*(h -> sp) == *(h -> size))
		doubleArrayList(h);
*/
	h -> content[*(h->sp)] -> total_quant = (int*) malloc(sizeof(int) * 3);
	h -> content[*(h->sp)] -> total_client = (int*) malloc(sizeof(int) * 3);
	
	h -> content[*(h->sp)] -> entry = strdup(new_entry);
	h -> content[*(h->sp)] -> total_quant[filial] = new_quant;
	h -> content[*(h->sp)++] -> total_client[filial]++;
}

void doubleArrayList (HEAD_LIST h) {
	*(h -> size) *= 2;
	h -> content = realloc (h -> content, *(h -> size));
}

void freeArrayList (HEAD_LIST h) {
	int i;
	for (i = 0; i < *(h->sp); i++)
		free(h->content[i]->entry);
	free(h->content);
	free(h);
}

void printArray (int *array) {
	int i;
	for (i = 0; i < 3; i++)
		printf("%d |", array[i]);
	printf("\n");
}

void printArrayList (HEAD_LIST h) {
	int i;
	for (i = 0; i < *(h->sp); i++) {
		printf("%s\n", h->content[i]->entry);
		printArray(h->content[i]->total_client);
		printArray(h->content[i]->total_quant);
	}
}
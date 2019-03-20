#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arrayList.h"

void initArrayList (HEAD_LIST h, int initial_size) {

	h->sp = 0;
	h->size = initial_size;	
}

int isEmptyArrayList (HEAD_LIST h) {	
	return (h->sp == 0);
}

int find_pos (char *entry, HEAD_LIST h) {

	int i, pos = -1;

	for (i = 0; i < h -> sp; i++)
		if (!strcmp(entry, h -> content[i].entry)) {
			pos = i; break;
		}

	return pos;
}

void pushArrayList (HEAD_LIST h, char *new_entry, int filial, int new_quant) {

	int pos = find_pos(new_entry, h);

	if (pos >= 0) {
		h -> content[pos].total_quant[filial] = new_quant;
		h -> content[pos].total_client[filial]++;
	} else if (pos == -1) {
		h -> content[h->sp].entry = strdup(new_entry);
		h -> content[h->sp].total_quant[filial] = new_quant;
		h -> content[h->sp].total_client[filial]++;		
		h->sp++;
	} else 
		if (h->sp == h->size) 
			printf("\nMAX SIZE REACHED!\n");
}

void doubleArrayList (HEAD_LIST h) {

	h->size *= 2;
	h -> content = realloc (h -> content, h->size);

}

void freeArrayList (HEAD_LIST h) {
	int i;
	for (i = 0; i < h->sp; i++)
		free(h->content[i].entry);
	free(h->content);
	free(h);
}

void printArray (int *array) {
	int i;
	for (i = 0; i < 3; i++)
		printf("%d|", array[i]);
	printf(" ");
}

void printArrayList (HEAD_LIST h) {
	int i;
	for (i = 0; i < h->sp; i++) {
		printf("prod=%s ", h->content[i].entry);
		printf("\tQT_CLIENT: ");
		printArray(h->content[i].total_client);
		printf(" \tQT_COMPR: ");
		printArray(h->content[i].total_quant);
		printf("\n");
	}
}
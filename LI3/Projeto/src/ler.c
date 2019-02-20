#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ler.h"

void print_struct (TableProd t, int counter) {

	int i=0;
	while (i<counter) {
		printf("%s", t[i].products);
		i++;
	}

}

int read_products (char *filename, TableProd t) {

	FILE *fp = fopen(filename, "r");
	int counter = 0;
	char *buffer = (char*) malloc(sizeof(char)*SIZE);
	int i=0;
	while (!feof(fp)) {
		fgets(buffer, SIZE, fp);
		t[i].products = strdup(buffer);
		i++;
		counter++;
	}

	free(buffer);
	fclose(fp);

	return counter;
}
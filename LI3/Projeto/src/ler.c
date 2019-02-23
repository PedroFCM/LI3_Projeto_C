#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "ler.h"

int verify_product (char *product) {

	char *aux = strdup(product);

	int numb = atoi (aux+2);
	if (strlen(aux) == 8)
		if (numb >= 1000 && numb <= 9999)
			if (isupper(aux[0]) && isupper(aux[1]) &&
				isdigit(aux[2]) && isdigit(aux[3]) &&
				isdigit(aux[4]) && isdigit(aux[5]))
					return 1;
				else return 0;
		else return 0;
	else return 0;
}

void readNvalidate_products (char* filename, char *produtos[], FILE_SETTINGS *set) {

	FILE *fp = fopen(filename, "r");
	char *buffer = (char*) malloc(sizeof(char)*64);
	int validos = 0, i=0;

	while (fgets(buffer, 64, fp)) {
		if (verify_product(buffer)) {
			produtos[validos] = strdup(buffer);
			validos++;
		} else set->nulo = i+1;
		i++;
	}
	
	free(buffer);

	set->num_prods = i;
	set->prods_val = validos;
}

void print_products (char *produtos[], FILE_SETTINGS *set) {

	int i=0, size = set->prods_val;
	
	while (i < size) {
		printf("%s", produtos[i]);
		i++;
	}

	printf("\nNº de readed lines: %d\n",        set->num_prods);
	printf("Nº of valid products (printed): %d\n", set->prods_val);
	printf("Linha invalida: %d\n", set->nulo);
	
}

void write_products_on_file (char *produtos[], FILE_SETTINGS *set) {

	FILE *fp = fopen("validData/Produtos(validados).txt", "w");
	int i = 0, size = set->prods_val;

	while (i<size) {
		fprintf(fp, "%s", produtos[i]);
		i++;
	}

}
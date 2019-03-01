#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "produtos_read_write.h"
#include "global.h"
#include "avlstruct.h"

int verify_product (char *product) {

	char *aux = strdup(product);

	int r = 0, num_prod = atoi(aux+2);
	if (num_prod >= 1000 && num_prod <= 9999)
		if (isupper(aux[0]) && isupper(aux[1]) &&
				isdigit(aux[2]) && isdigit(aux[3]) &&
				isdigit(aux[4]) && isdigit(aux[5]) &&
				!isdigit(aux[6])) r = 1;
	
	return r;
}

AVL* readNvalidate_products (char* filename, AVL *prod, GLOBAL *set) {

	FILE *fp = fopen(filename, "r");

	int max_size_line = biggest_line_in_file(filename);
	int validos = 0, i = 0;


	char *buffer = (char*) malloc(sizeof(char) * max_size_line);
			
	while (fgets(buffer, max_size_line, fp)) {
		
		if (verify_product(buffer)) {
			
			prod = updateAVL(prod, buffer);
			
			validos++;
		}
	
		i++;
	}

	free(buffer);

	set -> num_prods      = i;
	set -> val_prods      = validos;
	set -> max_line_prods = max_size_line;

	return prod;
}

void write_products_on_file (char **produtos, GLOBAL *set) {

	FILE *fp = fopen(VAL_PROD_PATH, "w");

	int i = 0, size = set -> val_prods;

	while (i<size) {
	
		fprintf(fp, "%s", produtos[i]);
	
		i++;
	}
}

int preorder_avl (AVL *a) {

	int i = 0;

	if (a != NULL) {
		i++;
		printf("%s", a -> tag);
		
		i+=preorder_avl(a -> left);
		i+=preorder_avl(a -> right);
	}

	return i;
}
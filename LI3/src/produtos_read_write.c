#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "produtos_read_write.h"
#include "global.h"
#include "avlstruct.h"

int verify_product (char *product) {

	char *aux = strndup(product, 6);

	int r = 0, num_prod = atoi(aux+2);

	if (num_prod >= 1000 && num_prod <= 9999)
		if (isupper(aux[0]) && isupper(aux[1]) &&
				isdigit(aux[2]) && isdigit(aux[3]) &&
				isdigit(aux[4]) && isdigit(aux[5]) &&
				!isdigit(aux[7]) && !isupper(aux[7])) r = 1;
	
	return r;
}

AVL* readNvalidate_products (char* filename, AVL *prod, GLOBAL *set) {

	FILE *fp = fopen(filename, "r");

	int max = biggest_line_in_file(filename);
	int validos = 0, i = 0;

	char *buffer = (char*) malloc(sizeof(char) * (max+10));
			
	while (fgets(buffer, max, fp)) {
		
		if (verify_product(buffer)) {
			
			prod = updateAVL(prod, buffer);
			
			validos++;
		}
	
		i++;
	}

	free(buffer);

	set -> num_prods      = i;
	set -> val_prods      = validos;
	set -> max_line_prods = max;

	fclose(fp);

	return prod;
}
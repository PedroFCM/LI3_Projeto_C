#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>

#include "produtos_read_write.h"
#include "global.h"
#include "avlstruct.h"

int verify_product (char *product) {

	int r = 0;
	int num_prod = atoi(product+2);

	r = (num_prod >= 1000) && (num_prod <= 9999); 

	r = r && (is_uppercase(product[0]) && is_uppercase(product[1]) &&
			  is_number(product[2])    && is_number(product[3]) &&
			  is_number(product[4])    && is_number(product[5]) &&
		     !is_number(product[6])    && !is_uppercase(product[6]));
	
	return r;
}

AVL readNvalidate_products (char* filename, AVL prod, GLOBAL set) {

	FILE *fp = fopen(filename, "r");

	int max = biggest_line_in_file(filename);
	
	set -> num_prods = 0;
	set -> val_prods = 0;
	set -> max_line_prods = max;

	char *buffer = (char*) malloc(sizeof(char) * (2 * max));
			
	while (fgets(buffer, max, fp)) {
		
		if (verify_product(buffer)) {
			
			prod = updateAVL(prod, buffer);
			
			set -> val_prods++;
		}
	
		set -> num_prods++;
	}

	free(buffer);

	fclose(fp);

	return prod;
}
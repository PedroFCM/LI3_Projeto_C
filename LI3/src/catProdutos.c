
/** @file catProdutos.c
*	@brief Ficheiro que cria o catálogo de Produtos validados.
*
*	@autor João Pedro Rodrigues Azevedo (A85227) 
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@bug Nenhum que tivessemos reparado.
*	
*/

/*MACRO para suprimir warnings de strdup do <string.h>*/
#define _GNU_SOURCE

/*_________________BIBLIOTECAS STD IMPORTADAS________________________*/

#include <stdio.h>
#include <stdlib.h>

/*_________________BIBLIOTECAS IMPLEMENTADAS____________________________*/


#include "catProdutos.h"
#include "global.h"
#include "avlstruct.h"

/*______________________________________________________________________*/


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
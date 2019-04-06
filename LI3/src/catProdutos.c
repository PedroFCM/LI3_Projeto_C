
/** @file catProdutos.c 
*	@brief Ficheiro que cria o catálogo de Produtos validados.
*          Efetua também operações básicas sobre os mesmos.
*
*	@autor João Pedro Rodrigues Azevedo
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@bug Nenhum.
*	
*/

/** Macro para suprimir warnings de strdup do <string.h> */
#define _GNU_SOURCE

/*----------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*----------------------------------------------------------------------*/

#include "catProdutos.h"
#include "global.h"
#include "avlstruct.h"
#include "menu.h"

/*----------------------------------------------------------------------*/

/**
* Struct para representar uma lista de elementos (Produtos no caso implementado).
* Usada para guardar as paginas a apresentar ao utilizador.
* Pode ser entendida com o catálogo de produtos com uma dada letra.
*/
struct listaProdutos {
	/*@{*/
	int size; /**< Tamanho da lista de elementos. */
	char **elements; /**< Lista de strings. */
	int ocurr; /**< Nº de ocurrencias de um elemento. */
	int sp; /**< Index do ultimo elemento adicionado. */
	/*@}*/
};

/*----------------------------------------------------------------------*/

int verify_product (PRODUTO product) {

	int r = 0;
	int num_prod = atoi(product+2);

	r = (num_prod >= 1000) && (num_prod <= 9999); 

	r = r && (is_uppercase(product[0]) && is_uppercase(product[1]) &&
			  is_number(product[2])    && is_number(product[3]) &&
			  is_number(product[4])    && is_number(product[5]) &&
		     !is_number(product[6])    && !is_uppercase(product[6]));
	
	return r;
}

CAT_PRODUTOS readNvalidate_products (char* filename, CAT_PRODUTOS prod, GLOBAL set) {

	FILE *fp = fopen(filename, "r");

	int max = biggest_line_in_file(filename);

	set -> num_prods = 0;
	set -> val_prods = 0;
	set -> max_line_prods = max;

	char *buffer = (char*) malloc(sizeof(char) * (2 * max));
			
	while (fgets(buffer, max, fp)) {
		
		if (verify_product(buffer)) {
			
			prod = updateAVL(prod, NULL, NULL, NULL, buffer, 0);
			
			set -> val_prods++;
		}

		set -> num_prods++;
	}

	free(buffer);

	fclose(fp);

	return prod;
}

/*----------------------------------------------------------------------*/

LISTA_PROD geraListaLetra (AVL produtos, LISTA_PROD ls, char letra) {

	if (produtos != NULL) {
		
		if (letra == getFirstLetterTag(produtos)) {

			ls = addProduto(ls, getTag(produtos)); 
			
			ls = geraListaLetra(getDir(produtos), ls, letra);
			ls = geraListaLetra(getEsq(produtos), ls, letra); 
			
		}
		
		else
		{
			if (letra < getFirstLetterTag(produtos))
				ls = geraListaLetra(getEsq(produtos), ls, letra);			
		
			else
				ls = geraListaLetra(getDir(produtos), ls, letra);
		}
	}

	return ls;
}

int getCurrentSize (LISTA_PROD s) {
	return s->sp;
}

char* getElementList(LISTA_PROD s, int pos) {
	return s -> elements[pos];
}

int getSPList (LISTA_PROD s) {
	return s -> sp;
}

void duplicateList (LISTA_PROD s) {
	s -> size *= 2;
	s -> elements = realloc (s -> elements, s->size);
}

void freeList (LISTA_PROD s) {
	int i;
	for (i = 0; i < s->sp; i++)
		free(s->elements[i]);

	free(s);
}

LISTA_PROD addProduto (LISTA_PROD l, char *new_produto) {

	if (l -> sp == l -> size)
		duplicateList(l);

	l -> elements[l->sp++] = strdup(new_produto);

	return l;
}

int isEmptyLista (LISTA_PROD s) {
	return s->sp==0;
}

LISTA_PROD initLista (LISTA_PROD s, int tamanho_inicial) {

	s = (LISTA_PROD) malloc (sizeof(struct listaProdutos));
	s -> elements = (char**) malloc(sizeof(char*) * tamanho_inicial);
	s -> size = tamanho_inicial;
	s -> sp = 0;

	return s;
}

/*----------------------------------------------------------------------*/

/** @file queries.c
*	@brief Ficheiro que implenta as 12 querys em causa.
*
*	@autor João Pedro Rodrigues Azevedo (A85227) 
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@bug Nenhum que tivessemos reparado.
*	
*/

/*______________________________________________________________________*/

/*MACRO para suprimir warnings de strdup do <string.h>*/
#define _GNU_SOURCE

/*_________________BIBLIOTECAS STD IMPORTADAS________________________*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*_________________BIBLIOTECAS IMPLEMENTADAS____________________________*/

#include "avlstruct.h"
#include "global.h"
#include "catProdutos.h"
#include "Faturacao.h"
#include "Filial.h"

/*-----------------------------------------------------------------------*/

void query1 (GLOBAL set) {

	printf("\n*****************************************");

	printf("\nNúmero de produtos validados   : %d.\n", set->val_prods);
	printf("Número de clientes validados   : %d.\n" , set->val_clients);
	printf("Vendas válidas                 : %d.\n", set->val_sells);
	
	printf("\nOutros:\n");
	printf("\nLinha mais longa venda         : %d\n", set->max_line_sells);
	printf("Número de produtos inválidos   : %d\n", set->num_prods-set->val_prods);
	printf("Número de clientes inválidos   : %d\n", set->num_clients-set->val_clients);
	printf("Número de vendas   inválidas   : %d\n\n", set->num_sells-set->val_sells);

	printf("*****************************************\n");
}

/*-----------------------------------------------------------------------*/

LISTA_PROD query2 (LISTA_PROD ls, AVL produtos, char c) {

	ls = geraListaLetra (produtos, ls, c);

	return ls;
}


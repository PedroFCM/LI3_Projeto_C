/**
*	@mainpage LI3_PROJETO GRUPO 58
*	
*	@autor João Pedro Rodrigues Azevedo (A85227) 
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@file main.c
*	@brief Função principal que carrega todo o sistema SGV.
*	@bug Nenhum que tivessemos reparado.
*
*/

/*MACRO para suprimir warnings de strdup do <string.h>*/
#define _GNU_SOURCE

/*_________________BIBLIOTECAS STD IMPORTADAS________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*_________________BIBLIOTECAS IMPLEMENTADAS____________________________*/

#include "global.h"
#include "catProdutos.h"
#include "catClientes.h"
#include "catVendas.h"
#include "avlstruct.h"
#include "queries.h"
#include "menu.h"
#include "Faturacao.h"
#include "Filial.h"

/**
* @brief Função que carrega o SGV.
* 
* Mostra o menu do sistema e permite a navegação num
* conjunto determinado de funcionalidades. Opera sobre
* estruturas como AVL's...
*
* @param void Nenhum.
*
* @returns Retorna 0 caso tudo corra bem.
*/

/*______________________________________________________________________*/

int main (void) {

	clock_t start, end;
	double cpu_time_used;


	GLOBAL set = (GLOBAL) malloc(sizeof(struct settings)); 

	CAT_PRODUTOS products = NULL;
	CAT_CLIENTES clients  = NULL;
	CAT_VENDAS   sells    = NULL;
	
	start = clock();
	
	products = readNvalidate_products(PROD_PATH, products, set);	
	clients = readNvalidate_clients(CLIE_PATH, clients, set);
	sells = readNvalidate_sells(SELL_PATH_1M, sells, set, products, clients);

	write_inorder_avl_on_file(VAL_CLIE_PATH, clients, set);
	write_inorder_avl_on_file(VAL_PROD_PATH, products, set);
	write_inorder_avl_on_file(VAL_SELL_PATH, sells, set);

	query1(set);

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	printf("\n\nCPU Time = %.4f seconds.\n\n", cpu_time_used );
	
	
		
/*	FAT_FILIAL nova = NULL;
	initFaturacao(nova, products, sells);
		
*/		
	FILIAL new = NULL;
	initFilial(new, clients, sells);
	
	free(set);

	return 0;
}
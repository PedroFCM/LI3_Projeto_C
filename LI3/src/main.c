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

#define _GNU_SOURCE


/*_________________BIBLIOTECAS STD IMPORTADAS________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*_________________BIBLIOTECAS IMPLEMENTADAS____________________________*/

#include "global.h"
#include "produtos_read_write.h"
#include "clientes_read_write.h"
#include "vendas_read_write.h"
#include "avlstruct.h"
#include "queries.h"

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

int main (void) {

	/*-------------------------CPU TIME------------------------------*/
	
	clock_t start, end;
	double cpu_time_used;
	start = clock();

	/*--------------------CRIAÇÃO DE ESTRUTURAS----------------------*/

	GLOBAL set = (GLOBAL) malloc(sizeof(struct settings)); 

	AVL products = NULL;
	AVL clients  = NULL;
	AVL sells    = NULL;

	/*--------------------LEITURA DE DADOS---------------------------*/
	
	products = readNvalidate_products(PROD_PATH, products, set);
	write_inorder_avl_on_file(VAL_PROD_PATH, products, set);
	
	clients = readNvalidate_clients(CLIE_PATH, clients, set);
	write_inorder_avl_on_file(VAL_CLIE_PATH, clients, set);
	
	sells = readNvalidate_sells(SELL_PATH, sells, set, products, clients);
	write_inorder_avl_on_file(VAL_SELL_PATH, sells, set);
	
	/*--------------------STATS DE LEITURA---------------------------*/

	show_stats_vendas(set);
	
	/*---------------------FREE DAS ESTRUTURAS-----------------------*/

	freeAVL(products);
	freeAVL(clients);
	freeAVL(sells);
	free(set);
		
	/*-------------------------CPU TIME------------------------------*/
	
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("\nCPU Time = %f\n\n", cpu_time_used );
	
	return 0;
}
/**
*	@mainpage LI3_PROJETO GRUPO 58
*	
*	@autor João Pedro Rodrigues Azevedo
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@file main.c
*	@brief Módulo principal que carrega todo o sistema SGV.
*	@bug Nenhum que tivessemos reparado.
*
*/

/*_________________BIBLIOTECAS IMPLEMENTADAS____________________________*/

/*@brief Include relativo ao controlador do SGV*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "global.h"
#include "catProdutos.h"
#include "catClientes.h"
#include "catVendas.h"
#include "avlstruct.h"
#include "queries.h"
#include "menu.h"
#include "Faturacao.h"
#include "Filial.h"
/*----------------------------------------------------------------------*/

/**
* @brief Função principal do programa (main).
* 
* Mostra o menu do sistema e permite a navegação num
* conjunto determinado de funcionalidades. Opera sobre
* estruturas como AVL's, hashtables, arrays, stacks e Linked Lists.
*
* @param void Nenhum.
*
* @returns Retorna 0 caso tudo corra bem.
*/

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

    FILIAL new = NULL;
    initFilial(new, clients, sells);

    free(set);

    return 0;

}

/*
int main (void) {

	FUNÇÃO RESPONSAVEL POR CARREGAR O SGV
	loadMenu();

	return 0;
}
*/
/*----------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "produtos_read_write.h"
#include "clientes_read_write.h"
#include "vendas_read_write.h"
#include "avlstruct.h"
#include "queries.h"
#include "menu.h"

int checkInput (int input, int selection) {
	return (input==1 && (selection>=1 || selection<=12));
}

void clear_screen() {
	if (system("clear")==-1);
}

void loadOption (int option) {
	
	clear_screen();

	/*---------------------------------------------------------------*/

	int option_selected = 0, data_loaded = 0, input;
	
	GLOBAL set = (GLOBAL) malloc(sizeof(struct settings)); 

	AVL products = NULL;
	AVL clients  = NULL;
	AVL sells    = NULL;
	
	/*---------------------------------------------------------------*/

	displayMenuAndOptions();

	input = scanf("%d", &option_selected);

	/*---------------------------------------------------------------*/
	if (checkInput(input, option_selected)) {
			
		switch(option_selected) {

			case 1: if (!data_loaded) {
						
				printf("\nA efetuar a leitura de dados...\n");
				
				products = readNvalidate_products(PROD_PATH, products, set);
				write_inorder_avl_on_file(VAL_PROD_PATH, products, set);
				
				clients = readNvalidate_clients(CLIE_PATH, clients, set);
				write_inorder_avl_on_file(VAL_CLIE_PATH, clients, set);
				
				sells = readNvalidate_sells(SELL_PATH, sells, set, products, clients);
				write_inorder_avl_on_file(VAL_SELL_PATH, sells, set);

				data_loaded = 1;
			
				clear_screen();

				displayMenuAndOptions();

				show_stats_vendas(set);
				
				loadOption(0);

				break;
			} else {
					freeAVL(products);
					freeAVL(clients);
					freeAVL(sells);
					free(set);
			}

			default: printf("Nao disponivel...\n"); break;
		}

	} else {
		printf("Nao disponivel...\n");
		loadOption(0);
	}
}

void displayMenuAndOptions () {

	printf("\n_____Sistema geral de Vendas [SGV]_____\n\n");

	printf("Opções disponivéis (Introduza o respetivo número):\n\n");

	printf("[1] Leitura dos ficheiros com os Produtos, Clientes e Vendas.\n");
	printf("[2] Lista de Produtos que se iniciam por uma letra maiúscula.\n");
	printf("[3] Número total de Vendas num mês e o total faturado (global ou por filial).\n");
	printf("[4] Lista de produtos que ninguém comprou (global ou por filial).\n");
	printf("[5] Lista de Clientes que realizaram compras em todas as filiais.\n");
	printf("etc...\n\n");
}

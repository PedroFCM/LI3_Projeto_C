
/** @file menu.c
*	@brief Ficheiro que implementa o menu do SGV.
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

#include "global.h"
#include "catProdutos.h"
#include "catClientes.h"
#include "catVendas.h"
#include "avlstruct.h"
#include "queries.h"
#include "menu.h"
#include "time.h"

/*______________________________________________________________________*/

int checkInput (int input, int selection) {
	return (input==1 && ( 
		(selection >= 'A' && selection <= 'Z') || 
		(selection >= 'a' && selection <= 'z') ||
		(selection >= '0' && selection <= '9')));
}

void clear_screen() {
	if (system("clear")==-1);
}

void showTime (double time) {
	printf("\n\n(Carregados em %.4f segundos)\n\n", time);
}

void displayMenuAndOptions (int loaded) {

	clear_screen();


	printf("\n\t\t\t -- Sistema geral de Vendas [SGV] --\n");

	if (loaded == 1) 
		printf("\n\t\t\t\t\t\t\t\t\t[DADOS CARREGADOS]\n\n");
	else 
		printf("\n\t\t\t\t\t\t\t\t\t[DADOS NÃO CARREGADOS]\n\n");

	printf("Opções disponivéis (Introduza o respetivo número):\n\n");

	printf("[1]  Leitura dos ficheiros com os Produtos, Clientes e Vendas.\n");
	printf("[2]  Lista de Produtos que se iniciam por uma letra maiúscula.\n");
	printf("[3]  Nº total de Vendas num mês e o total faturado (global ou por filial).\n");
/*	printf("[4]  Lista de produtos que ninguém comprou (global ou por filial).\n");
	printf("[5]  Lista de Clientes que realizaram compras em todas as filiais.\n");
	printf("[6]  Nº de clientes registados que não realizaram compras e o nº de produtos que ninguém comprou\n");
	printf("[7]  Tabela de todos os produtos comprados mês a mês, organizada por filial.\n");
*/	printf("[8]  Nº total de vendas num intervalo de meses (p.ex. [1..3]) e total faturado.\n");
	printf("[9]  Dado um código de Produto e uma filial apresentar os códigos (e o Nº total),\n");
	printf("     dos clientes que o compraram (distinguindo N e P)\n");
	printf("[10] Dado um Cliente e um mês determinar a lista de códigos que mais comprou por quantidade, \nordem descendente.\n");
	printf("[11] Lista dos N produtos mais vendidos no ano, indicando o nº total de clientes e nº de unidades vendidas, filial a filial.\n");
	printf("[12] Dado um Cliente indica quais os códigos dos 3 produtos em que mais gastou dinheiro.\n");
}

void displayFicheirosLeitura() {
	printf("\n-> Qual ficheiro deseja ler?\n\n");
	
	printf("\t[1] Vendas_1M.txt\n");
	printf("\t[2] Vendas_3M.txt\n");
	printf("\t[3] Vendas_5M.txt\n");
}

void loadOption () {
	
	clear_screen();

	/*---------------------------------------------------------------*/
	
	clock_t start, end;
	double cpu_time_used;
					
	char option_selected = 0, data_loaded = 0, input;
	int mes;
	int argumentoInteiro;
	
	GLOBAL set = (GLOBAL) malloc(sizeof(struct settings)); 

	CAT_PRODUTOS products = NULL;
	CAT_CLIENTES clients  = NULL;
	CAT_VENDAS   sells    = NULL;
	
	/*---------------------------------------------------------------*/

	displayMenuAndOptions(data_loaded);

	input = scanf("%c", &option_selected);
	if (!checkInput(input, option_selected))
		option_selected = '0';

	/*---------------------------------------------------------------*/

	while (option_selected != 'q' && option_selected != 'Q' && option_selected != 'y') {

		switch(option_selected) {

			/*---------------------------------------------------------------*/

			case 'x' : 
					displayMenuAndOptions(data_loaded);
				break;

			case 'X' : 
					displayMenuAndOptions(data_loaded);
				break;

			/*---------------------------------------------------------------*/

			case '1': 

				if (!data_loaded) {
				
					displayFicheirosLeitura();

					while (1) {  
						
						if (scanf("%d", &argumentoInteiro)!=-1) {

							if (argumentoInteiro == 1 || 
								argumentoInteiro == 2 || 
								argumentoInteiro == 3) {

								printf("\nA ler Vendas_%dM.txt ...\n", argumentoInteiro);
								printf("\n\n->A efetuar a leitura de dados...\n");
								
								start = clock();

								products = readNvalidate_products(PROD_PATH, products, set);
								clients = readNvalidate_clients(CLIE_PATH, clients, set);
						
								switch (argumentoInteiro) {
									case 1: 
										sells = readNvalidate_sells(SELL_PATH_1M, sells, set, products, clients);
										break;
									case 2:
										sells = readNvalidate_sells(SELL_PATH_3M, sells, set, products, clients);
										break;
									case 3:
										sells = readNvalidate_sells(SELL_PATH_5M, sells, set, products, clients);
										break;
								}
					
								write_inorder_avl_on_file(VAL_CLIE_PATH, clients, set);
								write_inorder_avl_on_file(VAL_PROD_PATH, products, set);
								write_inorder_avl_on_file(VAL_SELL_PATH, sells, set);

								end = clock();
								cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
								
								query1(set);

								data_loaded = 1;
			
								printf("\nDados Carregados e guardados no folder validData/.");
								showTime(cpu_time_used);

								printf("\n\t[VOLTAR AO MENU INICIAL (Pressionar X + ENTER)]\n");

								break;
					
					} else printf("[ERRO] Escolha uma opcção válida por favor...\n");

				} else printf("[ERRO] Escolha uma opcção válida por favor...\n");

				} 
				} else {
					printf("Os dados já foram carregados, por favor escolha outra opcção.\n");
					printf("Carregar novos dados? [y]\n");
				}

				break;

			/*---------------------------------------------------------------*/

			case '2': 
					if (!data_loaded) 
						printf("Carregue os dados para o programa primeiro, por favor.\n");
					else {
						printf("Escolha uma letra (Maiúscula): ");
						while (1) {
							char letra;
							if (scanf("%c", &letra) == 1) 
								if (letra >= 'A' && letra <='Z') {
									query2(products, letra);
									printf("\n\t[VOLTAR AO MENU INICIAL (Pressionar X + ENTER)]\n");
									break;
								}
						}
					}
					break;

			/*---------------------------------------------------------------*/

			case '3':
					if (!data_loaded) 
						printf("Carregue os dados para o programa primeiro, por favor.\n");
					else {
						printf("Insira um mês: ");
						while (1)
							if (scanf("%d", &mes))
								break;
						char *codprod = (char*) malloc(sizeof(char)*10);
						int opcao_mostragem;
						printf("Insira um código de Produto: ");
						while(1) {
							if (scanf("%s", codprod))
								if (mes >= 1 && mes <= 12) {
									printf("Deseja o resultado por filial ou o Total?\n");
									printf("(0: FILIAL | 1: TOTAL)");
									while (1) {
										if (scanf("%d", &opcao_mostragem)) {
											if (opcao_mostragem == 0 || opcao_mostragem == 1) {
												query3(sells, mes, codprod, opcao_mostragem);
												printf("\n\t[VOLTAR AO MENU INICIAL (Pressionar X + ENTER)]\n");
												free(codprod);
												break;
											}
										}
									}
									break; 
								}
						}
					}

					break;

			/*---------------------------------------------------------------*/

			case '4': 
					if (!data_loaded)
						printf("Carregue os dados para o programa primeiro, por favor.\n");
					else {
						printf("\n[error 404] query not found\n");
					}
					break;

			case '5': 
					if (!data_loaded)
						printf("Carregue os dados para o programa primeiro, por favor.\n");
					else {
						printf("\n[error 404] query not found\n");
					}

			case '6': 
					if (!data_loaded)
						printf("Carregue os dados para o programa primeiro, por favor.\n");
					else {
						printf("\n[error 404] query not found\n");
					}
			case '7': 
					if (!data_loaded)
						printf("Carregue os dados para o programa primeiro, por favor.\n");
					else {
						printf("\n[error 404] query not found\n");
					}

			case '8': 
					if (!data_loaded)
						printf("Carregue os dados para o programa primeiro, por favor.\n");
					else {
				
						printf("\nInsira um intervalo de meses:\n");
						printf("(Exemplo o intervalo [1..3] ficaria > 1..3)\n");
						int mes_inf, mes_sup;
						while (1) {
							if (scanf("%d..%d", &mes_inf, &mes_sup))
								if ((mes_inf <= mes_sup || mes_sup <= mes_inf) &&
									mes_inf >= 1 && mes_inf <= 12 &&
									mes_sup >= 1 && mes_sup <= 12) {
										query8(mes_inf, mes_sup, sells);
										break;
								}
						}
					}

			case '9': 
					if (!data_loaded)
						printf("Carregue os dados para o programa primeiro, por favor.\n");
					else {

						char *codprod = (char*) malloc(sizeof(char)*10);
						printf("\nInsira o código do produto:");
						while (1) {
							if (scanf("%s", codprod)) {
								break;
							}
						}
						int filial;
						printf("\nInsira a FILIAL: ");
						while (1) {
							if (scanf("%d", &filial)) break;
						}

						if (filial >=1 && filial <=3)
							query9(sells, codprod, filial);
					}
					break;
			case 'a':
					if (!data_loaded)
						printf("Carregue os dados para o programa primeiro, por favor.\n");
					else {
						char *codcliente = (char*) malloc(sizeof(char)*10);
						printf("\nInsira o código do cliente:");
						while (1) {
							if (scanf("%s", codcliente)) {
								break;
							}
						}
						int new_mes;
						printf("\nInsira o mês: ");
						while (1) {
							if (scanf("%d", &new_mes)) break;
						}

						if (new_mes>=1 && new_mes <=12)
							query10(sells, codcliente, new_mes);
					}

			case 'b': 
					
					if (!data_loaded)
						printf("Carregue os dados para o programa primeiro, por favor.\n");
					else {

						printf("\nInsira o N que deseja: ");
						int n;
						while (1) {
							if (scanf("%d", &n)) {
								break;
							}
						}
						query11(sells, n);
					}
			default: 
				break;
		}

		input = scanf("%c", &option_selected);
		
		if (!checkInput(input, option_selected)) 
			option_selected = '0';
	
	}

	if (option_selected == 'q' || option_selected == 'Q' || option_selected == 'y') {
		printf("A sair do programa...\n");
		freeAVL(products, 0);
		freeAVL(clients, 0);
		freeAVL(sells, 1);
		free(set);
		if (option_selected=='y') loadOption();
	}
}

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

void loadOption () {
	
	clear_screen();

	/*---------------------------------------------------------------*/
	
	clock_t start, end;
	double cpu_time_used;
					
	char option_selected = 0, data_loaded = 0, input;
	int mes;
	
	GLOBAL set = (GLOBAL) malloc(sizeof(struct settings)); 

	AVL products = NULL;
	AVL clients  = NULL;
	AVL sells    = NULL;
	
	/*---------------------------------------------------------------*/

	displayMenuAndOptions();

	input = scanf("%c", &option_selected);
	if (!checkInput(input, option_selected))
		option_selected = '0';

	/*---------------------------------------------------------------*/

	while (option_selected != 'q' && option_selected != 'Q' && option_selected != 'y') {

		if (data_loaded == 1) printf("\n\t\t\t\t\t\t[DADOS CARREGADOS]\n");
		else printf("\n\t\t\t\t\t\t[DADOS NÃO CARREGADOS]\n");

		switch(option_selected) {

			/*---------------------------------------------------------------*/

			case 'x' : 
				if (option_selected == 'X' || option_selected == 'x')
					displayMenuAndOptions();
				break;

			/*---------------------------------------------------------------*/

			case '1': 

				if (!data_loaded) {
								
					printf("\nA efetuar a leitura de dados...\n");
					
					start = clock();
					
					products = readNvalidate_products(PROD_PATH, products, set);
					write_inorder_avl_on_file(VAL_PROD_PATH, products, set);
					
					clients = readNvalidate_clients(CLIE_PATH, clients, set);
					write_inorder_avl_on_file(VAL_CLIE_PATH, clients, set);
					
					sells = readNvalidate_sells(SELL_PATH, sells, set, products, clients);
					write_inorder_avl_on_file(VAL_SELL_PATH, sells, set);

					end = clock();
					cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
					
					query1(set);

					data_loaded = 1;
					printf("\nDados Carregados e guardados no folder validData/.");
					showTime(cpu_time_used);

					printf("\n\t[VOLTAR AO MENU INICIAL (Pressionar X + ENTER)]\n");

				} else {
					printf("Os dados já foram carregados, por favor escolha outra opcção.\n");
					printf("Carregar novos dados? [y/n]\n");
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

			default: break;
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

void displayMenuAndOptions () {

	clear_screen();

	printf("\n\t\tSistema geral de Vendas [SGV]\n\n");

	printf("Opções disponivéis (Introduza o respetivo número):\n\n");

	printf("[1]  Leitura dos ficheiros com os Produtos, Clientes e Vendas.\n");
	printf("[2]  Lista de Produtos que se iniciam por uma letra maiúscula.\n");
	printf("[3]  Nº total de Vendas num mês e o total faturado (global ou por filial).\n");
	printf("[4]  Lista de produtos que ninguém comprou (global ou por filial).\n");
	printf("[5]  Lista de Clientes que realizaram compras em todas as filiais.\n");
	printf("[6]  Nº de clientes registados que não realizaram compras e o nº de produtos que ninguém comprou\n");/*
	printf("[7]  Tabela de todos os produtos comprados mês a mês, organizada por filial.\n");
	printf("[8]  Nº total de vendas num intervalo de meses (p.ex. [1..3]) e total faturado.\n");
	printf("[9]  Dado um código de Produto e uma filial apresentar os códigos (e o Nº total),\n");
	printf("     dos clientes que o compraram (distinguindo N e P)\n");
	printf("[10] Dado um Cliente e um mês determinar a lista de códigos que mais comprou por quantidade, \nordem descendente.\n");
	printf("[11] Lista dos N produtos mais vendidos no ano, indicando o nº total de clientes e nº de unidades vendidas, filial a filial.\n");
	printf("[12] Dado um Cliente indica quais os códigos dos 3 produtos em que mais gastou dinheiro.\n");
*/}

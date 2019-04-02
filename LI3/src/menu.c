
/** @file menu.c
*	@brief Ficheiro que implementa o menu do SGV.
*
*	@autor João Pedro Rodrigues Azevedo
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@bug Bugs de entrada de argumentos (Não muito relevantes).
*	
*/

/*MACRO para suprimir warnings de strdup da library <string.h>*/
#define _GNU_SOURCE

/*_________________BIBLIOTECAS STD IMPORTADAS________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

/*_________________BIBLIOTECAS IMPLEMENTADAS____________________________*/

/*Contém estatisticas de leitura de dados*/
#include "global.h"
/*Para validacao de produtos*/
#include "catProdutos.h"
/*Para validacao de clientes*/
#include "catClientes.h"
/*Para validacao de vendas*/
#include "catVendas.h"
/*Para criacao das estruras de armazenamento dos dados de leitura*/
#include "avlstruct.h"
/*Para obter a query requested*/
#include "queries.h"
/*Default include*/
#include "menu.h"
/*Para apresentar tempos de leitura e outros*/
#include "time.h"

/*----------------------------------------------------------------------*/

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

	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	int l = 0;
	while (l < w.ws_col) {printf(RED "_" RESET); l++;}

	printf(CYN "\n\n\t\t\t\t -- Sistema geral de Vendas [SGV] --\n" RESET);

	l = 0;
	while (l < w.ws_col) {printf(RED "_" RESET); l++;}

	printf(YEL "\n\n=> Opções disponivéis (Introduza o respetivo número):\n" RESET);

	if (loaded == 1) 
		printf(YEL "\n\t\t\t\t\t\t\t\t\t[DADOS CARREGADOS]\n\n" RESET);
	else 
		printf(YEL "\n\t\t\t\t\t\t\t\t\t[DADOS NÃO CARREGADOS]\n\n" RESET);

	printf("\t[1]  Leitura de ficheiros e validação.\n");
	printf("\n\t[2]  Lista de Produtos que se iniciam por uma letra maiúscula.\n");
	printf("\n\t[3]  Nº total de Vendas num mês e o total faturado (global ou por filial).\n");
	printf("\n\t[4]  Lista de produtos que ninguém comprou (global ou por filial).\n");
	printf("\n\t[5]  Lista de Clientes que realizaram compras em todas as filiais.\n");
	printf("\n\t[6]  Nº de clientes que não realizaram compras + Nº de produtos não comprados.\n");
	printf("\n\t[7]  Tabela de todos os produtos comprados mês a mês, organizada por filial.\n");
	printf("\n\t[8]  Nº total de vendas num intervalo de meses (p.ex. [1..3]) e total faturado.\n");
	printf("\n\t[9]  Dado um código de Produto e uma filial apresentar os códigos (e o Nº total)\n");
	printf("\t     dos clientes que o compraram (distinguindo N e P)\n");
	printf("\n\t[a]  Lista de códigos que mais comprou por quantidade, ordem descendente.\n");
	printf("\n\t[b]  Lista dos N produtos mais vendidos no ano.\n");
	printf("\n\t[c]  Códigos dos 3 produtos em que mais gastou dinheiro.\n\n");

	l = 0;
	while (l < w.ws_col) {printf(RED "_" RESET); l++;}
}

void displayFicheirosLeitura() {

	printf(YEL "\n-> Qual ficheiro deseja ler?\n\n" RESET);
	
	printf(RED "\t[1] Vendas_1M.txt\n");
	printf("\t[2] Vendas_3M.txt\n");
	printf("\t[3] Vendas_5M.txt\n" RESET);

}

/*----------------------------------------------------------------------*/
					/*FUNÇÃO PRINCIPAL DO MENU*/

void loadMenu () {
	
	/*---------------------------------------------------------------*/

	clear_screen();

	/*---------------------------------------------------------------*/
	
	clock_t start, end;
	double cpu_time_used;
					
	char option_selected = 0, data_loaded = 0, input;
	int mes;
	int argumentoInteiro;
	char codprod[10], codcliente[10];

	/*---------------------------------------------------------------*/

	GLOBAL set = (GLOBAL) malloc(sizeof(struct settings)); 

	CAT_PRODUTOS products = NULL;
	CAT_CLIENTES clients  = NULL;
	CAT_VENDAS   sells    = NULL;
	
	FAT_FILIAL fat = NULL;
	FILIAL fil = NULL;

	/*---------------------------------------------------------------*/

	displayMenuAndOptions(data_loaded);

	input = scanf("%c", &option_selected);

	if (!checkInput(input, option_selected))
		option_selected = '0';

	/*---------------------------------------------------------------*/

	while (option_selected != 'q' && option_selected != 'Q' && option_selected != 'y') {
			
		switch(option_selected) {

			/*---------------------------------------------------------------*/
			/*PARA SAIR DO PROGRAMA*/

			case 'x' : 
					displayMenuAndOptions(data_loaded);
				break;

			case 'X' : 
					displayMenuAndOptions(data_loaded);
				break;

			/*---------------------------------------------------------------*/
			/*QUERIES DISPONIVEIS*/

			case '1': 

				if (!data_loaded) {
				
					displayFicheirosLeitura();

					while (1) {  
						
						if (scanf("%d", &argumentoInteiro)==1) {

							if (argumentoInteiro == 1 || 
								argumentoInteiro == 2 || 
								argumentoInteiro == 3) {

								printf(YEL "\n\n-> A efetuar a leitura de dados...\n" RESET);
								
								start = clock();

								products = readNvalidate_products(PROD_PATH, products, set);
								clients = readNvalidate_clients(CLIE_PATH, clients, set);
						
								switch (argumentoInteiro) {
									case 1: 
										printf("\n...A ler Vendas_1M.txt ...\n");
										sells = readNvalidate_sells(SELL_PATH_1M, sells, set, products, clients);
										break;
									case 2:
										printf("\n...A ler Vendas_3M.txt ...\n");
										sells = readNvalidate_sells(SELL_PATH_3M, sells, set, products, clients);
										break;
									case 3:
										printf("\n...A ler Vendas_5M.txt ...\n");
										sells = readNvalidate_sells(SELL_PATH_5M, sells, set, products, clients);
										break;
								}
					
								end = clock();
							
								/*Gera a faturação a partir das vendas*/
								fat = initFaturacao(fat, products, sells);
								fil = initFilial(fil, clients, sells);

								/*Escreve os elementos válidos da leitura*/
								write_inorder_avl_on_file(VAL_CLIE_PATH, clients, set);
								write_inorder_avl_on_file(VAL_PROD_PATH, products, set);
								write_inorder_avl_on_file(VAL_SELL_PATH, sells, set);
					
								cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
								
								query1(set);

								data_loaded = 1;
			
								printf(YEL "\nDados Carregados e guardados no folder validData/." RESET);
								showTime(cpu_time_used);

								printf(GRN "\n\t[VOLTAR AO MENU INICIAL (Pressionar X + ENTER)]\n" RESET);

								break;
					
					} else printf("[ERRO] Escolha uma opcção válida por favor...\n");

				} else printf("[ERRO] Escolha uma opcção válida por favor...\n");

				} 
				} else {
					printf(RED "Os dados já foram carregados, por favor escolha outra opcção.\n" RESET);
					printf(YEL "Carregar novos dados? [y]\n" RESET);
				}

				break;

			/*---------------------------------------------------------------*/

			case '2': 
					if (!data_loaded) 
						printf(RED "Carregue os dados para o programa primeiro, por favor.\n" RESET);
					else {
						printf("Escolha uma letra (Maiúscula): ");
						while (1) {
							char letra;
							if (scanf("%c", &letra) == 1) 
								if (letra >= 'A' && letra <='Z') {
									
									LISTA_PROD ls = NULL;
									ls = initLista(ls, 10000);
									ls = query2(ls, products, letra);
	
									pages(ls, data_loaded);

									printf("\nNúmero total de produtos com letra %c: %d.\n", letra, getCurrentSize(ls));
					
									freeList(ls);
									printf(GRN "\n\t[VOLTAR AO MENU INICIAL (Pressionar X + ENTER)]\n" RESET);
									break;
								}
						}
					}
					break;

			/*---------------------------------------------------------------*/

			case '3':
					if (!data_loaded) 
						printf(RED "Carregue os dados para o programa primeiro, por favor.\n" RESET);
					else {
						printf("Insira um mês: ");
						while (1)
							if (scanf("%d", &mes)==1)
								if (mes >= 1 && mes <= 12)
									break;
						char *codprod = (char*) malloc(sizeof(char)*10);
						int opcao_mostragem;
						printf("Insira um código de Produto: ");
						while(1) {
							if (scanf("%s", codprod)!=-1) {
									if (verify_product(codprod)) {
										printf("Deseja o resultado por filial ou o Total? [0: FILIAL | 1: TOTAL]");
										while (1) {
											if (scanf("%d", &opcao_mostragem)) {
												if (opcao_mostragem == 0 || opcao_mostragem == 1) {
													query3(fat, mes, codprod, opcao_mostragem);
													printf(GRN "\n\t[VOLTAR AO MENU INICIAL (Pressionar X + ENTER)]\n" RESET);
													free(codprod);
													break;
												}
										}
									}
									break; 
								} else {
									printf(RED "[ERROR] Produto inválido!\n" RESET);
									printf("Insira um código de Produto: ");
								}
							} else {
								printf("Produto inválido!\n");
								printf("Insira um código de Produto: ");
							} 
						}
					}

					break;

			/*---------------------------------------------------------------*/

			case '4': 
					if (!data_loaded)
						printf(RED "Carregue os dados para o programa primeiro, por favor.\n" RESET);
					else {
						query4(fat, products);
					}
					break;

			case '5': 
					if (!data_loaded)
						printf(RED "Carregue os dados para o programa primeiro, por favor.\n" RESET);
					else {
						printf("\n => A gerar lista...\n");
						query5(fil, clients);
						printf(GRN "\n\t[VOLTAR AO MENU INICIAL (Pressionar X + ENTER)]\n" RESET);
						break;
					}

					break;

			case '6': 
					if (!data_loaded)
						printf(RED "Carregue os dados para o programa primeiro, por favor.\n" RESET);
					else {
						query6(fat, fil, products, clients);
						printf(GRN "\n\t[VOLTAR AO MENU INICIAL (Pressionar X + ENTER)]\n" RESET);
					}
					break;
			case '7': 
					if (!data_loaded)
						printf(RED "Carregue os dados para o programa primeiro, por favor.\n" RESET);
					else {
						printf("\nInsira um cliente: ");						
						while (1) {
							if (scanf("%s", codcliente)!=-1) {
								if (verify_client(codcliente)) 
									break;
								else {
									printf(RED "[ERROR] Cliente inválido!\n" RESET);
									printf("Insira um cliente: ");
								}
							}
						}
						query7(sells, codcliente);
						printf(GRN "\n\t[VOLTAR AO MENU INICIAL (Pressionar X + ENTER)]\n" RESET);
						}
					break;

			case '8': 
					if (!data_loaded)
						printf(RED "Carregue os dados para o programa primeiro, por favor.\n" RESET);
					else {
				
						printf("\nInsira um intervalo de meses:\n");
						printf("(Exemplo o intervalo [1..3] ficaria > 1..3)\n");
						int mes_inf, mes_sup;
						while (1) {
							if (scanf("%d..%d", &mes_inf, &mes_sup))
								if ((mes_inf <= mes_sup || mes_sup <= mes_inf) &&
									mes_inf >= 1 && mes_inf <= 12 &&
									mes_sup >= 1 && mes_sup <= 12) {
										query8(fat, mes_inf, mes_sup);
										break;
								}
						}
								printf(GRN "\n\t[VOLTAR AO MENU INICIAL (Pressionar X + ENTER)]\n" RESET);
					}
					break;

			case '9': 
					if (!data_loaded)
						printf(RED "Carregue os dados para o programa primeiro, por favor.\n" RESET);
					else {

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
								printf(GRN "\n\t[VOLTAR AO MENU INICIAL (Pressionar X + ENTER)]\n" RESET);
					break;
			case 'a':
					if (!data_loaded)
						printf(RED "Carregue os dados para o programa primeiro, por favor.\n" RESET);
					else {
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
						printf("\nProdutos que mais comprou: \n");
						if (new_mes>=1 && new_mes <=12)
							query10(sells, codcliente, new_mes);
					}
					printf(GRN "\n\t[VOLTAR AO MENU INICIAL (Pressionar X + ENTER)]\n" RESET);
					break;

			case 'b': 
					
					if (!data_loaded)
						printf(RED "Carregue os dados para o programa primeiro, por favor.\n" RESET);
					else {

						printf("\nInsira o N que deseja: ");
						int n;
						while (1) {
							if (scanf("%d", &n)) {
								break;
							}
						}
						query11(sells, n);
						printf(GRN "\n\t[VOLTAR AO MENU INICIAL (Pressionar X + ENTER)]\n" RESET);
					}
					break;

			case 'c':

					if (!data_loaded)
						printf(RED "Carregue os dados para o programa primeiro, por favor.\n" RESET);
					else {
					
						printf("\nInsira um cliente: ");
						
						while (1) {
							if (scanf("%s", codcliente)!=-1) break;
						}
						printf("\n");
						query12(sells, codcliente);
						printf(GRN "\n\t[VOLTAR AO MENU INICIAL (Pressionar X + ENTER)]\n" RESET);
					}				

			default: 
				break;
		}

		input = scanf("%c", &option_selected);
		
		if (!checkInput(input, option_selected)) 
			option_selected = '0';
	
	}

	/*---------------------------------------------------------------*/

	if (option_selected == 'q' || option_selected == 'Q' || option_selected == 'y') {
		printf(YEL "A sair do programa...\n" RESET);
		freeAVL(products, 0);
		freeAVL(clients, 0);
		freeAVL(sells, 1);
		free(set);
		if (option_selected=='y') loadMenu();
	}
}

/*---------------------------------------------------------------*/

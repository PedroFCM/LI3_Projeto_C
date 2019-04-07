 
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
#include "lstring.h"
#include "hashtables.h"
#include "catProdutos.h"
#include "Faturacao.h"
#include "Filial.h"
#include "catVendas.h"


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

/*-----------------------------------------------------------------------*/

void showStatPorFilial(VENDAS n_vendas, FAT_MES faturacao) {
	int l, c;
	printf("\n\n-> Faturação por Filial: \n\n");
	
	printf("   1   2   3     (Filial)\n");
	
	for (l = 0; l < 2; l++) 
	{
		if (l == 0) 
			printf("P: ");
		
		if (l == 1) 
			printf("N: ");
		
		for (c = 0; c < 3; c++)
			printf("%.3f | ", faturacao[l][c]);
		
		printf("\n");
	}
	
	printf("\n-> Número de vendas por Filial: \n\n");
	
	printf("   1   2   3     (Filial)\n");
	
	for (l = 0; l < 2; l++) 
	{
		if (l == 0) 
			printf("P: ");
		
		if (l == 1) 
			printf("N: ");
		
		for (c = 0; c < 3; c++) 
			printf("%d | ", n_vendas[l][c]);
		
		printf("\n");
	}
}

void showStatGlobal(VENDAS n_vendas, FAT_MES faturacao) {
	int l, c;
	int globalVendas[2][1];
	float globalFat[2][1];

	printf("\n\nFaturação total das Filiais: \n\n");
	for (l = 0; l < 2; l++) 
	{
		if (l == 0) 
			printf("P: ");
		
		if (l == 1) 
			printf("N: ");
		
		for (c = 0; c < 1; c++) 
		{
			globalFat[l][c] = faturacao[l][0] + faturacao[l][1] + faturacao[l][2];
			printf("%.3f | ", globalFat[l][c]);
		}
		
		printf("\n");
	}
	
	printf("\nNúmero de vendas totais das Filiais: \n\n");
	
	for (l = 0; l < 2; l++) 
	{
		if (l == 0) 
			printf("P: ");
		
		if (l == 1) 
			printf("N: ");
		
		for (c = 0; c < 1; c++) 
		{
			globalVendas[l][c] = n_vendas[l][0] + n_vendas[l][1] + n_vendas[l][2];
			printf("%d | ", globalVendas[l][c]);
		}
		
		printf("\n");
	}
}

void query3 (FAT_FILIAL fat, int mes, char *produto, int opcao) 
{	
	int** v = (VENDAS) malloc(sizeof(int*)*2);
	float** f = (FAT_MES) malloc(sizeof(float*)*2);
	int l, c;

	for (l = 0; l < 2; l++)   /* N ou P */
	{
		f[l] = malloc(sizeof(float) * 3);
		v[l] = malloc(sizeof(int) * 3);
		
		for (c = 0; c < 3; c++)  /* FILIAL 1,2 ou 3*/
		{
			f[l][c] = 0.0;
			v[l][c] = 0;
		}
	}

	vendasNoMes(getFaturacao(fat, 0), 0, produto, mes-1, f, v);
	vendasNoMes(getFaturacao(fat, 1), 1, produto, mes-1, f, v);
	vendasNoMes(getFaturacao(fat, 2), 2, produto, mes-1, f, v);

	switch(opcao)
	{	
		case 0: 
			showStatPorFilial(v,f);
			break;	
			
		case 1: 
			showStatGlobal(v,f);
			break;

		default: 
			break;
	}

	free(v);
	free(f);

}

/*-----------------------------------------------------------------------*/
/*
void query4(FAT_FILIAL fat, AVL produtos, int opcao)
{
	AVL* produtoFilial1 = malloc(sizeof(AVL));
	AVL* produtoFilial2 = malloc(sizeof(AVL));
	AVL* produtoFilial3 = malloc(sizeof(AVL));
	
	*produtoFilial1 = NULL;
	*produtoFilial2 = NULL;
	*produtoFilial3 = NULL;

	prodNinguemComprou(fat, produtos, produtoFilial1, produtoFilial2, produtoFilial3, opcao);

	printf("Produtos não comprados nas 3 filiais: %d Produto(s).\n", 
			inorder_avl_just_tag(*produtoFilial1));
	
	freeAVL(*produtoFilial1, 0);
	freeAVL(*produtoFilial2, 0);
	freeAVL(*produtoFilial3, 0);

}
*/

void query4(FAT_FILIAL fat, AVL produtos, int opcao)
{
	AVL* produtoFilial1 = malloc(sizeof(AVL));
	AVL* produtoFilial2 = malloc(sizeof(AVL));
	AVL* produtoFilial3 = malloc(sizeof(AVL));
	
	*produtoFilial1 = NULL;
	*produtoFilial2 = NULL;
	*produtoFilial3 = NULL;

	prodNinguemComprou(fat, produtos, produtoFilial1, produtoFilial2, produtoFilial3, opcao);

	int fil1, fil2, fil3;

	switch(opcao)
	{
		case 0: 
			printf("Produtos não comprados na filial 1:\n");
			fil1 = inorder_avl_just_tag(*produtoFilial1);
			
			printf("Produtos não comprados na filial 2:\n");
			fil2 = inorder_avl_just_tag(*produtoFilial2);
			
			printf("Produtos não comprados na filial 3:\n");
			fil3 = inorder_avl_just_tag(*produtoFilial3);

			printf("Número de Produtos não comprados na filial 1: %d\n", fil1);
			printf("Número de Produtos não comprados na filial 2: %d\n", fil2);
			printf("Número de Produtos não comprados na filial 3: %d\n", fil3);
			break;

		case 1: 
			printf("Produtos não comprados nas 3 filiais: %d Produto(s).\n", inorder_avl_just_tag(*produtoFilial1));
			break;
	}
}

/*-----------------------------------------------------------------------*/

void query5(FILIAL filial, AVL clientes) {

    AVL compramEmTodas = NULL; 

    compramEmTodas = compraramEmTodas(filial, clientes, &compramEmTodas);

    printf("\nClientes que compraram em todas as filiais:\n");

    int r = inorder_avl_just_tag(compramEmTodas); 

    printf("\n>> Existem %d clientes que compraram em todas as filiais.\n", r);

	freeAVL_andTag(compramEmTodas);    
}

/*-----------------------------------------------------------------------*/

int existeProdutoNaAVLFilial (AVL filial, char* elem) {
	
	int cmp;
	
	if (filial != NULL) {

		cmp = strcmp(elem, getProdFatura(getFatura(filial)));

		if (cmp==0) return 1;
		else if (cmp > 0) 
			return (existeProdutoNaAVLFilial(getDir(filial), elem));
		else return (existeProdutoNaAVLFilial(getEsq(filial), elem));
	}

	return 0;
}

void produtosSemCompras (FAT_FILIAL fat, AVL produtos, int *produtosNC) {

	if (produtos != NULL) {
		
		char *aux;
		aux = strdup(getTag(produtos));
		aux[6]='\0';

		if (!existeProdutoNaAVLFilial(getFaturacao(fat, 0), aux) &&
			!existeProdutoNaAVLFilial(getFaturacao(fat, 1), aux) &&
			!existeProdutoNaAVLFilial(getFaturacao(fat, 2), aux)) {
			*produtosNC += 1;
		}

		produtosSemCompras(fat, getEsq(produtos), produtosNC);
		produtosSemCompras(fat, getDir(produtos), produtosNC);
	}
}

void query6 (FAT_FILIAL fat, FILIAL fil, AVL produtos, AVL clientes) {

	int *clientesSemCompras = (int*) malloc(sizeof(int));
	int *produtosNaoComprados = (int*) malloc(sizeof(int));

	*clientesSemCompras = 0;
	*produtosNaoComprados = 0;

	clientesSemCompra(fil, clientes, clientesSemCompras);
	produtosSemCompras(fat, produtos, produtosNaoComprados);

	printf("Existem %d clientes que não realizaram compras.\n", 
			*clientesSemCompras);
	printf("Existem %d produtos que não foram comprados.\n", 
			*produtosNaoComprados);

	free(clientesSemCompras);
	free(produtosNaoComprados);
}

/*-----------------------------------------------------------------------*/

void query7(FILIAL filial, char* cliente){

	int **nProd = malloc(sizeof(int*)*12);
	int i = 0, j = 0;

	for (i = 0; i < 12; i++){
		nProd[i] = malloc(sizeof(int)*3);
		for (j = 0; j < 3; j++){
			nProd[i][j] = 0;
		}
	}

	tabelaComprasFilial(getAVLfilial(filial,1), cliente, nProd, 1);
	tabelaComprasFilial(getAVLfilial(filial,2), cliente, nProd, 2);
	tabelaComprasFilial(getAVLfilial(filial,3), cliente, nProd, 3);

	printf("\nO Cliente %s fez as seguintes compras:\n", cliente);	

	printf("\nMÊS\t\tFILIAL1\t\tFILIAL2\t\tFILIAL3");

	for (i = 0; i < 12; i++){

		printf("\n\t-------------------------------------------------\n");
		printf(" %d\t|", i+1);

		for (j = 0; j < 3; j++){
		
		printf("\t%d\t|", nProd[i][j]);

		}	
	}

	printf("\n\t-------------------------------------------------\n");

	free(nProd);
}

/*------------------------------------------------------------------------------------------------*/

void query8(FAT_FILIAL fat, int min, int max)
{
	float *faturacao = (float*) malloc(sizeof(float*));
	int *total_vendas = (int*) malloc(sizeof(int*));
	*faturacao = 0.0;
	*total_vendas = 0;

	vendasEntreMeses(getFaturacao(fat, 0), min-1, max-1, faturacao, total_vendas);
	vendasEntreMeses(getFaturacao(fat, 1), min-1, max-1, faturacao, total_vendas);
	vendasEntreMeses(getFaturacao(fat, 2), min-1, max-1, faturacao, total_vendas);

	printf("Nº Vendas: %d venda(s) | Total Faturado: %f euro(s)\n", *total_vendas, *faturacao);

	free(faturacao);
	free(total_vendas);
}

/*------------------------QUERY 9 TESTING------------------------*/

int matrizAzeros (float **f, int flag) {

	int c;

		for (c = 0; c < 12; c++)
			if (f[flag][c]!=0) return 0;

	return 1;
}

LString geraClientesFilial (AVL fil, char *codProd, LString compras, char tipo) {

	if (fil != NULL) 
	{
			if (existeNaLista(codProd, getList(getGestaoFilial(fil))))
			{

				switch(tipo) {
				
					case 'N': 
						if (0==matrizAzeros(getFatMesElem(getList(getGestaoFilial(fil))), 0))
						{				
							compras = pushLString(compras, getClienteFilial(getGestaoFilial(fil)), 'N');
						}
						break;

					case 'P': 
						if (0==matrizAzeros(getFatMesElem(getList(getGestaoFilial(fil))), 1)) 
						{
							compras = pushLString(compras, getClienteFilial(getGestaoFilial(fil)), 'P');
						} 
				}

			}

			compras = geraClientesFilial(getEsq(fil), codProd, compras, tipo);
			compras = geraClientesFilial(getDir(fil), codProd, compras, tipo);
	}

	return compras;
}

void query9 (FILIAL fil, char *codProd, int filial) {

	LString comprasN = NULL, comprasP = NULL;

	comprasN = geraClientesFilial(getAVLfilial(fil, filial), codProd, comprasN, 'N');
	comprasP = geraClientesFilial(getAVLfilial(fil, filial), codProd, comprasP, 'P');

	printf("\n=> Clientes (Com promoção): (%d cliente(s))\n", sizeLString(comprasP));

	if (comprasP == NULL)
		printf("Nenhum cliente encontrado do tipo P.\n");

	printLString(comprasP, 3);

	printf("\n=> Clientes (Sem promoção): (%d cliente(s))\n", sizeLString(comprasN));

	if (comprasN == NULL)
		printf("Nenhum cliente encontrado do tipo N.\n");

	printLString(comprasN, 3);

}


/*-----------------------------------------------------------------------------------*/

void query10(FILIAL filial, char* cliente, int mes)
{
	AVL* prodMaisComprad = malloc(sizeof(AVL));
	*prodMaisComprad = NULL;

	cria_avl_produtos_Comprados(getAVLfilial(filial, 1), prodMaisComprad, cliente, mes-1);
	cria_avl_produtos_Comprados(getAVLfilial(filial, 2), prodMaisComprad, cliente, mes-1);
	cria_avl_produtos_Comprados(getAVLfilial(filial, 3), prodMaisComprad, cliente, mes-1);

	printDecresAvl(*prodMaisComprad);
}

/*-----------------------------------------------------------------------------------*/

void geraTabelaQuantidades (AVL filial, HEAD_TABLE h, int flag) {

	if (filial != NULL) {

		updateQuantidadesProduto(getList(getGestaoFilial(filial)), h, flag);

		geraTabelaQuantidades(getEsq(filial), h, flag);
		geraTabelaQuantidades(getDir(filial), h, flag);
	}
}

void query11 (FILIAL filial, int n) {
	
	HEAD_TABLE h = NULL;

	h = initTable(h, 200000);
	
	printf("A gerar a lista...\n");
	geraTabelaQuantidades(getAVLfilial(filial, 1) , h, 1);
	geraTabelaQuantidades(getAVLfilial(filial, 2) , h, 2);
	geraTabelaQuantidades(getAVLfilial(filial, 3) , h, 3);

	printf("A ordenar a lista...\n");
	quicksort(h, 0, getSize(h) - 1);
	printf("> Ordenação feita.\n");

	printNfirstTableReverse(h, n);

	free_hashtable(h);

}

/*-----------------------------------------------------------------------------------*/

void query12 (FILIAL filial, char* cliente){

	LString produtos = NULL;

	produtos = top3Compras_do_cliente(getAVLfilial(filial,1), cliente, produtos);
	produtos = top3Compras_do_cliente(getAVLfilial(filial,2), cliente, produtos);
	produtos = top3Compras_do_cliente(getAVLfilial(filial,3), cliente, produtos);

	produtos = quickSortL (produtos, 1);

	printLString(produtos, 1);
	
}

/*-----------------------------------------------------------------------------------*/

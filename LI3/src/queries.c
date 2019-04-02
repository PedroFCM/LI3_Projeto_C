
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
#include "stack.h"
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
}

/*-----------------------------------------------------------------------*/

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

}

/*-----------------------------------------------------------------------*/

void query5(FILIAL filial, AVL clientes) {

    AVL compramEmTodas = NULL; 

    compramEmTodas = compraramEmTodas(filial, clientes, &compramEmTodas);

    printf("\nClientes que compraram em todas as filiais:\n");

    int r = inorder_avl_just_tag(compramEmTodas); 

    printf("\n>> Existem %d clientes que compraram em todas as filiais.\n", r);
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

	printf("Nº Vendas: %d euro(s) | Total Faturado: %f euro(s)\n", *total_vendas, *faturacao);
}

/*-----------------------------------------------------------------------*/

void query9 (AVL vendas, char* produto, int filial){

	Stack clientesP = NULL;
	Stack clientesN = NULL;
	
	clientesP = initStack(clientesP, 10000);
	clientesN = initStack(clientesN, 10000);

	compraramNaFilial(vendas, produto, filial, clientesP, clientesN);

	if (getSP(clientesP) > 0) {
		
		printf("\nClientes do tipo P: (%d resultados)\n", getSP(clientesP));
		printStack(clientesP);
	
	} else printf("\nTIPO P VAZIO\n");
	
	if (getSP(clientesN) > 0) {
	
		printf("\nClientes do tipo N: (%d resultados)\n", getSP(clientesN));
		printStack(clientesN);
	
	} else printf("\nTIPO N VAZIO\n");

	freeStack(clientesP);
	freeStack(clientesN);
}

/*------------------------QUERY 9 TESTING------------------------*/
/*
int matrizAzeros (float **f) {

	int l, c;

	for (l = 0; l < 2; l++)
		for (c = 0; c < 12; c++)
			if (f[l][c]!=0) return 0;

	return 1;
}

void geraClientesFilial (AVL fil, char *codProd, LString comprasN, LString comprasP) {

	if (fil != NULL) 
	{
			if (existeNaLista(codProd, getFatMes(getList(getGestaoFilial(fil)))))
			{
				if (matrizAzeros(getFatMes(getGestaoFilial(fil))), 1) 
				{
					comprasN = insertLString(comprasN, getClienteFilial(fil), 'N');

				} else if (matrizAzeros(getFatMes(getList(getGestaoFilial(fil)))), 2) {

					comprasP = insertLString(comprasP, getClienteFilial(fil), 'P');
				
				} 

			}

			geraClientesFilial(getEsq(fil), codProd, comprasN, comprasP);
			geraClientesFilial(getDir(fil), codProd, comprasN, comprasP);
	}
}

void query9 (FILIAL fil, char *codProd, int filial) {

	LString comprasN = NULL;
	LString comprasP = NULL;

	geraClientesFilial(getAVLfilial(fil, filial), codProd, comprasP, comprasN);

	printLString(comprasN);
	printLString(comprasP);

}
*/
/*------------------------------------------------------------------------------------------------*/
/*
LString recursive_query10 (AVL vendas, char* cliente, int mes, LString produtos) {

	if (vendas != NULL) {

		if (strcmp(getCodCliente(vendas), cliente) == 0 && mes == getMes(vendas))
			produtos = insertLString (produtos, getCodProd(vendas), 0, 0);

		produtos = recursive_query10(getEsq(vendas), cliente, mes, produtos);		
		produtos = recursive_query10(getDir(vendas), cliente, mes, produtos);

	}

	return produtos;
}

void query10 (AVL vendas, char* cliente, int mes){

	LString l = NULL;

	l = recursive_query10(vendas, cliente, mes, l);

	l = quickSortL(l, 0);

	printLString(l, 0);
}
*/
/*-----------------------------------------------------------------------------------*/

void recursive_query11(AVL vendas, HEAD_TABLE h) {

	if (vendas != NULL) {

		update(h, getCodProd(vendas), 
				  getFilial(vendas), 
				  getQuantidade(vendas));
		
		recursive_query11(getEsq(vendas),  h);
		recursive_query11(getDir(vendas), h);
	}
}

void query11 (AVL vendas, int n) {
	
	HEAD_TABLE h = NULL;

	h = initTable(h, 200000);
	
	recursive_query11(vendas, h);

	juntaQuantFilial(h);

	quicksort(h, 0, getSize(h) - 1);

	printf("\nOs %d produtos mais comprados são: \n\n", n);

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

void recursive_query10(AVL filial, AVL* prodMaisComprad, char* cliente, int mes) 
{
	if(filial != NULL)
	{
		int equal = strcmp(getClienteFilial(getGestaoFilial(filial)), cliente);

		if(!equal)
			acumVendas(filial, prodMaisComprad, mes);

		else
		{
			if(equal > 0)
				recursive_query10(getEsq(filial), prodMaisComprad, cliente, mes);
			else
				recursive_query10(getDir(filial), prodMaisComprad, cliente, mes);
		}

	}
}

void query10(FILIAL filial, char* cliente, int mes)
{
	AVL* prodMaisComprad = malloc(sizeof(AVL));
	*prodMaisComprad = NULL;

	recursive_query10(getAVLfilial(filial, 1), prodMaisComprad, cliente, mes-1);
	recursive_query10(getAVLfilial(filial, 2), prodMaisComprad, cliente, mes-1);
	recursive_query10(getAVLfilial(filial, 3), prodMaisComprad, cliente, mes-1);

	printDecresAvl(*prodMaisComprad);
}
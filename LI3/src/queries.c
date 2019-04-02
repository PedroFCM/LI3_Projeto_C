
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

/*______________________________________________________________________*/

/*NOVO TYPE que guarda matrizes de floats*/
typedef float** FAT_PRECO;

/*NOVO TYPE que guarda matrizes de inteiros*/
typedef int** FAT_QUANT;

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

void recursive_query3(AVL faturacao, int filial, char* prod, int mes, FAT_MES f, VENDAS v) 
{
	if(faturacao != NULL) 
	{		
		int equal = strcmp(getProdFatura(getFatura(faturacao)), prod);
		int i;

		if(!equal) 
			for(i = 0; i < 2; i++)
			{	
				f[i][filial] += getFatMes(getFatura(faturacao))[i][mes];
				v[i][filial] += getNumVendas(getFatura(faturacao))[i][mes];
			}

		else
		{
			if(equal > 0)
				recursive_query3(getEsq(faturacao), filial, prod, mes, f, v);
			else
				recursive_query3(getDir(faturacao), filial, prod, mes, f, v);
		}
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

	/* FILIAL 1 */
	recursive_query3(getFaturacao(fat, 0), 0, produto, mes-1, f, v);
	/* FILIAL 2 */
	recursive_query3(getFaturacao(fat, 1), 1, produto, mes-1, f, v);
	/* FILIAL 3 */
	recursive_query3(getFaturacao(fat, 2), 2, produto, mes-1, f, v);

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

int existFaturacao(AVL fat, char* produto)
{
	int r = 0;

	if(fat != NULL)
	{
		int equal = strcmp(getProdFatura(getFatura(fat)), produto);

		if(!equal)
			r++;

		else
		{	
			if(equal > 0)
				r += existFaturacao(getEsq(fat), produto);
			else
				r += existFaturacao(getDir(fat), produto);
		}
	}

	return r;
}

void recursive_query4(FAT_FILIAL fat, AVL produtos, AVL* produtoFilial1, AVL* produtoFilial2, AVL* produtoFilial3)
{
	if(produtos != NULL)
	{
		getTag(produtos)[6] = '\0';
		
		if( !existFaturacao(getFaturacao(fat, 0), getTag(produtos)) && !exist_element(*produtoFilial1, getTag(produtos)) )
			*produtoFilial1 = updateAVL(*produtoFilial1, NULL, NULL, NULL, getTag(produtos), 1);	

		else
		{	
			if( !existFaturacao(getFaturacao(fat, 1), getTag(produtos)) && !exist_element(*produtoFilial2, getTag(produtos)) )
				*produtoFilial2 = updateAVL(*produtoFilial2, NULL, NULL, NULL, getTag(produtos), 1);	
			
			else
				if( !existFaturacao(getFaturacao(fat, 2), getTag(produtos)) && !exist_element(*produtoFilial3, getTag(produtos)) )
					*produtoFilial3 = updateAVL(*produtoFilial3, NULL, NULL, NULL, getTag(produtos), 1);	
				
		}

		recursive_query4(fat, getEsq(produtos), produtoFilial1, produtoFilial2, produtoFilial3);
		recursive_query4(fat, getDir(produtos), produtoFilial1, produtoFilial2, produtoFilial3);		
	}
}

void query4(FAT_FILIAL fat, AVL produtos)
{
	AVL* produtoFilial1 = malloc(sizeof(AVL));
	AVL* produtoFilial2 = malloc(sizeof(AVL));
	AVL* produtoFilial3 = malloc(sizeof(AVL));
	
	*produtoFilial1 = NULL;
	*produtoFilial2 = NULL;
	*produtoFilial3 = NULL;

	recursive_query4(fat, produtos, produtoFilial1, produtoFilial2, produtoFilial3);

	printf("%d\n", inorder_avl_just_tag(*produtoFilial1));

}

/*-----------------------------------------------------------------------*/

int exist_elementFilial (AVL a, char *element) {
 
    int r = 0;

    while (a != NULL) {

        r = strcmp(getClienteFilial(getGestaoFilial(a)), element);

        if (r == 0) return 1;
        else if (r > 0) return exist_elementFilial(getDir(a), element);
        else if (r < 0) return exist_elementFilial(getEsq(a), element);
    }

    return 0;
}

AVL recursive_query5(FILIAL filial, AVL clientes, AVL *compramEmTodas){

    if(clientes != NULL)
    {

        if (exist_elementFilial(getAVLfilial(filial,1), getTag(clientes)) == 0 &&
       	 	exist_elementFilial(getAVLfilial(filial,2), getTag(clientes)) == 0 &&
        	exist_elementFilial(getAVLfilial(filial,3), getTag(clientes)) == 0) 
        	*compramEmTodas = updateAVL (*compramEmTodas, NULL, NULL, NULL, getTag(clientes), 0);

        *compramEmTodas = recursive_query5(filial, getEsq(clientes), compramEmTodas);
        *compramEmTodas = recursive_query5(filial, getDir(clientes), compramEmTodas);
    }

    return *compramEmTodas;
}


void query5(FILIAL filial, AVL clientes) {

    AVL compramEmTodas = NULL; 

    compramEmTodas = recursive_query5(filial, clientes, &compramEmTodas);

    printf("\nClientes que compraram em todas as filiais:\n");

    int r = inorder_avl_just_tag(compramEmTodas); 

    printf("\n>> Existem %d clientes que comraram em todas as filiais.\n", r);
}



/*-----------------------------------------------------------------------*/

int existeProdutoNaAVLFilial (AVL a, char* elem) {
	
	int cmp;
	
	if (a != NULL) {

		cmp = strcmp(elem, getProdFatura(getFatura(a)));

		if (cmp==0) return 1;
		else if (cmp > 0) 
			return (existeProdutoNaAVLFilial(getDir(a), elem));
		else return (existeProdutoNaAVLFilial(getEsq(a), elem));
	}

	return 0;
}

void produtosQuery6 (FAT_FILIAL fat, AVL produtos, int *produtosNC) {

	if (produtos != NULL) {
		
		char *aux;
		aux = strdup(getTag(produtos));
		aux[6]='\0';

		if (!existeProdutoNaAVLFilial(getFaturacao(fat, 0), aux) &&
			!existeProdutoNaAVLFilial(getFaturacao(fat, 1), aux) &&
			!existeProdutoNaAVLFilial(getFaturacao(fat, 2), aux)) {
			*produtosNC += 1;
		}

		produtosQuery6(fat, getEsq(produtos), produtosNC);
		produtosQuery6(fat, getDir(produtos), produtosNC);
	}
}

int existeClienteNaAVLFilial (AVL a, char* elem) {

	int r;

	if (a != NULL) {

		r = strcmp(elem, getClienteFilial(getGestaoFilial(a)));

		if (r==0) return 1;
		else if (r > 0) return existeClienteNaAVLFilial(getDir(a), elem);
		else return existeClienteNaAVLFilial(getEsq(a), elem);

	}

	return r;
}

void clientesQuery6 (FILIAL fil, AVL clientes, int *clientesSC) {

	if (clientes != NULL) {

		if (!existeClienteNaAVLFilial(getAVLfilial(fil, 1), getTag(clientes)) &&
			!existeClienteNaAVLFilial(getAVLfilial(fil, 2), getTag(clientes)) &&
			!existeClienteNaAVLFilial(getAVLfilial(fil, 3), getTag(clientes))) {
			*clientesSC += 1;
		}

		clientesQuery6(fil, getEsq(clientes), clientesSC);
		clientesQuery6(fil, getDir(clientes), clientesSC);
	}

}

void query6 (FAT_FILIAL fat, FILIAL fil, AVL produtos, AVL clientes) {

	int *clientesSemCompras = (int*) malloc(sizeof(int));
	int *produtosNaoComprados = (int*) malloc(sizeof(int));

	*clientesSemCompras = 0;
	*produtosNaoComprados = 0;

	clientesQuery6(fil, clientes, clientesSemCompras);

	produtosQuery6(fat, produtos, produtosNaoComprados);

	printf("Existem %d clientes que não realizaram compras.\n", 
			*clientesSemCompras);
	printf("Existem %d produtos que não foram comprados.\n", 
			*produtosNaoComprados);
}

/*-----------------------------------------------------------------------*/

void recursive_query7 (AVL vendas, char* cliente, int** nProd) {

	if (vendas != NULL) {

		if (strcmp(getCodCliente(vendas), cliente) == 0) {

			nProd[getMes(vendas)-1][getFilial(vendas)-1] += getQuantidade(vendas);
		}

		recursive_query7(getEsq(vendas), cliente, nProd);		
		recursive_query7(getDir(vendas), cliente, nProd);

	}
}

void query7(AVL vendas, char* cliente){

	int** nProd = (int**) malloc(sizeof(int*) * 12);

	int i = 0, j = 0;

	for (i = 0; i < 12; i++){
		nProd[i]  = malloc(sizeof(int)*3);
		for (j = 0; j < 3; j++){
			nProd[i][j] = 0;
		}
	}

	recursive_query7(vendas, cliente, nProd);

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

/*-----------------------------------------------------------------------*/

void recursive_query8(AVL fat, int min, int max, float* faturacao, int* total_vendas)
{
	if(fat != NULL)
	{
		int i,j;

		for(i = 0; i < 2; i++)
			for(j = 0; j < 12; j++)
				if(j >= min && j <= max)
				{
					*faturacao +=  getFatMes(getFatura(fat))[i][j];
					*total_vendas +=  getNumVendas(getFatura(fat))[i][j];
				}
		
		recursive_query8(getEsq(fat), min, max, faturacao, total_vendas);
		recursive_query8(getDir(fat), min, max, faturacao, total_vendas);
	}
}


void query8(FAT_FILIAL fat, int min, int max)
{
	float *faturacao = (float*) malloc(sizeof(float*));
	int *total_vendas = (int*) malloc(sizeof(int*));
	*faturacao = 0.0;
	*total_vendas = 0;

	recursive_query8(getFaturacao(fat, 0), min-1, max-1, faturacao, total_vendas);
	
	recursive_query8(getFaturacao(fat, 1), min-1, max-1, faturacao, total_vendas);

	recursive_query8(getFaturacao(fat, 2), min-1, max-1, faturacao, total_vendas);

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

/* QEWRUY 9 TESTING
int matrizAzeros (float **f, int flag) {

	int l, c;

	switch (flag) {

		case 1:
			for (l = 0; l < 2; l++)
				for (c = 0; c < 12; c++)
					if (f[l][c]!=0) return 0;
			break; 
		case 2:
			for (l = 0; l < 2; l++)
				for (c = 0; c < 12; c++)
					if (f[l][c]!=0) return 0;
			break;
	}

	return 1;
}

void geraClientesFilial (AVL fil, char *codProd, LString comprasN, LString comprasP) {

	if (fil != NULL) {

			if (existeNaLista(codProd, getFatMes(getList(getGestaoFilial(fil)))) {

				if (matrizAzeros(getFatMes(getGestaoFilial(fil))), 1) {

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

/*______________________________________________________________________*/

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

/*______________________________________________________________________*/

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

/*______________________________________________________________________*/

LString recursive_query12 (AVL vendas, char* cliente, LString produtos) {

	if (vendas != NULL) {

		if (strcmp(getCodCliente(vendas), cliente) == 0) {

			produtos = insertLString(produtos, getCodProd(vendas), getQuantidade(vendas), getPreco(vendas)); 
			
		}

		produtos = recursive_query12(getEsq(vendas), cliente,produtos);		
		produtos = recursive_query12(getDir(vendas), cliente,produtos);

	}

	return produtos;
}

void query12 (AVL vendas, char* cliente){

	LString produtos = NULL;

	produtos = recursive_query12(vendas, cliente, produtos);

	produtos = quickSortL (produtos, 1);

	printLString(produtos, 1);
	
}

/*______________________________________________________________________*/


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

/*MACRO para suprimir warnings de strdup do <string.h>*/
#define _GNU_SOURCE

/*_________________BIBLIOTECAS STD IMPORTADAS________________________*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*_________________BIBLIOTECAS IMPLEMENTADAS____________________________*/

#include "avlstruct.h"
#include "stack.h"
#include "global.h"
#include "lstring.h"
#include "arrayList.h"
#include "hashtables.h"

/*______________________________________________________________________*/

void query1 (GLOBAL set) {

	printf("\nNúmero de produtos validados   : %d.\n", set->val_prods);
	printf("Número de clientes validados   : %d.\n" , set->val_clients);
	printf("Vendas válidas                 : %d.\n", set->val_sells);
	
	printf("\nOutros:\n");
	printf("\nLinha mais longa venda         : %d\n", set->max_line_sells);
	printf("Número de produtos inválidos   : %d\n", set->num_prods-set->val_prods);
	printf("Número de clientes inválidos   : %d\n", set->num_clients-set->val_clients);
	printf("Número de vendas   inválidas   : %d\n\n", set->num_sells-set->val_sells);
}

Stack* recursive_query2 (AVL produtos, Stack *s, char c) {

	if (produtos != NULL) 
	{
		
		if (c == produtos->tag[0]) 
		{
			s = push(s, produtos->tag); 
			
			s = recursive_query2(produtos->right, s, c);
			s = recursive_query2(produtos->left, s, c); 
			
		}
		
		else
		{
			if ( c < produtos->tag[0] )
				s = recursive_query2(produtos->left, s, c);			
		
			else
				s = recursive_query2(produtos->right, s, c);
		}
	}

	return s;
}

void query2 (AVL produtos, char c) {

	Stack *s = NULL;
	s = initStack(s, 10000);
	
	s = recursive_query2(produtos, s, c);

	printStack(s);

	printf("\nNúmero total de produtos com letra %c: %d.\n", c, s->sp);

	freeStack(s);
}

void recursive_query3 (AVL vendas, char* prod, 
					   int mes, int** n_vendas, 
					   float** faturacao) {
	int month, sold, filial;
	char tipo;
	double price;


	if (vendas != NULL) {
	
		char **campos = (char**) malloc(sizeof(char*) * CAMPOS_SELLS);
	
		campos = tokenize (campos, vendas -> tag);
		month = atoi(campos[6]);
		
		if (!strcmp(campos[1], prod) && mes == month) {
			
			sscanf(campos[2], "%lf", &price);
			sold = atoi (campos[3]);
			filial = atoi(campos[7]);
			tipo = campos[4][0];

			switch (tipo) {
				case 'P': n_vendas[0][filial-1]++;
						  faturacao[0][filial-1]+=sold*price;
						  break;
				case 'N': n_vendas[1][filial-1]++;
						  faturacao[1][filial-1]+=sold*price;
						  break;
				default: break;
			}

		}
	
		free(campos);		

		recursive_query3(vendas->left, prod, mes, n_vendas, faturacao);
		recursive_query3(vendas->right, prod, mes, n_vendas, faturacao);
	}

}

void showStatPorFilial_query3 (int **n_vendas, float** faturacao) {

	int l, c;

	printf("-> Faturação por Filial: \n\n");
	
	printf("   1   2   3     (Filial)\n");
	for (l = 0; l < 2; l++) {
		if (l == 0) printf("P: ");
		if (l == 1) printf("N: ");
		for (c = 0; c < 3; c++) {
			printf("%.3f | ", faturacao[l][c]);
		}
		printf("\n");
	}
	
	printf("\n-> Número de vendas por Filial: \n\n");
	
	printf("   1   2   3     (Filial)\n");
	for (l = 0; l < 2; l++) {
		if (l == 0) printf("P: ");
		if (l == 1) printf("N: ");
		for (c = 0; c < 3; c++) {
			printf("%d | ", n_vendas[l][c]);
		}
		printf("\n");
	}

}

void showStatGlobal_query3 (int **n_vendas, float** faturacao) {

	int l, c;
	int globalVendas[2][1];
	float globalFat[2][1];

	printf("\n\nFaturação total das Filiais: \n\n");
	for (l = 0; l < 2; l++) {
		if (l == 0) printf("P: ");
		if (l == 1) printf("N: ");
		for (c = 0; c < 1; c++) {
			globalFat[l][c] = faturacao[l][0] + faturacao[l][1] + faturacao[l][2];
			printf("%.3f | ", globalFat[l][c]);
		}
		printf("\n");
	}
	
	printf("\nNúmero de vendas totais das Filiais: \n\n");
	for (l = 0; l < 2; l++) {
		if (l == 0) printf("P: ");
		if (l == 1) printf("N: ");
		for (c = 0; c < 1; c++) {
			globalVendas[l][c] = n_vendas[l][0] + n_vendas[l][1] + n_vendas[l][2];
			printf("%d | ", globalVendas[l][c]);
		}
		printf("\n");
	}

}

void query3 (AVL vendas, int mes, char *produto, int opcao) {
	
	int l, c;
	
	float **faturacao = (float**) malloc(sizeof(float*) * 2);
	int   **n_vendas  = (int**)   malloc(sizeof(int*)   * 2);
	
	for (l = 0; l < 2; l++) {
	
		n_vendas[l]  = malloc(sizeof(int)*3);
		faturacao[l] = malloc(sizeof(float)*3);

		for (c = 0; c < 3; c++) {
			n_vendas[l][c]  = 0;
			faturacao[l][c] = 0.0;
		}
	}

	recursive_query3(vendas, produto, mes, n_vendas, faturacao);

	switch(opcao) {
		case 1:	
			showStatGlobal_query3(n_vendas, faturacao);
			break;
		case 0: 
			showStatPorFilial_query3(n_vendas, faturacao);
			break;
		default: break; 
	}

	free(n_vendas);

}

void recursive_query8(int min, int max, AVL vendas, float* faturacao, int* total_vendas)
{
	if(vendas != NULL) 
	{
		char **campos = (char**) malloc(sizeof(char*) * CAMPOS_SELLS);
		int month, sold;
		double price;
	
		campos = tokenize (campos, vendas -> tag);
		month = atoi(campos[6]);

		if(month >= min && month <= max)
		{
			sscanf(campos[2], "%lf", &price);
			sold = atoi (campos[3]);

			*faturacao += sold*price;
			*total_vendas+=1;  
		}

		free(campos);

		recursive_query8(min, max, vendas -> left, faturacao, total_vendas);
		recursive_query8(min, max, vendas -> right, faturacao, total_vendas);

	}
}

void query8(int min, int max, AVL vendas)
{
	
	float *faturacao = (float*) malloc(sizeof(float*));
	int *total_vendas = (int*) malloc(sizeof(int*));
	*faturacao = 0.0;
	*total_vendas = 0;

	recursive_query8(min, max, vendas, faturacao, total_vendas);

	printf("\nFaturação entre os meses %d e %d\n", min, max);
	printf("%f\n", *faturacao);

	printf("\nNumero de vendas entre os meses %d e %d\n", min, max);
	printf("%d\n", *total_vendas);

}

void recursive_query9 (AVL vendas, char* prod, int filial, Stack* clientesN, Stack* clientesP) {
	
	int filial_prova;
	char* prod_prova;
	char tipo;
	char* cliente;

	if (vendas != NULL) {
		
		char **campos = (char**) malloc(sizeof(char*) * CAMPOS_SELLS);
	
		campos = tokenize (campos, vendas -> tag);
		filial_prova = atoi(campos[7]);
		prod_prova = campos[1];
		tipo = campos[4][0];
		cliente = campos[5];

		if (!strcmp(prod, prod_prova) && filial_prova == filial) 
		{
			if (tipo == 'N') clientesN = push(clientesN, cliente); 			

			if (tipo == 'P') clientesP = push(clientesP, cliente); 
			
			recursive_query9(vendas -> right, prod, filial, clientesP, clientesN);
			recursive_query9(vendas -> left, prod, filial, clientesP, clientesN); 
		}

		else
		{

			if ( prod < prod_prova )
				recursive_query9(vendas -> left, prod, filial, clientesP, clientesN);		
		
			else
				recursive_query9(vendas -> right, prod, filial, clientesP, clientesN);
		}
	}
}

void query9 (AVL vendas, char* produto, int filial){

	Stack* clientesP = NULL;
	Stack* clientesN = NULL;
	
	clientesP = initStack(clientesP, 10000);
	clientesN = initStack(clientesN, 10000);

	recursive_query9(vendas, produto, filial, clientesP, clientesN);

	printf("\nN: \n");
	printStack(clientesN);
	printf("\nP: \n");
	printStack(clientesP);

	freeStack(clientesP);
	freeStack(clientesN);
}

LString recursive_query10 (AVL vendas, char* cliente, int mes, LString produtos) {

	int mes_prova;
	char *cliente_prova;
	char *produto_prova;

	if (vendas != NULL) {
	
		char **campos = (char**) malloc(sizeof(char*) * CAMPOS_SELLS);
	
		campos = tokenize (campos, vendas -> tag);
		mes_prova = atoi(campos[6]);
		cliente_prova = strdup(campos[5]);
		produto_prova = strdup(campos[1]);
		
		if (strcmp(cliente_prova, cliente) == 0 && mes == mes_prova)
			produtos = insertLString (produtos,produto_prova);

		free(campos);

		produtos = recursive_query10(vendas -> left, cliente, mes, produtos);		
		produtos = recursive_query10(vendas -> right, cliente, mes, produtos);

	}

	return produtos;
}

void query10 (AVL vendas, char* cliente, int mes){

	LString l = NULL;

	l = recursive_query10(vendas, cliente, mes, l);

	l = quickSortL(l);

	printLString(l);
}

void recursive_query11(AVL vendas, HEAD_TABLE h) {

	if (vendas != NULL) {

		update(h, getCodProd(vendas), 
				  getFilial(vendas), 
				  getQuantidade(vendas));
		
		recursive_query11(getEsq(vendas),  h);
		recursive_query11(getDir(vendas), h);
	}
}

void query11 (AVL vendas) {
	
	HEAD_TABLE h = NULL;

	h = initTable(h, 200000);
	
	recursive_query11(vendas, h);

	int filial = 2, n = 5;

	quicksort(h, 0, h->hsize, filial);

	printf("%d produtos mais comprados: \n\n", n);

	printNfirstTableReverse(h, n);

	free_hashtable(h);
}
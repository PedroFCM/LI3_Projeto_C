#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "avlstruct.h"

#include "stack.h"
#include "global.h"

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

	printf("%d\n", s->sp);
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

	printf("-> Faturação total das Filiais: \n\n");
	for (l = 0; l < 2; l++) {
		if (l == 0) printf("P: ");
		if (l == 1) printf("N: ");
		for (c = 0; c < 1; c++) {
			globalFat[l][c] = faturacao[l][0] + faturacao[l][1] + faturacao[l][2];
			printf("%.3f | ", globalFat[l][c]);
		}
		printf("\n");
	}
	
	printf("\n-> Número de vendas totais das Filiais: \n\n");
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

void query3 (AVL vendas, int mes, char *produto) {
	
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

	showStatGlobal_query3(n_vendas, faturacao);

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
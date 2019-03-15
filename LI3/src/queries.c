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

			printf("\n%s\n", vendas->tag);			 
			printf("%c", tipo);
			printf(" %d\n", filial);

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

	printf("__________Faturação__________\n\n");
	
	for (l = 0; l < 2; l++) {
		for (c = 0; c < 3; c++) {
			printf("%.3f | ", faturacao[l][c]);
		}
		printf("\n");
	}
	
	printf("\n________Número de vendas________\n\n");
	
	printf("   1   2   3   <- Filial\n");
	for (l = 0; l < 2; l++) {
		if (l == 0) printf("P: ");
		if (l == 1) printf("N: ");
		for (c = 0; c < 3; c++) {
			printf("%d | ", n_vendas[l][c]);
		}
		printf("\n");
	}

	free(n_vendas);

}
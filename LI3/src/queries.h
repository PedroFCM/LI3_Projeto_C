#ifndef _QUERIES_
#define _QUERIES_

#include "stack.h"

void query1 (GLOBAL set);

Stack* recursive_query2 (AVL produtos, Stack *s, char c);

void query2 (AVL produtos, char c);

void query3 (AVL vendas, int mes, char *produto, int opcao);

void recursive_query3 (AVL vendas, char* prod, 
					   int mes, int**n_vendas, 
					   float** faturacao);

void showStatGlobal_query3 (int **n_vendas, float** faturacao);

void recursive_query8(int min, int max, AVL vendas, float* faturacao, int* total_vendas);

void showStatPorFilial_query3 (int **n_vendas, float** faturacao);

void query8(int min, int max, AVL vendas);

void recursive_query9 (AVL vendas, char* prod, int filial, Stack* clientesN, Stack* clientesP);

void query9 (AVL vendas, char* produto, int filial);

#endif
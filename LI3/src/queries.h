#ifndef _QUERIES_
#define _QUERIES_

#include "stack.h"

Stack* recursive_query2 (AVL produtos, Stack *s, char c);

void query2 (AVL produtos, char c);

void query3 (AVL vendas, int mes, char *produto);

void recursive_query3 (AVL vendas, char* prod, 
					   int mes, int**n_vendas, 
					   float** faturacao);
#endif
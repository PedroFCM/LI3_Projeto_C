
/** @file queries.h
*	@brief Header file de queries.c
*
*	@autor João Pedro Rodrigues Azevedo (A85227) 
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@bug Nenhum que tivessemos reparado.
*	
*/

#ifndef _QUERIES_
#define _QUERIES_

/*_________________BIBLIOTECAS IMPLEMENTADAS____________________________*/

#include "stack.h"
#include "lstring.h"
#include "hashtables.h"

/*______________________________________________________________________*/

void query1 (GLOBAL set);

LISTA_PROD query2 (LISTA_PROD ls, AVL produtos, char c);

void query3 (AVL vendas, int mes, char *produto, int opcao);

void showStatGlobal_query3 (int **n_vendas, float** faturacao);

void showStatPorFilial_query3 (int **n_vendas, float** faturacao);

void query8(int min, int max, AVL vendas);

void query9 (AVL vendas, char* produto, int filial);

LString recursive_query10 (AVL vendas, char* cliente, int mes, LString produtos);

void query10 (AVL vendas, char* cliente, int mes);

void recursive_query11(AVL vendas, HEAD_TABLE h);

void query11 (AVL vendas, int n);

LString recursive_query12 (AVL vendas, char* cliente, LString produtos);

void query12 (AVL vendas, char* cliente);

void query5(AVL vendas);

void query7(AVL vendas, char* cliente);

void recursive_query7 (AVL vendas, char* cliente, int** nProd);

#endif
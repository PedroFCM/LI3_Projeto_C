
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

/*-----------------------------------------------------------------------*/

#ifndef _QUERIES_
#define _QUERIES_

/*_________________BIBLIOTECAS IMPLEMENTADAS____________________________*/

#include "stack.h"
#include "lstring.h"
#include "hashtables.h"
#include "Faturacao.h"
#include "Filial.h"

/*-----------------------------------------------------------------------*/

typedef float** FAT_PRECO;

typedef int** FAT_QUANT;

/*-----------------------------------------------------------------------*/

void query1 (GLOBAL set);

/*-----------------------------------------------------------------------*/

LISTA_PROD query2 (LISTA_PROD ls, AVL produtos, char c);

/*-----------------------------------------------------------------------*/

void showStatGlobal(VENDAS n_vendas, FAT_MES faturacao);
void showStatPorFilial(VENDAS n_vendas, FAT_MES faturacao);
void query3 (FAT_FILIAL fat, int mes, char *produto, int opcao);

/*-----------------------------------------------------------------------*/

void query4(FAT_FILIAL fat, AVL produtos, int opcao);

/*-----------------------------------------------------------------------*/

void query5(FILIAL filial, AVL clientes);

/*-----------------------------------------------------------------------*/

int existeProdutoNaAVLFilial (AVL filial, char* elem);
void produtosSemCompras (FAT_FILIAL fat, AVL produtos, int *produtosNC);
void query6 (FAT_FILIAL fat, FILIAL fil, AVL produtos, AVL clientes);

/*-----------------------------------------------------------------------*/

void query7(FILIAL filial, char* cliente);

/*-----------------------------------------------------------------------*/

void query8(FAT_FILIAL fat, int min, int max);

/*-----------------------------------------------------------------------*/

/*void query9 (AVL vendas, char* produto, int filial);*/

int matrizAzeros (float **f, int flag);
LString geraClientesFilial (AVL fil, char *codProd, LString *compras, char tipo);
void query9 (FILIAL fil, char *codProd, int filial);


/*-----------------------------------------------------------------------*/

void query10(FILIAL filial, char* cliente, int mes);
void recursive_query10(AVL filial, AVL* prodMaisComprad, char* cliente, int mes);

/*-----------------------------------------------------------------------*/

void recursive_query11(AVL vendas, HEAD_TABLE h);
void query11 (AVL vendas, int n);

/*-----------------------------------------------------------------------*/

void query12 (FILIAL filial, char* cliente);

/*-----------------------------------------------------------------------*/

#endif
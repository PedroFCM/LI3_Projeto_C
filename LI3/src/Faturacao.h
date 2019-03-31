
/** @file Faturacao.h
*	@brief Ficheiro header de .
*
*	@autor João Pedro Rodrigues Azevedo (A85227) 
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@bug Nenhum que tivessemos reparado.
*	
*/

#ifndef _FATURACAO_
#define _FATURACAO_

/*_________________BIBLIOTECAS IMPLEMENTADAS____________________________*/

#include "avlstruct.h"

#define F1 0
#define F2 1
#define F3 2

/*______________________________________________________________________*/

typedef struct faturacao *FAT_FILIAL;

typedef struct fatura *FATURA;

typedef float** FAT_MES;

typedef int** VENDAS;

typedef struct avl *AVL;

/*______________________________________________________________________*/

void printFaturacao (AVL fat);

void printMATRIX (FAT_MES f, VENDAS v, int opcao);

void initFatura (FAT_MES f, VENDAS v);

void setFatMes (FATURA f, int l, int c, double val);

void setVendas (FATURA f, int l, int c);

VENDAS getNumVendas (FATURA f);

FAT_MES getFatMes (FATURA f);

void initMatriz(FATURA fat, FAT_MES f,VENDAS v);

char* getProdFatura (FATURA f);

void printFaturacao (AVL fat);

AVL getFaturacao (FAT_FILIAL f, int filial);

char* getProdFatura (FATURA f);

void insereNaFatura (FATURA f, double preco, int quant, char modo, int mes);

void insereProdFat (int filial, AVL *fatFilial, AVL vendas);

FAT_FILIAL initFaturacao (FAT_FILIAL nova, AVL prod, AVL vendas);

void updateFatura (AVL fatFilial, AVL vendas, char *p, int *r);

void setProdFatura (char* p, FATURA f);

/*______________________________________________________________________*/

#endif
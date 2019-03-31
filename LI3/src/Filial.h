
/** @file Filial.h
*	@brief Ficheiro header para o Filial.c.
*
*	@autor João Pedro Rodrigues Azevedo (A85227) 
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@bug Nenhum que tivessemos reparado.
*	
*/

#ifndef _FILIAL_
#define _FILIAL_

/*_________________BIBLIOTECAS IMPLEMENTADAS____________________________*/

#include "avlstruct.h"

typedef struct filial *FILIAL;

typedef struct fatura *FATURA;

typedef float** FAT_MES;

typedef int** VENDAS;

typedef struct avl *AVL;

typedef struct gestaoFilial* GESTAO_FILIAL;

typedef struct elementos* ELEM;

void initFaturaFilial (GESTAO_FILIAL new);

void setSizeGF (GESTAO_FILIAL f, int new_size);

GESTAO_FILIAL setClienteFilial (char *c, GESTAO_FILIAL* g);

void initMatrizFilial(GESTAO_FILIAL fat, FAT_MES f,VENDAS v, int prod);

int getSizeGF(GESTAO_FILIAL filial);

char* getProdFilial (GESTAO_FILIAL filial, int i);

void setFatFilial (GESTAO_FILIAL g, int prod, int l, int c, double val);

void setVendasFilial (GESTAO_FILIAL g, int prod, int l, int c);

void pushProdutoFilial (char *p, GESTAO_FILIAL filial);

char* getClienteFilial(GESTAO_FILIAL filial);

FILIAL initFilial (FILIAL nova, AVL clientes, AVL vendas);

void insereClienteFat (int fi, AVL *filial, AVL vendas);

void updateGestaoFilial (AVL filial, AVL vendas, char *c, int *r);

void insereNaFilial (GESTAO_FILIAL filial, char *p, char modo, float preco, int quant, int mes);

#endif
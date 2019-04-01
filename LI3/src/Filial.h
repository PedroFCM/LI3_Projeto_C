
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

int existeNaLista (char* elem, ELEM l);

ELEM pushLista (ELEM l, char* elem, char modo, int quant, float preco, int mes);

void updateGestaoFilial (AVL filial, AVL vendas, char *c, int *r);

AVL* insereClienteFat (int fi, AVL *filial, AVL vendas);

FILIAL initFilial (FILIAL nova, AVL clientes, AVL vendas);

void initFaturaFilial (FAT_MES f, VENDAS v);

void initMatrizFilial(ELEM elem, FAT_MES f, VENDAS v);

GESTAO_FILIAL setClienteFilial (char *c, GESTAO_FILIAL *g);

char* getProdFilial (GESTAO_FILIAL filial, int i);

void setList(AVL filial, ELEM l);

void setFatFilial (ELEM elem, int l, int c, double val);

void setVendasFilial (ELEM elem, int l, int c);

char* getClienteFilial(GESTAO_FILIAL filial);

ELEM getList(GESTAO_FILIAL g);

#endif

/** @file Filial.h
*	@brief Ficheiro header para o Filial.c.
*
*	@autor João Pedro Rodrigues Azevedo
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
#include "stack.h"
#include "hashtables.h"
#include "lstring.h"

/*---------------------------------------------------------------------------------------------*/

typedef struct filial *FILIAL;

typedef struct fatura *FATURA;

typedef float** FAT_MES;

typedef int** VENDAS;

typedef struct avl *AVL;

typedef struct gestaoFilial* GESTAO_FILIAL;

typedef struct elementos* ELEM;

/*-----------------------------------------------------------------------*/

void acumVendas(AVL filial, AVL *prodMaisComprad, int mes);

/*-----------------------------------------------------------------------*/

AVL compraramEmTodas(FILIAL filial, AVL clientes, AVL *compramEmTodas);

/*-----------------------------------------------------------------------*/

void clientesSemCompra (FILIAL fil, AVL clientes, int *clientesSC);

/*-----------------------------------------------------------------------*/

int existeClienteNaAVLFilial (AVL a, char* elem);

/*-----------------------------------------------------------------------*/

FAT_MES getFatMesElem (ELEM elem);

/*-----------------------------------------------------------------------*/

float sumatorioMatriz(float **matriz);

/*-----------------------------------------------------------------------*/

int** tabelaComprasFilial (AVL filial, char* cliente, int** nProd, int flag);

/*-----------------------------------------------------------------------*/

LString top3Compras_do_cliente (AVL filial, char* cliente, LString produtos);

/*-----------------------------------------------------------------------*/

LString recursividade (ELEM elem, LString l);

/*-----------------------------------------------------------------------*/

AVL getAVLfilial (FILIAL f, int fi);

/*-----------------------------------------------------------------------*/

int existeNaLista (char* elem, ELEM l);

/*-----------------------------------------------------------------------*/

ELEM pushLista (ELEM l, char* elem, char modo, int quant, float preco, int mes);

/*-----------------------------------------------------------------------*/

void updateGestaoFilial (AVL filial, AVL vendas, char *c, int *r);

/*-----------------------------------------------------------------------*/

void insereClienteFat (int fi, AVL *filial, AVL vendas);

/*-----------------------------------------------------------------------*/

FILIAL initFilial (FILIAL nova, AVL clientes, AVL vendas);

/*-----------------------------------------------------------------------*/

void initFaturaFilial (FAT_MES f, VENDAS v);

/*-----------------------------------------------------------------------*/

void initMatrizFilial(ELEM elem, FAT_MES f, VENDAS v);

/*-----------------------------------------------------------------------*/

void setClienteFilial (char *c, GESTAO_FILIAL g);

/*-----------------------------------------------------------------------*/

char* getProdFilial (GESTAO_FILIAL filial, int i);

/*-----------------------------------------------------------------------*/

void setList(AVL filial, ELEM l);

/*-----------------------------------------------------------------------*/

void setFatFilial (ELEM elem, int l, int c, double val);

/*-----------------------------------------------------------------------*/

void setVendasFilial (ELEM elem, int l, int c, int quant);

/*-----------------------------------------------------------------------*/

char* getClienteFilial(GESTAO_FILIAL filial);

/*-----------------------------------------------------------------------*/

ELEM getList(GESTAO_FILIAL g);

/*-----------------------------------------------------------------------*/

void printFilial (AVL filial);

/*-----------------------------------------------------------------------*/

void printElem(ELEM elemenos);

/*-----------------------------------------------------------------------*/

void printMATRIXFilial (FAT_MES f, VENDAS v, int opcao);

/*-----------------------------------------------------------------------*/

void somaMatrizes(int **nProd, int **atual, int flag);

/*-----------------------------------------------------------------------*/

void somaVendas(int **nProd, ELEM elem, int flag);

/*-----------------------------------------------------------------------*/

VENDAS getNumVendasElem (ELEM elem);

/*-----------------------------------------------------------------------*/

void procuraNaFilial (AVL vendas, int filial[], char* cliente);

/*-----------------------------------------------------------------------*/

int exist_elementFilial (AVL a, char *element);

/*-----------------------------------------------------------------------*/

void compraramNaFilial (AVL vendas, char* prod, int filial, Stack clientesN, Stack clientesP);

/*-----------------------------------------------------------------------*/

void juntaQuantFilial (HEAD_TABLE h);

/*-----------------------------------------------------------------------*/

char* getProdutoFilial(ELEM filial);

/*-----------------------------------------------------------------------*/

int sumatorioMatrizInt(int **matriz);

/*-----------------------------------------------------------------------*/

void updateQuantidadesProduto(ELEM l, HEAD_TABLE h, int flag);

#endif
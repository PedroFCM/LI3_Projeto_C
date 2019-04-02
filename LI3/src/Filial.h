
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
#include "stack.h"
#include "hashtables.h"

/*---------------------------------------------------------------------------------------------*/

typedef struct filial *FILIAL;

typedef struct fatura *FATURA;

typedef float** FAT_MES;

typedef int** VENDAS;

typedef struct avl *AVL;

typedef struct gestaoFilial* GESTAO_FILIAL;

typedef struct elementos* ELEM;

AVL getAVLfilial (FILIAL f, int fi);

int existeNaLista (char* elem, ELEM l);

ELEM pushLista (ELEM l, char* elem, char modo, int quant, float preco, int mes);

void updateGestaoFilial (AVL filial, AVL vendas, char *c, int *r);

void insereClienteFat (int fi, AVL *filial, AVL vendas);

FILIAL initFilial (FILIAL nova, AVL clientes, AVL vendas);

void initFaturaFilial (FAT_MES f, VENDAS v);

void initMatrizFilial(ELEM elem, FAT_MES f, VENDAS v);

void setClienteFilial (char *c, GESTAO_FILIAL g);

char* getProdFilial (GESTAO_FILIAL filial, int i);

void setList(AVL filial, ELEM l);

void setFatFilial (ELEM elem, int l, int c, double val);

void setVendasFilial (ELEM elem, int l, int c, int quant);

char* getClienteFilial(GESTAO_FILIAL filial);

ELEM getList(GESTAO_FILIAL g);

void printFilial (AVL filial);

void printElem(ELEM elemenos);

void printMATRIXFilial (FAT_MES f, VENDAS v, int opcao);

void somaMatrizes(int **nProd, int **atual, int flag);

void somaVendas(int **nProd, ELEM elem, int flag);

VENDAS getNumVendasElem (ELEM elem);

/*---------------------------------------------------------------------------------------------*/

/** @brief Função que gera uma matriz filial.
 *         Se a matriz estiver toda a 1 então o cliente comprou nas 3 filiais
 *
 *  @param vendas AVL de vendas para procura.
 *  @param filial matriz de verificacao.
 *  @param cliente string contendo o cliente de pesquisa.
 *  @return void.
 */

void procuraNaFilial (AVL vendas, int filial[], char* cliente);


/** @brief Função que gera a faturacao entre dois meses.
 *
 *  @param f Faturacao.
 *  @param min Mes inferior.
 *  @param max Mes superior.
 *  @param vendas AVL de vendas.
 *  @return void.
 */

void compraramEmTodas (AVL vendas, AVL* clie_filiais);


/** @brief Função que gera a faturacao entre dois meses.
 *
 *  @param f Faturacao.
 *  @param min Mes inferior.
 *  @param max Mes superior.
 *  @param vendas AVL de vendas.
 *  @return void.
 */

void compraramNaFilial (AVL vendas, char* prod, int filial, Stack clientesN, Stack clientesP);


/** @brief Função que adiciona uma nova quantidade a uma filial.
 *
 *  @param h HashTable cabeçalho.
 *  @return void.
 */

void juntaQuantFilial (HEAD_TABLE h);

#endif
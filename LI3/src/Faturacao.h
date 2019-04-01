
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

/* MACRO para float** */
typedef float** FAT_PRECO;
/* MACRO para int** */
typedef int** FAT_QUANT;

/*typedef para uma faturação*/
typedef struct listagem* FAT;

typedef struct faturacao *FAT_FILIAL;

typedef struct fatura *FATURA;

typedef float** FAT_MES;

typedef int** VENDAS;

/*______________________________________________________________________*/

/** @brief Função que imprime.
 *
 *  @param f Faturacao.
 *  @param min Mes inferior.
 *  @param max Mes superior.
 *  @param vendas AVL de vendas.
 *  @return void.
 */
AVL getFaturacao(FAT_FILIAL f, int i);

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

/** @brief Função que retorna o elemento que está na posição l, c da Faturacao.
 *
 *  @param f Faturacao.
 *  @param l linha.
 *  @param c coluna.
 *  @return elemento nessa posicao.
 */

int getQuantPos (FAT f, int l, int c);


/** @brief Função que retorna o elemento que está na posição l, c da Faturacao.
 *
 *  @param f Faturacao.
 *  @param l linha.
 *  @param c coluna.
 *  @return elemento nessa posicao.
 */

double getPrecoPos(FAT f, int l, int c);


/** @brief Função que inicializa a struct FAT.
 *
 *  @param new Fatu.
 *  @return elemento nessa posicao.
 */

FAT initFatProduto (FAT new);


/** @brief Função que gera a faturação de um produto.
 *
 *  @param vendas AVL de vendas.
 *  @param prod produto para verificacao.
 *  @param mes mes de procura.
 *  @param f Faturação
 *  @return void.
 */

void geraFaturacaoProduto (AVL vendas, char* prod, int mes, FAT f);


#endif

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
typedef struct faturacao* FAT;

/*______________________________________________________________________*/

/** @brief Função que gera a faturacao entre dois meses.
 *
 *  @param f Faturacao.
 *  @param min Mes inferior.
 *  @param max Mes superior.
 *  @param vendas AVL de vendas.
 *  @return void.
 */

void faturacaoMes (int min, int max, AVL vendas, FAT f);


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


/** @brief Função que liberta a memória de uma Faturacao.
 *
 *  @param f Faturacao.
 *  @return elemento nessa posicao.
 */

void freeFat (FAT f);

#endif
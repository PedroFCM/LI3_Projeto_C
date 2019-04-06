
/** @file avlstruct.h
*	@brief Header file de avlstruct.c
*
*	@autor João Pedro Rodrigues Azevedo (A85227) 
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@bug Nenhum que tivessemos reparado.
*	
*/

/*----------------------------------------------------------------------*/

#ifndef _AVL_
#define _AVL_

/*MACROS par indicar o tipo de balancemento duma AVL*/

/*MACRO Para indicar que está balanceada*/
#define BAL   0
/*MACRO Para indicar que está balanceada para a esquerda*/
#define LEFT -1
/*MACRO Para indicar que está balanceada para a direita*/
#define RIGHT 1

/*----------------------------------------------------------------------*/

/** Define uma AVL básica.*/
typedef struct avl* AVL;

/** Define um catálogo de clientes usando uma AVL.*/
typedef struct avl* CAT_CLIENTES;

/** Define um catálogo de produtos usando uma AVL.*/
typedef struct avl* CAT_PRODUTOS;

/** Define um catálogo de vendas usando uma AVL.*/
typedef struct avl* CAT_VENDAS;

/** Define o campo catálogo de clientes de uma AVL.*/
typedef struct registo* REGISTO;

/** Define o campo fatura de uma AVL.*/
typedef struct fatura *FATURA;

/** Define o campo gestao de filial de uma AVL.*/
typedef struct gestaoFilial* GESTAO_FILIAL;

/*----------------------------------------------------------------------*/

/** @brief Função que liberta a memoria de uma AVL contendo a struct gestaoFilial != NULL.
 *
 *  @param a AVL.
 *  @return void.
*/

void freeAVLfil (AVL a);

/** @brief Função que liberta a memoria de uma AVL contendo a struct registo != NULL.
 *
 *  @param a AVL.
 *  @return void.
*/

void freeAVLregisto(AVL a);

/** @brief Função que liberta a memoria de uma AVL contendo a struct fatura != NULL.
 *
 *  @param a AVL.
 *  @return void.
*/

void freeAVLfaturacao (AVL a);

/** @brief Função que retorna o campo GESTAO_FILIAL de uma AVL.
 *
 *  @param a AVL.
 *  @return A GESTAO_FILIAL.
*/

GESTAO_FILIAL getGestaoFilial(AVL filial);

/** @brief Função que o campo fatura de uma AVL
 *
 *  @param a AVL.
 *  @return Campo fatura.
*/

FATURA getFatura (AVL a);


/** @brief Função que o Campo registo de uma AVL
 *
 *  @param a AVL.
 *  @return Campo registo.
*/

REGISTO getRegisto (AVL a);

/** @brief Função que retorna a primeira letra da tag de uma venda
 *
 *  @param a AVL.
 *  @return Primeira letra do campo tag.
*/

char getFirstLetterTag (AVL a);


/** @brief Função que retorna a string venda
 *
 *  @param a AVL.
 *  @return string venda.
*/

char* getTag (AVL a);

/** @brief Função que retorna o lado esquerdo de uma AVL.
 *
 *  @param a AVL.
 *  @return Lado esquerdo da AVL
*/

AVL getEsq (AVL a);


/** @brief Função que retorna o lado direito de uma AVL.
 *
 *  @param a AVL.
 *  @return Lado direito da AVL
*/

AVL getDir (AVL a);


/** @brief Função que liberta memória de uma AVL.
 *
 *  @param a AVL.
 *  @return void
 */

void freeAVL_andTag (AVL a);

/** @brief Função que insere um novo elemento numa AVL.
 *
 *  @param a AVL.
 *  @param novo novo registos.
 *  @param arg string de venda.
 *  @return AVL após inserção.
 */

AVL updateAVL (AVL a, REGISTO novo, FATURA f, GESTAO_FILIAL nova_gestao, char *arg, int flag);

/*----------------------------------------------------------------------*/

#endif
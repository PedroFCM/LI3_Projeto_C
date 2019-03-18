
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

#ifndef _AVL_
#define _AVL_

/*MACRO par indicar o tipo de balancemento*/

#define BAL   0
#define LEFT -1
#define RIGHT 1

typedef struct avl {
	int bal;
	char *tag;
	struct avl *left, *right;
} *AVL;

/** @brief Função que liberta memória de uma AVL.
 *
 *  @param a AVL.
 *  @return void
 */

void freeAVL (AVL a);


/** @brief Função que faz uma rotação à direita de uma AVL.
 *
 *  @param a AVL.
 *  @return AVL após rotação.
 */

AVL rotateRight (AVL a);


/** @brief Função que faz uma rotação à esquerda de uma AVL.
 *
 *  @param a AVL.
 *  @return AVL após rotação.
 */

AVL rotateLeft (AVL b);


/** @brief Função que resolver diferenças de altura à direita.
 *
 *  @param a AVL.
 *  @return AVL após o fix.
 */

AVL fixRight (AVL a);


/** @brief Função que resolver diferenças de altura à esquerda.
 *
 *  @param a AVL.
 *  @return AVL após o fix.
 */

AVL fixLeft (AVL a);


/** @brief Função que cria memória para uma AVL.
 *
 *  @param a AVL.
 *  @return AVL após o fix.
 */

AVL initAVL (AVL a, char *arg, int *g);


/** @brief Função auxiliar que insere um elemento a uma AVL.
 *
 *  @param a AVL.
 *  @return AVL após o fix.
 */

AVL updateAVLRec (AVL a, char *arg, int *g);


/** @brief Função que insere um novo elemento numa AVL.
 *
 *  @param a AVL.
 *  @return AVL após o fix.
 */

AVL updateAVL (AVL a, char *arg);

#endif
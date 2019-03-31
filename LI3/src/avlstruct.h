
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

/*______________________________________________________________________*/

#ifndef _AVL_
#define _AVL_

#include "global.h"

/*MACRO par indicar o tipo de balancemento duma AVL*/
#define BAL   0
#define LEFT -1
#define RIGHT 1

/*______________________________________________________________________*/

/*TYPE para definir uma AVL básica*/
typedef struct avl* AVL;

/*TYPE para definir uma AVL básica, nome diferente*/
typedef struct avl* CAT_CLIENTES;

/*TYPE para definir uma AVL básica, nome diferente*/
typedef struct avl* CAT_PRODUTOS;

/*TYPE para definir uma AVL básica, nome diferente*/
typedef struct avl* CAT_VENDAS;

/*TYPE para definir um registo numa AVL, 
guarda a venda separada*/
typedef struct registo* REGISTO;
typedef struct fatura* FATURA;
typedef int** VENDAS;
typedef struct avl *AVL;
typedef float** FAT_MES;
typedef struct gestaoFilial* GESTAO_FILIAL;

/*______________________________________________________________________*/

GESTAO_FILIAL getGestaoFilial(AVL filial);

void printFaturacao (AVL fat);

FATURA getFatura (AVL a);

char getFirstLetterTag (AVL a);

REGISTO getRegisto (AVL a);

char* getTag (AVL a);

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

void freeAVL (AVL a, int flag);


/** @brief Função que faz uma rotação à direita de uma AVL.
 *
 *  @param a AVL.
 *  @param flag pode ser 0 ou 1, no caso de ser 1 indica que queremos fazer free às vendas
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

AVL initAVL (AVL a, REGISTO novo, char *arg, int *g, FATURA new, GESTAO_FILIAL nova_gestao, int flag);


/** @brief Função auxiliar que insere um elemento a uma AVL.
 *
 *  @param a AVL.
 *  @param novo novo registos.
 *  @param arg string de venda.
 *  @param g flag que indica se cresceu ou não a AVL após inserção
 *  @return AVL após inserção.
 */

AVL updateAVLRec (AVL a, REGISTO novo, GESTAO_FILIAL nova_gestao, char *arg, int *g, FATURA f, int flag);


/** @brief Função que insere um novo elemento numa AVL.
 *
 *  @param a AVL.
 *  @param novo novo registos.
 *  @param arg string de venda.
 *  @return AVL após inserção.
 */

AVL updateAVL (AVL a, REGISTO novo, GESTAO_FILIAL nova_gestao, char *arg, FATURA f, int flag);

#endif
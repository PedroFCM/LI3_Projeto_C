
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

/*TYPE para definir uma AVL básica*/
typedef struct avl* AVL;

/*TYPE para definir uma AVL básica, nome diferente*/
typedef struct avl* CAT_CLIENTES;

/*TYPE para definir uma AVL básica, nome diferente*/
typedef struct avl* CAT_PRODUTOS;

/*TYPE para definir uma AVL básica, nome diferente*/
typedef struct avl* CAT_VENDAS;

/*TYPE para definir um registo numa AVL, guarda a venda separada*/
typedef struct registo* REGISTO;

/*TYPE para definir uma Fatura numa AVL*/
typedef struct fatura *FATURA;

typedef struct gestaoFilial* GESTAO_FILIAL;

/*----------------------------------------------------------------------*/
GESTAO_FILIAL getGestaoFilial(AVL filial);

/** @brief Função que retorna a primeira letra da tag de uma venda
 *
 *  @param a AVL.
 *  @return Primeira letra do campo tag.
*/

char getFirstLetterTag (AVL a);


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

AVL initAVL (AVL a, REGISTO novo, FATURA f, GESTAO_FILIAL nova_gestao, char *arg, int *g, int flag);


/** @brief Função auxiliar que insere um elemento a uma AVL.
 *
 *  @param a AVL.
 *  @param novo novo registos.
 *  @param arg string de venda.
 *  @param g flag que indica se cresceu ou não a AVL após inserção
 *  @return AVL após inserção.
 */

AVL updateAVLRec (AVL a, REGISTO novo, FATURA f,  GESTAO_FILIAL nova_gestao, char *arg, int *g, int flag);


/** @brief Função que insere um novo elemento numa AVL.
 *
 *  @param a AVL.
 *  @param novo novo registos.
 *  @param arg string de venda.
 *  @return AVL após inserção.
 */

AVL updateAVL (AVL a, REGISTO novo, FATURA f, GESTAO_FILIAL nova_gestao, char *arg, int flag);

#endif
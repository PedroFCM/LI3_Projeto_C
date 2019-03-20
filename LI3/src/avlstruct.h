
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

typedef struct registo {

	char* codProd;
	double preco;
	int quantidade;
	char tipo;
	char* codCli;
	int mes;
	int filial;

} *REGISTO;

typedef struct avl {
	int bal;
	
	char* tag;
	
	REGISTO registo;

	struct avl *left, *right;

} *AVL;

/** @brief Função que retorna o produto comprado numa venda.
 *
 *  @param a AVL.
 *  @return codigo do produto vendido.
*/

char* getCodProd (AVL a);


/** @brief Função que retorna a filial da venda.
 *
 *  @param a AVL.
 *  @return Filial.
*/

int getFilial (AVL a);


/** @brief Função retorna a quantidade vendida numa venda.
 *
 *  @param a AVL.
 *  @return quantidade registada.
*/

int getQuantidade (AVL a);


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

AVL initAVL (AVL a, REGISTO novo, char *arg, int *g);


/** @brief Função auxiliar que insere um elemento a uma AVL.
 *
 *  @param a AVL.
 *  @param novo novo registos.
 *  @param arg string de venda.
 *  @param g flag que indica se cresceu ou não a AVL após inserção
 *  @return AVL após inserção.
 */

AVL updateAVLRec (AVL a, REGISTO novo, char *arg, int *g);


/** @brief Função que insere um novo elemento numa AVL.
 *
 *  @param a AVL.
 *  @param novo novo registos.
 *  @param arg string de venda.
 *  @return AVL após inserção.
 */

AVL updateAVL (AVL a, REGISTO novo, char *arg);

#endif
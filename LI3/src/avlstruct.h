
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

/*______________________________________________________________________*/

/** @brief Função que initializa um registo de venda.
 *
 *  @param novo Registo de venda.
 *  @return registo alocado
*/

REGISTO initRegisto (REGISTO novo);


/** @brief Função que insere uma filial num registo de venda.
 *
 *  @param reg Registo de venda.
 *  @param f filial para inserção
 *  @return void
*/

void setFilial (REGISTO reg, int f);


/** @brief Função que insere o mes de compra num registo.
 *
 *  @param reg Registo de venda.
 *  @param mes mes para inserção
 *  @return void
*/

void setMes (REGISTO reg, int m);


/** @brief Função que insere um cliente num registo.
 *
 *  @param reg Registo de venda.
 *  @param cliente cliente para inserção
 *  @return void
*/

void setCodCliente (REGISTO reg, char* cliente);


/** @brief Função que insere um tipo de compra a um registo.
 *
 *  @param reg Registo de venda.
 *  @param tp tipo de compra para inserção
 *  @return void
*/

void setTipo (REGISTO reg, char tp);


/** @brief Função que insere uma quantidade comprada num registo.
 *
 *  @param reg Registo de venda.
 *  @param qt quantidade para inserção
 *  @return void
*/

void setQuantidade (REGISTO reg, int qt);


/** @brief Função que insere o preco de um produto a um registo.
 *
 *  @param reg Registo de venda.
 *  @param price preco para inserção
 *  @return void
*/

void setPreco (REGISTO reg, double price);


/** @brief Função que insere um produto a um registo.
 *
 *  @param reg Registo de venda.
 *  @param prod produto para inserção
 *  @return void
*/

void setCodProd (REGISTO reg, char *prod);


/** @brief Função que retorna a primeira letra de uma tag.
 *
 *  @param a AVL.
 *  @return char primeira letra.
*/

char getFirstLetterTag (AVL a);


/** @brief Função que retorna o tipo de uma venda.
 *
 *  @param a AVL.
 *  @return o cliente de um registo venda.
*/

char getTipo (AVL a);


/** @brief Função que retorna o código de cliente.
 *
 *  @param a AVL.
 *  @return o cliente de um registo venda.
*/

char* getCodCliente (AVL a);

/** @brief Função que retorna o mes de uma venda.
 *
 *  @param a AVL.
 *  @return o mes de uma venda.
*/

int getMes (AVL a);


/** @brief Função que retorna o preco de um produto numa venda.
 *
 *  @param a AVL.
 *  @return o preco de um produto de uma venda.
*/

double getPreco (AVL a);


/** @brief Função que retorna o registo de uma venda.
 *
 *  @param a AVL.
 *  @return o registo da venda.
*/

REGISTO getRegisto (AVL a);


/** @brief Função que retorna a string venda
 *
 *  @param a AVL.
 *  @return string venda.
*/

char* getTag (AVL a);


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

AVL initAVL (AVL a, REGISTO novo, char *arg, int *g, int flag);


/** @brief Função auxiliar que insere um elemento a uma AVL.
 *
 *  @param a AVL.
 *  @param novo novo registos.
 *  @param arg string de venda.
 *  @param g flag que indica se cresceu ou não a AVL após inserção
 *  @return AVL após inserção.
 */

AVL updateAVLRec (AVL a, REGISTO novo, char *arg, int *g, int flag);


/** @brief Função que insere um novo elemento numa AVL.
 *
 *  @param a AVL.
 *  @param novo novo registos.
 *  @param arg string de venda.
 *  @return AVL após inserção.
 */

AVL updateAVL (AVL a, REGISTO novo, char *arg, int flag);

#endif
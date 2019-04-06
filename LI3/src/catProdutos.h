
/** @file catProdutos.h
*	@brief Header file de catProdutos.c
*
*	@autor João Pedro Rodrigues Azevedo
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*	
*/

/*----------------------------------------------------------------------*/

#ifndef _PRODUTOSRW_
#define _PRODUTOSRW_

/*----------------------------------------------------------------------*/

#include "global.h"
#include "avlstruct.h"

/*----------------------------------------------------------------------*/

/**
* Struct para representar uma lista de elementos (Produtos no caso implementado).
* Usada para guardar as paginas a apresentar ao utilizador.
* Pode ser entendida com o catálogo de produtos com uma dada letra.
*/
typedef struct listaProdutos* LISTA_PROD;

/*----------------------------------------------------------------------*/

/** @brief Função que verifica se um produto introduzido é válido.
 *
 *  @param *product produto para verificacao.
 *  @return 1 se for válido.
 */

int verify_product (char *product);


/** @brief Função que guarda num estrutura AVL os produtos validados.
 *
 *  @param *filename ficheiro de leitura.
 *  @param prod AVL para ler os produtos validados.
 *  @param set estrutura GLOBAL para guardar as stats principais de leitura.
 *  @return AVL de vendas válidas.
 */

CAT_PRODUTOS readNvalidate_products (char* filename, CAT_PRODUTOS prod, GLOBAL set);


/** @brief Função que que retorna o tamanho atual de uma lista.
 *
 *  @param s lista de produtos.
 *  @return 1 se for válido.
 */

int getCurrentSize (LISTA_PROD s);


/** @brief Função que liberta a memória de uma lista.
 *
 *  @param s lista.
 *  @return 1 se for válido.
 */

void freeList (LISTA_PROD s);


/** @brief Função que duplica o tamanho de uma lista.
 *
 *  @param s lista de produtos.
 *  @return void.
 */

void duplicateList (LISTA_PROD s);


/** @brief Função que adiciona um produto a uma lista.
 *
 *  @param s lista de produtos.
 *  @return void.
 */

LISTA_PROD addProduto (LISTA_PROD l, char *new_produto);


/** @brief Função que determina se uma lista está vazia.
 *
 *  @param s Lista para verificar.
 *  @return 1 se for vazia.
 */

int isEmptyLista (LISTA_PROD s);


/** @brief Função que gera a lista de produtos iniciada por uma dada letra.
 *
 *  @param produtos AVL de produtos argumento.
 *  @param letra letra para gerar a lista.
 *  @return 1 se for válido.
 */

LISTA_PROD initLista (LISTA_PROD s, int tamanho_inicial);


/** @brief Função que gera a lista de produtos iniciada por uma dada letra.
 *
 *  @param produtos AVL de produtos argumento.
 *  @param s lista de produtos onde guardar.
 *  @param letra letra para gerar a lista.
 *  @return A lista gerada.
 */

LISTA_PROD geraListaLetra (AVL produtos, LISTA_PROD s, char letra);


/** @brief Função que retorna a pos do ultimo elemento de uma lista de produtos.
 *
 *  @param s lista de produtos onde guardar.
 *  @return A lista gerada.
 */

int getSPList (LISTA_PROD s);
char* getElementList(LISTA_PROD s, int pos);

#endif
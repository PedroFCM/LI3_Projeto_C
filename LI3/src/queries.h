
/** @file queries.h
*	@brief Header file de queries.c
*
*	@autor João Pedro Rodrigues Azevedo (A85227) 
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@bug Nenhum que tivessemos reparado.
*	
*/

/*-----------------------------------------------------------------------*/

#ifndef _QUERIES_
#define _QUERIES_

/*-----------------------------------------------------------------------*/

#include "lstring.h"
#include "hashtables.h"
#include "Faturacao.h"
#include "Filial.h"

/*-----------------------------------------------------------------------*/


/*-----------------------------------------------------------------------*/


/** @brief Query1 apresenta os resultados de leitura dos ficheiros.
 *
 *  @param set struct que guarda as carateristicas de leitura.
 *  @return void.
 */

void query1 (GLOBAL set);

/*-----------------------------------------------------------------------*/


/** @brief Query2 gera e apresenta a lista de produtos iniciados por uma letra.
 *
 *  @param ls lista de produtos.
 *  @param produtos AVL de produtos validos
 *  @param c caracter de procura.
 *  @return void.
 */

LISTA_PROD query2 (LISTA_PROD ls, AVL produtos, char c);

/*-----------------------------------------------------------------------*/

/** @brief Auxiliar da Q3, faz print ao resultado de forma global.
 *
 *  @param n_vendas matriz de ints (vendas).
 *  @param faturacao matriz de floats (faturacao).
 *  @return void.
 */

void showStatGlobal(VENDAS n_vendas, FAT_MES faturacao);

/** @brief Auxiliar da Q3, faz print ao resultado por filial.
 *
 *  @param n_vendas matriz de ints (vendas).
 *  @param faturacao matriz de floats (faturacao).
 *  @return void.
 */

void showStatPorFilial(VENDAS n_vendas, FAT_MES faturacao);

/** @brief Query3 gera a matriz de vendas e faturacao num dado mes.
 *
 *  @param fat Struct faturacao (antes inicializada).
 *  @param mes o mes.
 *  @param produto produto de procura.
 *  @param opcao 0 -> global, 1 -> por filial
 *  @return void.
 */

void query3 (FAT_FILIAL fat, int mes, char *produto, int opcao);

/*-----------------------------------------------------------------------*/


/** @brief Query4 gera a matriz de vendas e faturacao num dado mes.
 *
 *  @param fat Struct faturacao (antes inicializada).
 *  @param mes o mes.
 *  @param produto produto de procura.
 *  @param opcao 0 -> global, 1 -> por filial
 *  @return void.
 */

void query4(FAT_FILIAL fat, AVL produtos, int opcao);

/*-----------------------------------------------------------------------*/


/** @brief Query5 gera e apresenta a AVL de clientes que compraram em todas a filiais.
 *
 *  @param filial Struct filial (antes inicializada).
 *  @param clientes AVL de clientes.
 *  @return void.
 */

void query5(FILIAL filial, AVL clientes);

/*-----------------------------------------------------------------------*/

/** @brief Aux da query6 verifica se um produto existe numa AVL.
 *
 *  @param filial AVL da struct filial escolhida.
 *  @param elem elemento para procura.
 *  @return 1 caso exista.
 */

int existeProdutoNaAVLFilial (AVL filial, char* elem);


/** @brief Aux da query6 que conta o numero de produtos que nunca foram comprados.
 *
 *  @param fat Struct faturacao (antes inicializada).
 *  @param produtos avl de produtos validos.
 *  @param produtosNC flag que guarda o numero de produtos validos.
 *  @return void.
 */

void produtosSemCompras (FAT_FILIAL fat, AVL produtos, int *produtosNC);


/** @brief Query6 apresenta o nº de clientes que nao realizaram compras,
 *         bem como o nº de produtos nao comprados.
 *
 *  @param fat Struct faturacao (antes inicializada).
 *  @param fil Sruct filial (antes inicializada).
 *  @param produtos avl de produtos validos.
 *  @param clientes avl de clientes validos.
 *  @return void.
 */

void query6 (FAT_FILIAL fat, FILIAL fil, AVL produtos, AVL clientes);

/*-----------------------------------------------------------------------*/


/** @brief Query7 apresenta a tabela de produtos comprados por um cliente (por mes / filial).
 * 
 *  @param filial Sruct filial (antes inicializada).
 *  @param cliente cliente de procura.
 *  @return void.
 */

void query7(FILIAL filial, char* cliente);

/*-----------------------------------------------------------------------*/


/** @brief Query8 apresenta o nº total de vendas e faturacao entre dois meses.
 * 
 *  @param fat Sruct fat (antes inicializada).
 *  @param min mes inferior.
 *  @param max mes superior.
 *  @return void.
 */

void query8(FAT_FILIAL fat, int min, int max);

/*-----------------------------------------------------------------------*/


/** @brief Aux da query9, verifica se uma matriz esta a zeros.
 * 
 *  @param f matriz de floats.
 *  @param flag useless.
 *  @return 1 caso esteja a zeros.
 */

int matrizAzeros (float **f, int flag);


/** @brief Aux da query9 que gera a lista de clientes que compraram um dado produto.
 * 
 *  @param fil Sruct avl filial (antes inicializada).
 *  @param codProd codigo do produto.
 *  @param compras lista para insercao e posterior return.
 *  @param tipo para distinguir a lista de N e P.
 *  @return lista de clientes.
 */

LString geraClientesFilial (AVL fil, char *codProd, LString *compras, char tipo);


/** @brief Query9 apresenta os codigos dos clientes que compraram um dado produto (N e P).
 * 
 *  @param fil Sruct filial (antes inicializada).
 *  @param codProd Codigo do produto para procura.
 *  @param filial numero da filial.
 *  @return void.
 */

void query9 (FILIAL fil, char *codProd, int filial);


/*-----------------------------------------------------------------------*/


/** @brief Query10 apresenta a lista de produtos comprados (por ordem do mais comprado).
 * 
 *  @param filial Sruct filial (antes inicializada).
 *  @param cliente Codigo do cliente para procura.
 *  @param mes o mes em questao.
 *  @return void.
 */

void query10(FILIAL filial, char* cliente, int mes);

/*-----------------------------------------------------------------------*/


/** @brief Aux da query11, gera a tabela de hash de quantidades compradas para um produto.
 * 
 *  @param filial Sruct avl filial (antes inicializada).
 *  @param h hashtable para insercao.
 *  @param flag para indicar o numero da filial.
 *  @return void.
 */

void geraTabelaQuantidades (AVL filial, HEAD_TABLE h, int flag);


/** @brief Query11 apresenta a lista dos N produtos mais comprados.
 * 
 *  @param filial Sruct filial (antes inicializada).
 *  @param n numero de elemntos a apresentar.
 *  @return void.
 */

void query11 (FILIAL filial, int n);

/*-----------------------------------------------------------------------*/


/** @brief Query12 apresenta o codigo dos 3 produtos em que um cliente mais gastou dinheiro.
 * 
 *  @param filial Sruct filial (antes inicializada).
 *  @param cliente o cliente.
 *  @return void.
 */

void query12 (FILIAL filial, char* cliente);

/*-----------------------------------------------------------------------*/

#endif
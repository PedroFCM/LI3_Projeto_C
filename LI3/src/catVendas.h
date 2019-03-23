
/** @file catVendas.h
*	@brief Header file de catVendas.c
*
*	@autor João Pedro Rodrigues Azevedo (A85227) 
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@bug Nenhum que tivessemos reparado.
*	
*/

/*______________________________________________________________________*/

#ifndef _SELLS_
#define _SELLS_

/*_________________BIBLIOTECAS IMPLEMENTADAS____________________________*/

#include "global.h"
#include "avlstruct.h"

/*______________________________________________________________________*/

/** @brief Função que verifica se uma venda é válida.
 *
 *  @param vendas AVL de vendas.
 *  @param prod AVL de produtos para pesquisa.
 *  @param client AVL de clientes para pesquisa.
 *  @param set para guardar informações de leitura.
 *  @param sell venda para análise.
 *  @param reg registo que será adicionado caso a venda seja válida.
 *  @return 1 se for valido.
 */

int verify_sell (CAT_VENDAS vendas, AVL prod, AVL client, GLOBAL set, char *sell, REGISTO reg);


/** @brief Função que verifica se uma venda é válida.
 *
 *  @param filename ficheiro para guardar as vendas válidas
 *  @param sells AVL de vendas.
 *  @param prod AVL de produtos para pesquisa.
 *  @param client AVL de clientes para pesquisa.
 *  @param set para guardar informações de leitura.
 *  @return 1 se for valido.
 */

CAT_VENDAS readNvalidate_sells (char* filename, CAT_VENDAS sells, GLOBAL set, AVL prod, AVL cli);

#endif
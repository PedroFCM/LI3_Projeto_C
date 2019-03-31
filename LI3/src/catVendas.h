
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

char* getCodProd (AVL a);

int getFilial (AVL a);

int getQuantidade (AVL a);

char getTipo (AVL a);

char* getCodCliente (AVL a);

int getMes (AVL a);

double getPreco (AVL a);

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
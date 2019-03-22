
/** @file Filial.h
*	@brief Ficheiro header para o Filial.c.
*
*	@autor João Pedro Rodrigues Azevedo (A85227) 
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@bug Nenhum que tivessemos reparado.
*	
*/

#ifndef _FILIAL_
#define _FILIAL_

/*_________________BIBLIOTECAS IMPLEMENTADAS____________________________*/

#include "avlstruct.h"
#include "stack.h"

/** @brief Função que gera uma matriz filial.
 *         Se a matriz estiver toda a 1 então o cliente comprou nas 3 filiais
 *
 *  @param vendas AVL de vendas para procura.
 *  @param filial matriz de verificacao.
 *  @param cliente string contendo o cliente de pesquisa.
 *  @return void.
 */

void procuraNaFilial (AVL vendas, int filial[], char* cliente);


/** @brief Função que gera a faturacao entre dois meses.
 *
 *  @param f Faturacao.
 *  @param min Mes inferior.
 *  @param max Mes superior.
 *  @param vendas AVL de vendas.
 *  @return void.
 */

void compraramEmTodas (AVL vendas, AVL* clie_filiais);


/** @brief Função que gera a faturacao entre dois meses.
 *
 *  @param f Faturacao.
 *  @param min Mes inferior.
 *  @param max Mes superior.
 *  @param vendas AVL de vendas.
 *  @return void.
 */

void compraramNaFilial (AVL vendas, char* prod, int filial, Stack* clientesN, Stack* clientesP);

#endif
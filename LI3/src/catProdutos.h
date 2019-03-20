
/** @file catProdutos.h
*	@brief Header file de catProdutos.c
*
*	@autor João Pedro Rodrigues Azevedo (A85227) 
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@bug Nenhum que tivessemos reparado.
*	
*/

/*______________________________________________________________________*/

#ifndef _PRODUTOSRW_
#define _PRODUTOSRW_

/*_________________BIBLIOTECAS IMPLEMENTADAS____________________________*/

#include "global.h"
#include "avlstruct.h"

/*______________________________________________________________________*/

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

#endif
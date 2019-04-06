
/** @file catClientes.h
*	@brief Header file de catClientes.c
*
*	@autor João Pedro Rodrigues Azevedo (A85227) 
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@bug Nenhum que tivessemos reparado.
*	
*/

/*----------------------------------------------------------------------*/

#ifndef _CLIENTESRW_
#define _CLIENTESRW_

/*_________________BIBLIOTECAS IMPLEMENTADAS____________________________*/

#include "global.h"
#include "avlstruct.h"

/*----------------------------------------------------------------------*/

/** @brief Função que verifica se um cliente é válido.
 *
 *  @param client Cliente para verificao.
 *  @return 1 caso seja válido.
 */

int verify_client (char *client);


/** @brief Função que guarda na estrutura AVL os clientes validados.
 *
 *  @param filename ficheiro de leitura dos clientes.
 *  @param clients AVL para guardar os clientes validos.
 *  @param set Estrutura GLOBAL que guarda stats de leitura dos ficheiros.
 *  @return AVL resultado.
 */

CAT_CLIENTES readNvalidate_clients (char *filename, CAT_CLIENTES clients, GLOBAL set);

/*----------------------------------------------------------------------*/

#endif
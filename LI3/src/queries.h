
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

/*______________________________________________________________________*/

#ifndef _QUERIES_
#define _QUERIES_

/*_________________BIBLIOTECAS IMPLEMENTADAS____________________________*/

#include "Faturacao.h"

/*______________________________________________________________________*/

/** @brief Função que gere a query1.
 *
 *  @param set Struct que contém as informações de leitura.
 *  @return void.
*/

void query1 (GLOBAL set);


/** @brief Função que implementa a query2.
 *
 *  @param ls Lista de produtos para inserção.
 *  @param produtos AVL que guarda os produtos validos.
 *  @param c letra que o user pretende para guardar os produtos
 *		     que se iniciam por essa letra.
 *  @return A lista dos produtos iniciados por essa letra.
*/

LISTA_PROD query2 (LISTA_PROD ls, AVL produtos, char c);


#endif
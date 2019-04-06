/**
*	@mainpage LI3_PROJETO GRUPO 58
*	
*	@autor João Pedro Rodrigues Azevedo 
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@file main.c
*	@brief Módulo principal que carrega todo o sistema SGV.
*	@bug Nenhum que tivessemos reparado.
*
*/

/*_________________BIBLIOTECAS IMPLEMENTADAS____________________________*/

/*@brief Include relativo ao controlador do SGV*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "global.h"
#include "catProdutos.h"
#include "catClientes.h"
#include "catVendas.h"
#include "avlstruct.h"
#include "queries.h"
#include "menu.h"
#include "Faturacao.h"
#include "Filial.h"
/*----------------------------------------------------------------------*/

/**
* @brief Função principal do programa (main).
* 
* Mostra o menu do sistema e permite a navegação num
* conjunto determinado de funcionalidades. Opera sobre
* estruturas como AVL's, hashtables, arrays, stacks e Linked Lists.
*
* @param void Nenhum.
*
* @returns Retorna 0 caso tudo corra bem.
*/


int main (void) {

	/*FUNÇÃO RESPONSAVEL POR CARREGAR O SGV*/
	loadMenu();

	return 0;
}

/*----------------------------------------------------------------------*/
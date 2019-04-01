/**
*	@mainpage LI3_PROJETO GRUPO 58
*	
*	@autor João Pedro Rodrigues Azevedo (A85227) 
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@file main.c
*	@brief Função principal que carrega todo o sistema SGV.
*	@bug Nenhum que tivessemos reparado.
*
*/

/*_________________BIBLIOTECAS IMPLEMENTADAS____________________________*/

/*Include relativo ao controlador do SGV*/
#include "menu.h"

/**
* @brief Função principal do programa (main).
* 
* Mostra o menu do sistema e permite a navegação num
* conjunto determinado de funcionalidades. Opera sobre
* estruturas como AVL's...
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

/** @file menu.h
*	@brief Header file de menu.c
*
*	@autor João Pedro Rodrigues Azevedo (A85227) 
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@bug Nenhum que tivessemos reparado.
*	
*/

#ifndef _MENU_
#define _MENU_

/** @brief Função que verifica o input do user.
 *
 *  @param input numero de caracteres lidos do scanf.
 *  @param selection opcao que selecionou.
 *  @return 1 se for valido.
 */

int checkInput (int input, int selection);


/** @brief Função que limpa o ecrã.
 *
 *  @return void
 */

void clear_screen();


/** @brief Função principal que carrega o menu.
 *
 *  @return void
 */

void loadOption ();


/** @brief Função que imprime o tempo de execução da leitura.
 *
 *  @param time tempo que demorou.
 *  @return void
 */

void showTime (double time);


/** @brief Função que imprime as opções do user.
 *
 *  @return void
 */

void displayMenuAndOptions ();

#endif
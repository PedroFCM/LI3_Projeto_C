
/** @file menu.h
*	@brief Header file de menu.c
*
*	@autor João Pedro Rodrigues Azevedo
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@bug Nenhum que tivessemos reparado.
*	
*/

/*----------------------------------------------------------------------*/

#ifndef _MENU_
#define _MENU_

/*----------------------------------------------------------------------*/

/*@brief MACROS para cores do terminal*/
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

/*----------------------------------------------------------------------*/

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


/** @brief Função principal que carrega o menu do SGV.
 *
 *  @return void
 */

void loadMenu ();


/** @brief Função que imprime o tempo de execução da leitura.
 *
 *  @param time tempo que demorou.
 *  @return void
 */

void showTime (double time);


/** @brief Função que imprime as opções do user.
 *
 *  @param loaded variavel que indica se os dados já se encontram carregados.
 *  @return void
 */

void displayMenuAndOptions (int loaded);


/** @brief Função que imprime as opções do user relativamente à leitura de ficheiros.
 *
 *  @return void
 */

void displayFicheirosLeitura();

/** @brief Função que gera e apresenta as páginas que mostram a lista.
 *
 *  @param s Lista de produtos.
 *  @param dados_carregados uma flag que indica se os dados já foram carregados no programa.
 *  @return void.
 */

void pages (LISTA_PROD s, int dados_carregados);


/** @brief Função quem imprime uma lista entre duas posições.
 *
 *  @param s lista.
 *  @param low limite inferior.
 *  @param high limite superior
 *  @return void.
 */

void printListBetween (LISTA_PROD s, int low, int high);

/*----------------------------------------------------------------------*/

#endif
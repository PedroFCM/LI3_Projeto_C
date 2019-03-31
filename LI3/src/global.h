
/** @file global.h
*	@brief Header file de global.c
*
*	@autor João Pedro Rodrigues Azevedo (A85227) 
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@bug Nenhum que tivessemos reparado.
*	
*/

#ifndef _LER_
#define _LER_

/*_________________BIBLIOTECAS IMPLEMENTADAS____________________________*/

#include "avlstruct.h"

/*MACROS que estabelecem os paths para os ficheiros de leitura*/
#define PROD_PATH "datafiles/Produtos.txt"
#define CLIE_PATH "datafiles/Clientes.txt"
#define SELL_PATH_1M "datafiles/Vendas_1M.txt"
#define SELL_PATH_3M "datafiles/Vendas_3M.txt"
#define SELL_PATH_5M "datafiles/Vendas_5M.txt"

/*MACROS que estabelecem os paths para guardar os ficheiros*/
#define VAL_PROD_PATH "validData/Produtos(validados).txt"
#define VAL_CLIE_PATH "validData/Clientes(validados).txt"
#define VAL_SELL_PATH "validData/Vendas(validadas).txt"

/*MACRO para indicar o nº de campos que uma venda tem*/
#define CAMPOS_SELLS 7

#define NUM_FILIAIS 3
#define NUM_MESES 12

typedef enum {false, true} boolean;
typedef struct avl* AVL;


/*ESTRUTURA QUE DEFINE ESTATISTICAS GLOBAIS DE LEITURA DOS FICHEIROS*/
typedef struct settings {

	int num_prods, num_clients, num_sells;
	
	int val_prods, val_clients, val_sells;

	int max_line_prods, max_line_clients, max_line_sells;

} *GLOBAL;


char** tokenize (char** campos, char* sell);


/** @brief Função que remove o caracter extra de uma string.
 *         Coloca, portanto, '\0' para indicar o término da string.
 *
 *  @param  entry string para cortar.
 *  @return Nova string.
 */

char* string_cut_extra_char (char *entry);


/** @brief Função que verifica se um caracter está em uppercase.  
 *
 *  @param  ch caracter para verificação.
 *  @return 1 se for uppercase.
 */

int is_uppercase (char ch);


/** @brief Função que verifica se um caracter é um número.  
 *
 *  @param  ch caracter para verificação.
 *  @return 1 se for número.
 */

int is_number (char ch);


/** @brief Função que calcula o comprimento da 
 *    	   maior linha de um ficheiro.  
 *
 *  @param  filename Ficheiro input.
 *  @return Maior linha.
 */

int biggest_line_in_file (char *filename);


/** @brief Função que calcula o número de espaços de uma string.  
 *
 *  @param  str String para análise.
 *  @return Número de espaços que a string tem.
 */

int numb_spaces_in_string (char *str);


/** @brief Função que verifica se um elemento existe numa AVL.  
 *
 *  @param  AVL AVL input.
 *  @param  element elemento para procura.
 *  @return 1 caso exista.
 */

int exist_element (AVL a, char *element);


/** @brief Função que imprime uma AVL por ordem no ecrã.  
 *
 *  @param  AVL AVL input.
 *  @return Nada (void).
 */

void inorder_avl (AVL a);


/** @brief Função auxiliar de write_inorder_avl_on_file que
 * 		   escreve uma AVL num ficheiro por ordem alfabetica.  
 *
 *  @param  AVL AVL input.
 *  @param  element elemento para procura.
 *  @return 1 caso exista.
 */

void write_recursive (AVL a, FILE *fp);


/** @brief Função que escreve uma AVL num ficheiro por ordem alfabetica.  
 *
 *  @param  filepath Nome do ficheiro onde escrever.
 *  @param  AVL AVL input.
 *  @return 1 caso exista.
 */

void write_inorder_avl_on_file (char *filepath, AVL a, GLOBAL set);


/** @brief Função que imprime a tag de uma AVL.  

 *  @param  AVL AVL input.
 *  @return 1 caso corra bem.
 */

int inorder_avl_just_tag (AVL a);

#endif
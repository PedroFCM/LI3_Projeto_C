
/** @file global.h
*	@brief Header file de global.c
*
*	@autor João Pedro Rodrigues Azevedo
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@bug Nenhum que tivessemos reparado.
*	
*/

#ifndef _LER_
#define _LER_

/*-----------------------------------------------------------------*/

#include "avlstruct.h"

/*-----------------------------------------------------------------*/

/**PATH source para os produtos*/
#define PROD_PATH "datafiles/Produtos.txt"
/**PATH source para os clientes*/
#define CLIE_PATH "datafiles/Clientes.txt"
/**PATH source para os vendas 1M*/
#define SELL_PATH_1M "datafiles/Vendas_1M.txt"
/**PATH source para os vendas 3M*/
#define SELL_PATH_3M "datafiles/Vendas_3M.txt"
/**PATH source para os vendas 5M*/
#define SELL_PATH_5M "datafiles/Vendas_5M.txt"

/*-----------------------------------------------------------------*/

/*PATH source para os vendas (VALIDADAS)*/
#define VAL_PROD_PATH "validData/Produtos(validados).txt"
/*PATH source para os clientes (VALIDADOS)*/
#define VAL_CLIE_PATH "validData/Clientes(validados).txt"
/*PATH source para os produtos (VALIDADOS)*/
#define VAL_SELL_PATH "validData/Vendas(validadas).txt"

/*-----------------------------------------------------------------*/

/**MACRO para indicar o nº de campos que uma venda tem*/
#define CAMPOS_SELLS 7

/**MACRO para indicar o nº total de filiais*/
#define NUM_FILIAIS 3

/**MACRO para indicar o nº de meses total*/
#define NUM_MESES 12

/**MACRO para definir um char* com um PRODUTO */
#define PRODUTO char*

/**MACRO definir um char* como um CLIENTE*/
#define CLIENTE char*

/*-----------------------------------------------------------------*/

/**
* Struct para representar o registo de uma venda válida.
*/
typedef struct settings {
	/*@{*/
	int num_prods, num_clients, num_sells; /**< Numero de prods, clients e vendas lidas. */	
	int val_prods, val_clients, val_sells; /**< Numero de prods, clients e vendas lidas (VALIDADAS). */
	int max_line_prods, max_line_clients, max_line_sells; /**< Tamanho de linha maximo do ficheiro. */
	/*@}*/
} *GLOBAL;

/*-----------------------------------------------------------------*/

/** @brief Função que separa uma string vendas nos seus campos.
 *
 *  @param campos array para guardar.
 *  @param sell string venda para separar
 *  @return array com os campos separados.
 */

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


/** @brief Função que imprime uma AVL posorder.  

 *  @param  AVL AVL input.
 *  @return 1 caso corra bem.
 */

int printDecresAvl(AVL a);

/*-----------------------------------------------------------------*/

#endif
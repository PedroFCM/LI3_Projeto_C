
/** @file hashtables.h
*	@brief Header file de hashtables.c.
*
*	@autor João Pedro Rodrigues Azevedo (A85227) 
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@bug Nenhum que tivessemos reparado.
*	
*/

/*______________________________________________________________________*/

#ifndef _HASHTABLES_
#define _HASHTABLES_

/*______________________________________________________________________*/

/*MACRO que define o tamanho que seria de esperar num HT de produtos*/
#define HSIZE_PRODS 200000
/*MACRO que define o tamanho que seria de esperar num HT de clientes*/
#define HSIZE_CLIEN 20000

/*______________________________________________________________________*/

#define FREE 0
#define USED 1
#define DELETED 2

/*______________________________________________________________________*/

/**TYPE para um cabeçalho de uma hashtable*/
typedef struct head_table* HEAD_TABLE;

/**TYPE para definir uma posição/célula de uma hashtable*/
typedef struct celula* HashTable;

/*______________________________________________________________________*/

/** @brief Função que faz set da variavel final de um HT.
 *
 *  @param h Cabeçalho da hashtable.
 *  @param pos posição para adicionar o valor.
 *  @param val valor para adicionar.
 *  @return void.
 */

void setFinal (HEAD_TABLE h, int pos, int val);


/** @brief Função que faz get da quantidade de uma HT.
 *
 *  @param h Cabeçalho da hashtable.
 *  @param pos posição para procurar.
 *  @param col coluna do array para procurar.
 *  @return Quantidade encontrada.
 */

int getQuant (HEAD_TABLE h, int pos, int col);


/** @brief Função que encontra o status de uma posição de uma HT.
 *
 *  @param h Cabeçalho da hashtable.
 *  @param pos posição para adicionar o valor.
 *  @return status da posiçao pos.
 */

int getStatus(HEAD_TABLE h, int pos);


/** @brief Função que encontra o size de uma hashtable.
 *
 *  @param h Cabeçalho da hashtable.
 *  @return size da hashtable.
 */

int getSize (HEAD_TABLE h);


/** @brief Função que inicializa uma hashtable.
 *
 *  @param h Cabeçalho da hashtable.
 *  @param hsize_in tamanho inicial.
 *  @return void.
 */

HEAD_TABLE initTable (HEAD_TABLE h, int hsize_in);


/** @brief Função de hash para strings (explora o número da string).
 *
 *  @param key string para cálculo de hash.
 *  @param hsize tamanho da hashtable.
 *  @return key hashed.
 */

int hash_string (char *key, int hsize);


/** @brief Função que encontra uma posição livre numa HT (usa quadratic probing).
 *
 *  @param h Cabeçalho da hashtable.
 *  @param key string para encontrar posição.
 *  @return -1 caso não tenha posicao disponivel, >= 0 nos outros casos.
 */

int find_quad_probe (HEAD_TABLE h, char* key);


/** @brief Função que adiciona um elemento a uma hashtable.
 *
 *  @param h Cabeçalho da hashtable.
 *  @param key string para adicionar.
 *  @param filial parametro para adicionar.
 *  @param new_quant parametro para adicionar.
 *  @return void.
 */

void update (HEAD_TABLE h, char *key, int filial, int new_quant);


/** @brief Função que procura key numa hashtable.
 *
 *  @param h Cabeçalho da hashtable.
 *  @param key string para adicionar.
 *  @param hsize tamanho da hashtable.
 *  @return Posição encontrada.
 */

int lookup (HEAD_TABLE h, char* key, int hsize);


/** @brief Função que liberta memória de uma hashtable.
 *
 *  @param h Cabeçalho da hashtable.
 *  @return void.
 */

void free_hashtable (HEAD_TABLE h);


/** @brief Função que imprime um array de uma hashtable no ecrã.
 *
 *  @param array content da hashtable em si.
 *  @return void.
 */

void printArrayTable (int *array);


/** @brief Função que imprime uma hashtable no ecrã.
 *
 *  @param h cabeçalho da hashtable.
 *  @return void.
 */

void printTable (HEAD_TABLE h);


/** @brief Função que orderna uma hashtable.
 *
 *  @param h hashtable para ordenação.
 *  @param first primeira posição da hashtable
 *  @param last ultima posição da hashtable
 *  @return void.
 */

void quicksort(HEAD_TABLE h, int first, int last);


/** @brief Função que imprime uma hashtable no ecrã a partir da última posição.
 *
 *  @param array content da hashtable em si.
 *  @return void.
 */

void printNfirstTableReverse (HEAD_TABLE h, int n);

#endif
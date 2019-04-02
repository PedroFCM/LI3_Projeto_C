
/** @file lstring.h
*	@brief Ficheiro header do lstring.c.
*
*	@autor João Pedro Rodrigues Azevedo (A85227) 
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@bug Nenhum que tivessemos reparado.
*	
*/

/*______________________________________________________________________*/

#ifndef _LINKEDLIST_
#define _LINKEDLIST_

/*______________________________________________________________________*/

/*TYPE para simplificar a escrita*/
typedef struct node *LString;

/*______________________________________________________________________*/

/** @brief Função que imprime uma lista de strings no ecra.
 *
 *  @param l LString argumento para imprimir.
 *  @param flag muda o tipo de impressão (é usada de 2 maneiras diferentes).
 *  @return void.
 */

void printLString (LString l, int flag);


/** @brief Função que verifica se um elemento existe num LString.
 *
 *  @param elem elemento de procura.
 *  @param l LString.
 *  @return 1 se existir.
 */

int existLString (char* elem, LString l);


/** @brief Função que insere os parametros num LString.
 *
 *  @param l LString.
 *  @param elem string.
 *  @param vendidos int.
 *  @param preco double.
 *  @return LString após inserção.
 */
LString insertLString2 (LString l, char* elem, double total);
LString insertLString (LString l, char* elem, int vendidos, double preco);


/** @brief Função que retorna a tail de uma lista.
 *
 *  @param l LString.
 *  @return tail da LString l.
 */

LString getTail (LString l);


/** @brief Função que efetua a partition para a qSort.
 *
 *  @param head LString.
 *  @param end LString.
 *  @param *newHead LString.
 *  @param *newEnd LString.
 *  @param flag tipo de ordenação
 *  @return LString após partition.
 */

LString partitionLString (LString head, LString end, LString *newHead, LString *newEnd, int flag);


/** @brief Função auxiliar da quickSortL.
 *
 *  @param lhead LString.
 *  @param lfim string.
 *  @param flag tipo de ordenação.
 *  @return LString após ordenação.
 */

LString qSortLStringAux (LString lhead, LString lfim, int flag);


/** @brief Função que implementa o algoritmo quicksort.
 *
 *  @param l LString.
 *  @param flag tipo de ordenação.
 *  @return LString após ordenação.
 */

LString quickSortL (LString l, int flag);

#endif
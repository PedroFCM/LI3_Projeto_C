
/** @file stack.h
*	@brief Header file de stack.c
*
*	@autor João Pedro Rodrigues Azevedo (A85227) 
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@bug Nenhum que tivessemos reparado.
*	
*/

/*______________________________________________________________________*/

#ifndef _STACK_
#define _STACK_
/*______________________________________________________________________*/

typedef struct stack* Stack;

/** @brief Função que retorna o stack pointer.
 *
 *  @param s A stack.
 *  @return stack pointer.
 */

int getSP(Stack s);


/** @brief Função que initializa uma stack.
 *
 *  @param s para inicializar.
 *  @param n tamanho inicial da stack.
 *  @return A stack initializada.
 */

Stack initStack (Stack s, int n);


/** @brief Função verifica se uma stack é vazia.
 *
 *  @param s Stack.
 *  @return 1 se for vazia.
 */

int isEmpty (Stack s);


/** @brief Função que adiciona um elemento a uma stack.
 *
 *  @param s Stack.
 *  @param *new novo elemento.
 *  @return Stack após insercao.
 */

Stack push (Stack s, char *new);


/** @brief Função que elimina o elemento do topo da stack.
 *
 *  @param s Stack.
 *  @return void.
 */

void pop (Stack s);


/** @brief Função que duplica o tamanho de uma array com realloc.
 *
 *  @param s Stack.
 *  @return Stack duplicada.
 */

void doubleArray (Stack s);


/** @brief Função que faz free à memória usada pela stack.
 *
 *  @param s Stack.
 *  @return void.
 */

void freeStack (Stack s);


/** @brief Função que imprime a stack no ecrã.
 *
 *  @param s Stack.
 *  @return void.
 */

void printStack (Stack s);

#endif
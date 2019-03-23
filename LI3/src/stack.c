
/** @file stack.c
*	@brief Ficheiro que implementa uma STACK em C.
*
*	@autor João Pedro Rodrigues Azevedo (A85227) 
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@bug Nenhum que tivessemos reparado.
*	
*/

/*MACRO para suprimir warnings de strdup do <string.h>*/

#define _GNU_SOURCE

/*_________________BIBLIOTECAS STD IMPORTADAS________________________*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*_________________BIBLIOTECAS IMPLEMENTADAS____________________________*/

#include "stack.h"

/*______________________________________________________________________*/

/*Struct que implementa uma stack básica em C*/
struct stack {
	int size; 
	char **elements; /*ARRAY DE STRINGS GUARDADO NA STACK*/ 
	int ocurr;
	int sp;
};

/*______________________________________________________________________*/

int getSP (Stack s) {
	return s->sp;
}

Stack initStack (Stack s, int n) {
	s = (Stack) malloc (sizeof(struct stack));
	s -> elements = (char**) malloc(sizeof(char*)*n);
	s -> size = n;
	s -> sp = 0;

	return s;
}

int isEmpty (Stack s) {
	return s->sp==0;
}

Stack push (Stack s, char *new) {

	if (s -> sp == s -> size)
		doubleArray(s);

	s -> elements[s->sp++] = strdup(new);

	return s;
}

void pop (Stack s) {
	if (s -> sp > 0)
		free(s->elements[--s->sp]);
}

void doubleArray (Stack s) {
	s -> size *= 2;
	s -> elements = realloc (s -> elements, s->size);
}

void freeStack (Stack s) {
	int i;
	for (i = 0; i < s->sp; i++)
		free(s->elements[i]);

	free(s);
}

void printStack (Stack s) {
	int i;
	for (i = 0; i < s->sp; i++)
		printf("%s\n", s->elements[i]);
}
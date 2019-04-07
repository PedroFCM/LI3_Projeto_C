
/** @file lstring.c 
*	@brief Ficheiro que implementa um lista de strings em C.
*
*	@autor João Pedro Rodrigues Azevedo
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@bug Nenhum que tivessemos reparado.
*	
*/

/**MACRO para suprimir warnings de strdup do <string.h>*/
#define _GNU_SOURCE

/*----------------------------------------------------------------------*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*----------------------------------------------------------------------*/

#include "lstring.h"

/*----------------------------------------------------------------------*/

/**
* Struct que representa uma lista de elementos (linked list).
*/
struct node {
    
    char* val; /**< key para insercao. */
    int ocurr; /**< Numero de ocurrencias. */
    int vendidos; /**< Quantidade vendida. */
    double preco; /**< Preco ao qual foi vendido. */
    float total; /**< total faturado. */
    char *elem; /**< elemento para add. */
    char tipo; /**< tipo de venda. */

    struct node * next;

};

/*----------------------------------------------------------------------*/

int sizeLString (LString l) {
	
	int size = 0;
	LString *pt = &l;

	while ((*pt) != NULL) {
		pt = &((*pt) -> next);
		size++;	
	}

	return size;
}

void printLString (LString l, int flag) {

	LString *pt = &l;
	
	int i = 0;

	switch(flag) {
		case 0:
	    	while ((*pt) != NULL) {
		        printf("%s %f\n", (*pt)->val, (*pt)->total);
		    	pt = &((*pt) -> next);
		    }
		break;

		case 1:
	    	while (i < 3) {
		        printf("%s %f\n", (*pt)->val, (*pt)->total);
		    	pt = &((*pt) -> next);
		    	i++;
		    }
		    break;
		case 3:
	    	while ((*pt) != NULL) {
		        printf(" %s,", (*pt)->elem);
		    	pt = &((*pt) -> next);
		    }
		    break;

	}

}

int existLString (char* elem, LString l) {

	int r = 0;

	LString *pt = &l;

    while ((*pt) != NULL && r != 1) {

    	if (!strcmp(elem, (*pt) -> val)) r = 1;
	    
	    pt = &((*pt) -> next);
    }

    return r;
}

LString insertLString2 (LString l, char* elem, double total) {

	LString new = malloc (sizeof(struct node));
	LString *pt = &l;

    if(existLString(elem, *pt)){
	    
	    while (strcmp(elem, (*pt) -> val) != 0)
	    	pt = &((*pt) -> next);
    
	    (*pt) -> total += total;	    

	} else {
	  
	    while (*pt != NULL) pt = &((*pt) -> next);
	    
	    new -> val = strdup(elem);

	    new -> total = total;
	    new -> next = *pt;
	    *pt = new;
	} 

	return l;
}

LString pushLString (LString l, char* elem, char tipo) {

	LString new = malloc (sizeof(struct node));
	LString *pt = &l;


	while (*pt != NULL) pt = &((*pt) -> next);

	new -> elem = strdup(elem);
	new -> tipo = tipo;	
	new -> next = *pt;
	*pt = new;

	return l;
}


LString insertLString (LString l, char* elem, int vendidos, double preco) {

	LString new = malloc (sizeof(struct node));
	LString *pt = &l;

    if(existLString(elem, *pt)){
	    
	    while (strcmp(elem, (*pt) -> val) != 0)
	    	pt = &((*pt) -> next);

	    (*pt) -> ocurr++;	    
	    (*pt) -> vendidos+=vendidos;	    
	    (*pt) -> preco += preco*vendidos;	    

	} else {
	  
	    while (*pt != NULL) pt = &((*pt) -> next);
	    
	    new -> val = strdup(elem);
	    new -> ocurr = 1;
	    new -> vendidos = vendidos;
	    new -> preco = vendidos * preco;
	    new -> next = *pt;
	    *pt = new;
	} 

	return l;
}


LString getTail (LString l) {

	while (l != NULL && l->next != NULL)
		l = l -> next;

	return l;
}

LString partitionLString (LString head, LString end, LString *newHead, LString *newEnd, int flag) {

	LString pivot = end;
	LString prev = NULL, curr = head, tail = pivot;

	int compare = 0;

	while (curr != pivot) {

		switch (flag) {

			case 0: 
				compare = curr -> ocurr > pivot -> ocurr;
				break;
			case 1: 
				compare = curr -> total > pivot -> total;
				break;

		}

		if (compare) {
			
			if ((*newHead) == NULL) 
				(*newHead) = curr;

			prev = curr;
			curr = curr -> next;
		}
		else {

			if (prev != NULL)
				prev -> next = curr -> next;
			
			LString tmp = curr -> next;

			curr -> next = NULL;
			tail -> next = curr;
			tail = curr;
			curr = tmp;
		}
	}

	if ((*newHead)==NULL) 
		(*newHead) = pivot;

	(*newEnd) = tail;

	return pivot;
}

LString qSortLStringAux (LString lhead, LString lfim, int flag) {

	if (lhead == NULL || lhead == lfim)
		return lhead;

	LString newHead = NULL, newEnd = NULL;
	LString pivot = partitionLString (lhead, lfim, &newHead, &newEnd, flag);

	if (newHead != pivot) {

		LString tmp = newHead;
		while (tmp -> next != pivot)
			tmp = tmp -> next;

		tmp->next = NULL;

		newHead = qSortLStringAux(newHead, tmp, flag);

		tmp = getTail(newHead);
		tmp -> next = pivot;
	} 

	pivot -> next = qSortLStringAux(pivot -> next, newEnd, flag);

	return newHead;
}

LString quickSortL (LString l, int flag) {

	l = qSortLStringAux (l, getTail(l), flag);

	return l;
}

/*----------------------------------------------------------------------*/
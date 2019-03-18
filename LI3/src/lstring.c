#define _GNU_SOURCE

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "lstring.h"

void printLString (LString l) {

	LString *pt = &l;

    while ((*pt) != NULL) {

        printf("%s %d\n", (*pt)->val, (*pt)->ocurr);
    	pt = &((*pt) -> next);
    
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


LString insertLString (LString l, char* elem) {

	LString new = malloc (sizeof(struct node));
	LString *pt = &l;

    if(existLString(elem, *pt)){
	    
	    while (strcmp(elem, (*pt) -> val) != 0)
	    	pt = &((*pt) -> next);

	    (*pt) -> ocurr++;	    
	} else {
	  
	    while (*pt != NULL) pt = &((*pt) -> next);
	    
	    new -> val = strdup(elem);
	    new -> ocurr = 1;
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

LString partitionLString (LString head, LString end, LString *newHead, LString *newEnd) {

	LString pivot = end;
	LString prev = NULL, curr = head, tail = pivot;

	while (curr != pivot) {

		if (curr -> ocurr < pivot -> ocurr) {
			
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

LString qSortLStringAux (LString lhead, LString lfim) {

	if (lhead == NULL || lhead == lfim)
		return lhead;

	LString newHead = NULL, newEnd = NULL;
	LString pivot = partitionLString (lhead, lfim, &newHead, &newEnd);

	if (newHead != pivot) {

		LString tmp = newHead;
		while (tmp -> next != pivot)
			tmp = tmp -> next;

		tmp->next = NULL;

		newHead = qSortLStringAux(newHead, tmp);

		tmp = getTail(newHead);
		tmp -> next = pivot;
	} 

	pivot -> next = qSortLStringAux(pivot -> next, newEnd);

	return newHead;
}

LString quickSortL (LString l) {

	l = qSortLStringAux (l, getTail(l));

	return l;
}
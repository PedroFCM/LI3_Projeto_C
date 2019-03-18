#ifndef _LINKEDLIST_
#define _LINKEDLIST_


typedef struct node {
    
    char* val;
    int ocurr;
    struct node * next;

} *LString;

void printLString (LString l);

int existLString (char* elem, LString l);

LString insertLString (LString l, char* elem);

LString getTail (LString l);

LString partitionLString (LString head, LString end, LString *newHead, LString *newEnd);

LString qSortLStringAux (LString lhead, LString lfim);

LString quickSortL (LString l);

#endif
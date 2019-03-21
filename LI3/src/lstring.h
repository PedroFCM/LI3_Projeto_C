#ifndef _LINKEDLIST_
#define _LINKEDLIST_


typedef struct node {
    
    char* val;
    int ocurr;
    int vendidos;
    double preco;
    struct node * next;

} *LString;

void printLString (LString l, int flag);

int existLString (char* elem, LString l);

LString insertLString (LString l, char* elem, int vendidos, double preco);

LString getTail (LString l);

LString partitionLString (LString head, LString end, LString *newHead, LString *newEnd, int flag);

LString qSortLStringAux (LString lhead, LString lfim, int flag);

LString quickSortL (LString l, int flag);

#endif
#ifndef _STACK_
#define _STACK_

typedef struct stack {
	int size;
	char **elements;
	int sp;
} Stack;

Stack* initStack (Stack *s, int n);

int isEmpty (Stack *s);

Stack* push (Stack *s, char *new);

void pop (Stack *s);

void doubleArray (Stack *s);

#endif
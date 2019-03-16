#define _GNU_SOURCE

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "stack.h"

Stack* initStack (Stack *s, int n) {
	s = (Stack*) malloc (sizeof(struct stack));
	s -> elements = (char**) malloc(sizeof(char*)*n);
	s -> size = n;
	s -> sp = 0;

	return s;
}

int isEmpty (Stack *s) {
	return s->sp==0;
}

Stack* push (Stack *s, char *new) {
	printf("%s\n", new);
	if (s -> sp == s -> size)
		doubleArray(s);

	s -> elements[s->sp++] = strdup(new);

	return s;
}

void pop (Stack *s) {
	int r = 0;
	if (s -> sp == 0) r = 1;
	else free(s->elements[--s->sp]);
}

void doubleArray (Stack *s) {
	s -> size *= 2;
	s -> elements = realloc (s -> elements, s->size);
}


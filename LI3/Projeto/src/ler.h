#ifndef _LER_
#define _LER_

#define SIZE 64

typedef struct produtos {

	char *products;

} PROD, TableProd[200000];

int read_products (char *filename, TableProd t);
void print_struct (TableProd t, int counter);

#endif
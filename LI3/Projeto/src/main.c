#include <stdio.h>
#include <stdlib.h>

#include "ler.h"

int main () {

	TableProd t;
	int i = read_products("Produtos.txt", t);
	print_struct(t, i);
	printf("\ncounter=%d\n", i);
	
	return 0;

}
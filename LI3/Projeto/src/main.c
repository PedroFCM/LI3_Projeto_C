#include <stdio.h>
#include <stdlib.h>

#include "ler.h"

int main () {
	
	FILE_SETTINGS *set = malloc(sizeof(struct ficheiros)); 

	char *produtos[200000];
	
	readNvalidate_products("datafiles/Produtos.txt", produtos, set);
	print_products(produtos, set);
	write_products_on_file(produtos, set);
	return 0;

}
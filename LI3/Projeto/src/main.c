#include <stdio.h>
#include <stdlib.h>

#include "ler.h"

int main () {
	
	FILE_SETTINGS *set = malloc(sizeof(struct ficheiros)); 

	char *produtos[200000];
	char *clientes[20000];
	char *vendas[1000000];

	//readNvalidate_products("datafiles/Produtos.txt", produtos, set);
	//print_products(produtos, set);
	//write_products_on_file(produtos, set);

	//readNvalidate_clients("datafiles/Clientes.txt", clientes, set);
	//print_clients(clientes, set);
	//write_clients_on_file(clientes, set);

	readNvalidate_sells("datafiles/Vendas_1M.txt", vendas, set);
	print_sells(vendas, set);
	write_sells_on_file(vendas, set);
	
	return 0;

}
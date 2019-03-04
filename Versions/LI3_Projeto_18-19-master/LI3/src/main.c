#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "produtos_read_write.h"
#include "clientes_read_write.h"
#include "vendas_read_write.h"

int main () {
	
	printf("_STARTING_\n");
	
	//_______________________________________________________//

	GLOBAL *set = malloc(sizeof(struct settings)); 

	char **products = (char**) malloc(sizeof(char*) * 200000);
	char **clients = (char**) malloc(sizeof(char*) *  20000);
	char **sells;

	printf("_variables alocated_\n");
	
	//_______________________________________________________//

	readNvalidate_products(PROD_PATH, products, set);
	write_products_on_file(products, set);

	printf("_PRODs_DONE_\n");

	readNvalidate_clients(CLIE_PATH, clients, set);
	write_clients_on_file(clients, set);

	printf("_CLIENTs_DONE_\n");
	
	sells = readNvalidate_sells(SELL_PATH, sells, set, products, clients);
	write_sells_on_file(sells, set);
	
	printf("_SELLs_DONE_\n");
	
	//_______________________________________________________//

	free(set);
	free(products);
	free(clients);

	//_______________________________________________________//
	
	printf("_END_\n");

	return 0;
}
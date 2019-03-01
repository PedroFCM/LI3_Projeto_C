#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "produtos_read_write.h"
#include "clientes_read_write.h"
#include "vendas_read_write.h"
#include "avlstruct.h"

int main () {
	
	//_______________________________________________________//

	GLOBAL *set = malloc(sizeof(struct settings)); 

	AVL *products = NULL;

	//_______________________________________________________//

	products = readNvalidate_products(PROD_PATH, products, set);
	preorder_avl(products);

	// write_products_on_file(products, set);

	// printf("_PRODs_DONE_\n");

	// readNvalidate_clients(CLIE_PATH, clients, set);
	// write_clients_on_file(clients, set);

	// printf("_CLIENTs_DONE_\n");
	
	// sells = readNvalidate_sells(SELL_PATH, sells, set, products, clients);
	// write_sells_on_file(sells, set);
	
	// printf("_SELLs_DONE_\n");
	
	// //_______________________________________________________//

	// free(set);
	free(products);
	// free(clients);

	// //_______________________________________________________//
	
	// printf("_END_\n");

	return 0;
}
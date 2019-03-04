#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"
#include "produtos_read_write.h"
#include "clientes_read_write.h"
#include "vendas_read_write.h"
#include "avlstruct.h"

int main () {
	
	//_______________________________________________________//

	GLOBAL *set = malloc(sizeof(struct settings)); 

	AVL *products = NULL;
	AVL *clients  = NULL;
	AVL *sells    = NULL;

	//_______________________________________________________//

	products = readNvalidate_products(PROD_PATH, products, set);
	write_inorder_avl_on_file(VAL_PROD_PATH, products, set);
	//inorder_avl(products);
	
	clients = readNvalidate_clients(CLIE_PATH, clients, set);
	write_inorder_avl_on_file(VAL_CLIE_PATH, clients, set);
	//inorder_avl(clients);
	
	sells = readNvalidate_sells(SELL_PATH, sells, set, products, clients);
	write_inorder_avl_on_file(VAL_SELL_PATH, sells, set);
	//inorder_avl(sells);

	// //_______________________________________________________//

	free(products);
	free(clients);
	free(sells);
	
	free(set);
		
	return 0;
}
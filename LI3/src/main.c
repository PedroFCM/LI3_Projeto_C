#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "global.h"
#include "produtos_read_write.h"
#include "clientes_read_write.h"
#include "vendas_read_write.h"
#include "avlstruct.h"

int main () {
	
	clock_t start, end;
	double cpu_time_used;
	start = clock();

	GLOBAL *set = (GLOBAL*) malloc(sizeof(struct settings)); 

	AVL *products = NULL;
	AVL *clients  = NULL;
	AVL *sells    = NULL;


	products = readNvalidate_products(PROD_PATH, products, set);
	write_inorder_avl_on_file(VAL_PROD_PATH, products, set);
	
	clients = readNvalidate_clients(CLIE_PATH, clients, set);
	write_inorder_avl_on_file(VAL_CLIE_PATH, clients, set);
	
	sells = readNvalidate_sells(SELL_PATH, sells, set, products, clients);
	write_inorder_avl_on_file(VAL_SELL_PATH, sells, set);
	
	show_stats_vendas(set);
	
	free(products);
	free(clients);
	free(sells);
	
	free(set);
		
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("\nCPU Time = %f\n\n", cpu_time_used );
	
	return 0;
}
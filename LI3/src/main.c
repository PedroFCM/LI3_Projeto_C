#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

#include "global.h"
#include "produtos_read_write.h"
#include "clientes_read_write.h"
#include "vendas_read_write.h"
#include "avlstruct.h"
#include "hashtables.h"

int main () {
	 
	/*_______________MEDIR TEMPOS_____________________*/

	clock_t start, end;
	double cpu_time_used;
	start = clock();
	
	/*_________________PROGRAM_____________________*/

	GLOBAL *set = (GLOBAL*) malloc(sizeof(struct settings)); 

	HashTable products, clients;
	AVL sells = NULL;
	
	products = initTable (products, HSIZE_PRODS);
	clients  = initTable (clients,  HSIZE_CLIEN);
	
	/*______________________________________________*/
	
	products = readNvalidate_products (PROD_PATH, products, set);
	write_HashTable(VAL_PROD_PATH, products, HSIZE_PRODS);

	clients  = readNvalidate_clients (CLIE_PATH, clients, set);
	write_HashTable(VAL_CLIE_PATH, clients, HSIZE_CLIEN);	

	sells = readNvalidate_sells(SELL_PATH, sells, set, products, clients);
	write_inorder_avl_on_file(VAL_SELL_PATH, sells, set);
	
	/*______________________________________________*/
	
	show_stats_vendas(set);

	/*______________________________________________*/
	
	free_hashtable(products, HSIZE_PRODS);
	free(products);
	free_hashtable(clients, HSIZE_CLIEN);
	free(clients);
	free(sells);
	
	free(set);

	/*______________________________________________*/
	
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("\nCPU Time = %f seconds.\n\n", cpu_time_used );
	
	return 0;
}
#ifndef _LER_
#define _LER_

typedef struct ficheiros {
	int num_prods, num_clients, num_sells;
	int prods_val, val_clients, val_sells;
	int nulo;
} FILE_SETTINGS;

void print_products (char *produtos[], FILE_SETTINGS *set);
void readNvalidate_products (char* filename, char *produtos[], FILE_SETTINGS *set);
int  verify_product (char *product);
void write_products_on_file (char *produtos[], FILE_SETTINGS *set);

#endif
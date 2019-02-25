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

void readNvalidate_clients (char *filename, char *clientes[], FILE_SETTINGS *set);
int verify_client (char *client);
void print_clients (char *clients[], FILE_SETTINGS *set);
void write_clients_on_file (char *clients[], FILE_SETTINGS *set);

int verify_sell (char *sell);
int numb_spaces_in_string (char *str);
void readNvalidate_sells (char* filename, char *sells[], FILE_SETTINGS *set);
void print_sells (char *sells[], FILE_SETTINGS *set);
void write_sells_on_file (char *sells[], FILE_SETTINGS *set);

#endif
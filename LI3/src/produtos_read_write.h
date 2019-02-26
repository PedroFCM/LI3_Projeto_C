#ifndef _PRODUTOSRW_
#define _PRODUTOSRW_

#include "global.h"

//_______________________________________________________//

int verify_product (char *product);

void readNvalidate_products (char* filename, char **produtos, GLOBAL *set);

void print_products (char **produtos, GLOBAL *set);

void write_products_on_file (char **produtos, GLOBAL *set);

#endif
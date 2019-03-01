#ifndef _PRODUTOSRW_
#define _PRODUTOSRW_

#include "global.h"
#include "avlstruct.h"

//_______________________________________________________//

int verify_product (char *product);

AVL* readNvalidate_products (char* filename, AVL *prod, GLOBAL *set);

void print_products (char **produtos, GLOBAL *set);

void write_products_on_file (char **produtos, GLOBAL *set);

int preorder_avl (AVL *a);

#endif
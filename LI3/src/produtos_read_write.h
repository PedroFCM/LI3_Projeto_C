#ifndef _PRODUTOSRW_
#define _PRODUTOSRW_

#include "global.h"
#include "avlstruct.h"

//_______________________________________________________//

int verify_product (char *product);

AVL* readNvalidate_products (char* filename, AVL *prod, GLOBAL *set);

#endif
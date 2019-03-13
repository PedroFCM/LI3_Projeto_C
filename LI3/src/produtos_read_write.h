#ifndef _PRODUTOSRW_
#define _PRODUTOSRW_

#include "global.h"
#include "avlstruct.h"
#include "hashtables.h"

int verify_product (char *product);

//AVL* readNvalidate_products (char* filename, AVL *prod, GLOBAL *set);

HashTable readNvalidate_products (char* filename, HashTable prod, GLOBAL *set);
//HashTableChain readNvalidate_products (char* filename, HashTableChain prod, GLOBAL *set);

#endif
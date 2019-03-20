#ifndef _SELLS_
#define _SELLS_

#include "global.h"
#include "avlstruct.h"

int verify_sell (CAT_VENDAS vendas, AVL prod, AVL client, GLOBAL set, char *sell, REGISTO reg);

CAT_VENDAS readNvalidate_sells (char* filename, CAT_VENDAS sells, GLOBAL set, AVL prod, AVL cli);

#endif
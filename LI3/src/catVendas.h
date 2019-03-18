#ifndef _SELLS_
#define _SELLS_

#include "global.h"

int verify_sell (AVL vendas, char *sell, AVL prod, AVL client, GLOBAL set);

AVL readNvalidate_sells (char* filename, AVL sells, GLOBAL set, AVL prod, AVL cli);

#endif
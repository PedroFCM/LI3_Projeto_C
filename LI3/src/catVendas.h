#ifndef _SELLS_
#define _SELLS_

#include "global.h"
#include "avlstruct.h"

int verify_sell (AVL vendas, AVL prod, AVL client, GLOBAL set, char *sell, REGISTO reg);

AVL readNvalidate_sells (char* filename, AVL sells, GLOBAL set, AVL prod, AVL cli);

#endif
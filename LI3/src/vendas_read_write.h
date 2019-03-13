#ifndef _SELLS_
#define _SELLS_

#include "global.h"

char** tokenizeSELL_LINE (char *sell, char** campos);

int verify_sell (char *sell, HashTable prod, HashTable client, GLOBAL *set);

AVL readNvalidate_sells (char* filename, AVL sells, GLOBAL *set, HashTable prod, HashTable cli);

#endif
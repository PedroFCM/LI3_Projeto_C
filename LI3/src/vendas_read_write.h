#ifndef _SELLS_
#define _SELLS_

#include "global.h"

char** tokenizeSELL_LINE (char *sell, char** campos);

int verify_sell (char *sell, AVL* prod, AVL* client, GLOBAL *set);

AVL* readNvalidate_sells (char* filename, AVL* sells, GLOBAL *set, AVL* prod, AVL* cli);

#endif
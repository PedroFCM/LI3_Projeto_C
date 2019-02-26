#ifndef _SELLS_
#define _SELLS_

#include "global.h"

//_______________________________________________________//


int verify_sell (char *sell, char **prod, char **client, GLOBAL *set);

char** readNvalidate_sells (char* filename, char **sells, GLOBAL *set, char **prod, char **cli);

void print_sells (char **sells, GLOBAL *set);

void write_sells_on_file (char **sells, GLOBAL *set);

#endif
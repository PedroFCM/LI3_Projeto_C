#ifndef _CLIENTESRW_
#define _CLIENTESRW_

#include "global.h"
#include "avlstruct.h"
#include "hashtables.h"

int verify_client (char *client);

HashTable readNvalidate_clients (char *filename, HashTable clients, GLOBAL *set);

#endif
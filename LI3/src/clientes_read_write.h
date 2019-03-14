#ifndef _CLIENTESRW_
#define _CLIENTESRW_

#include "global.h"
#include "avlstruct.h"

int verify_client (char *client);

AVL readNvalidate_clients (char *filename, AVL clients, GLOBAL set);

#endif
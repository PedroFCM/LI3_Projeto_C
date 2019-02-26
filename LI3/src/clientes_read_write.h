#ifndef _CLIENTESRW_
#define _CLIENTESRW_

#include "global.h"

int verify_client (char *client);

void readNvalidate_clients (char *filename, char **clientes, GLOBAL *set);

void print_clients (char **clients, GLOBAL *set);

void write_clients_on_file (char **clients, GLOBAL *set);

#endif
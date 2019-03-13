#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "global.h"
#include "clientes_read_write.h"
#include "avlstruct.h"
#include "hashtables.h"

int verify_client (char *client) {
	
	char *aux = strdup(client);
	int r = 0, num_client  = atoi (aux+1);

		if (num_client >= 1000 && num_client <= 5000)
			if (isupper(aux[0]) &&
				isdigit(aux[1]) && isdigit(aux[2]) &&
				isdigit(aux[3]) && isdigit(aux[4]) &&
				!isdigit(aux[5])) r = 1;
	return r;
}

HashTable readNvalidate_clients (char *filename, HashTable clients, GLOBAL *set) {

	FILE *fp = fopen(filename, "r");

	int max = biggest_line_in_file(filename);
	int validos = 0, i = 0;			

	char *buffer = (char*) malloc(sizeof(char) * (max + 10));

	while (fgets(buffer, max, fp)) {
	
		if (verify_client(buffer)) {

			clients = update(clients, buffer, HSIZE_CLIEN, 1);
			
			validos++;
		}
		
		i++;
	}
	
	free(buffer);

	set -> num_clients      = i;
	set -> val_clients      = validos;
	set -> max_line_clients = max; 

	fclose(fp);

	return clients;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "global.h"
#include "clientes_read_write.h"

//_______________________________________________________//

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

void readNvalidate_clients (char *filename, char **clients, GLOBAL *set) {

	FILE *fp = fopen(filename, "r");

	int max_size_line = biggest_line_in_file(filename);

	char *buffer = (char*) malloc(sizeof(char) * max_size_line);
	int validos = 0, i=0;			

	while (fgets(buffer, max_size_line, fp)) {
		
		if (verify_client(buffer)) {
			clients[validos] = strdup(buffer);
			validos++;
		}
		
		i++;
	}
	
	free(buffer);

	set -> num_clients      = i;
	set -> val_clients      = validos;
	set -> max_line_clients = max_size_line; 
}

void write_clients_on_file (char **clients, GLOBAL *set) {

	FILE *fp = fopen(VAL_PROD_PATH, "w");

	int i = 0, size = set->val_clients;

	while (i<size) {
		fprintf(fp, "%s", clients[i]);
		i++;
	}
}



//_______________________________________________________//



void print_clients (char **clients, GLOBAL *set) {

	int i=0, size = set -> val_clients;
	
	while (i < size) {
		printf("%s", clients[i]);
		i++;
	}	
}

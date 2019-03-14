#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "global.h"
#include "clientes_read_write.h"
#include "avlstruct.h"

int verify_client (char *client) {
	
	int r = 0;
	int num_client = atoi (client+1);

	r = (num_client >= 1000 && num_client <= 5000); 

	r = r && is_uppercase(client[0]) && is_number(client[1]) && 
			 is_number(client[2]) 	 && is_number(client[3]) && 
			 is_number(client[4])    && !is_number(client[5]) &&
			 !is_uppercase(client[5]);
	
	return r;
}

AVL readNvalidate_clients (char *filename, AVL clients, GLOBAL set) {

	FILE *fp = fopen(filename, "r");

	int max = biggest_line_in_file(filename);
	
	set -> num_clients      =   0;
	set -> max_line_clients = max; 
	set -> val_clients      =   0;

	char *buffer = (char*) malloc(sizeof(char) * (2 * max));

	while (fgets(buffer, max, fp)) {
		
		if (verify_client(buffer)) {

			clients = updateAVL(clients, buffer);
			
			set -> val_clients++;
		}
		
		set -> num_clients++;
	}
	
	free(buffer);

	fclose(fp);

	return clients;
}
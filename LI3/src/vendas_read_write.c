#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "global.h"
#include "produtos_read_write.h"
#include "clientes_read_write.h"

int verify_sell (char *sell, AVL prod, AVL client, GLOBAL set) {
	
	int r = 1;

	char *aux = strdup(sell);
	
	if (numb_spaces_in_string(aux) == 6) {

		char **campos = (char**) malloc(sizeof(char*) * CAMPOS_SELLS);
		
		int ind = 1;
		campos[0] = NULL;

		char *token = strtok(aux, " ");
		
		while (token) {	
			campos[ind++] = strdup(token);
			token = strtok(NULL, " ");
		}

		double price; 
		sscanf(campos[2], "%lf", &price);
		r = r && (price >= 0.0 && price <= 999.99);

		int sold = atoi (campos[3]);
		r = r && (sold >= 1 && sold <= 200); 
		
		r = r && (campos[4][0] == 'P' || campos[4][0] == 'N'); 
	
		int month = atoi(campos[6]);
		r = r && (month >= 1 && month <= 12); 

		int filial = atoi(campos[7]);
		r = r && (filial >= 1 && filial <= 3); 

		r = r && exist_element(prod, campos[1]) && 
		    	 exist_element(client, campos[5]);
		
		free(campos);	
	}

	free(aux);

	return r;
}

AVL readNvalidate_sells (char* filename, AVL sells, GLOBAL set, AVL prod, AVL cli) {

	FILE *fp = fopen(filename, "r");
	
	int max = biggest_line_in_file(filename);	
	
	set -> max_line_sells = max;
	set -> num_sells      =   0;
	set -> val_sells      =   0;

	char *buffer = (char*) malloc(sizeof(char) * (2* max));

	while (fgets(buffer, max, fp)) {
		
		if (verify_sell(buffer, prod, cli, set)) {
			
			sells = updateAVL(sells, buffer);

			set -> val_sells++;
		}

		set -> num_sells++;
	}
	
	free(buffer);

	fclose(fp);
	
	return sells;
}
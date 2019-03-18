#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "global.h"

int verify_sell (char *sell, AVL prod, AVL client, GLOBAL set) {
	
	int r = 1;

	char *aux = strdup(sell);
	
	if (numb_spaces_in_string(aux) == 6) {

		char *token = strtok(aux, " ");
		r = r && exist_element(prod, token);

		token = strtok(NULL, " ");
		double price; 
		sscanf(token, "%lf", &price);
		r = r && (price >= 0.0 && price <= 999.99);

		token = strtok(NULL, " ");
		int sold = atoi (token);
		r = r && (sold >= 1 && sold <= 200); 
		
		token = strtok(NULL, " ");
		r = r && (token[0] == 'P' || token[0] == 'N'); 
		
		token = strtok(NULL, " ");
		r = r && exist_element(client, token);
	
		token = strtok(NULL, " ");
		int month = atoi(token);
		r = r && (month >= 1 && month <= 12); 

		token = strtok(NULL, " ");
		int filial = atoi(token);
		r = r && (filial >= 1 && filial <= 3); 
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
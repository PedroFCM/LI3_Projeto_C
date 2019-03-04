#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "global.h"
#include "produtos_read_write.h"
#include "clientes_read_write.h"

//_______________________________________________________//

int verify_sell (char *sell, char **prod, char **client, GLOBAL *set) {
	
	int valid = 0;

	char *aux = strdup(sell);
	
	if (numb_spaces_in_string(aux) == 6) {

		char *store;

		store = strtok(aux, " ");
		valid = verify_product(store); 
		//valid = valid && exist_element(0, store, prod, client, set);

		store = strtok(NULL, " ");
		float price;
		sscanf(store, "%f", &price);
		valid = valid && (price >= 0.0 && price <= 999.99); 
		
		store = strtok(NULL, " ");
		int sold = atoi (store);
		valid = valid && (sold >= 1 && sold <= 200); 
		
		store = strtok(NULL, " ");
		valid = valid && (!strcmp(store, "P") || !strcmp(store, "N")); 
		
		store = strtok(NULL, " ");
		valid = valid && verify_client(store); 
		//valid = valid && exist_element(1, store, prod, client, set);		

		store = strtok(NULL, " ");
		int month = atoi(store);
		valid = valid && (month >= 1 && month <= 12); 

		store = strtok(NULL, " ");
		int filial = atoi(store);
		valid = valid && (filial >= 1 && filial <= 3); 
	}

	return valid;
}

char** readNvalidate_sells (char* filename, char **sells, GLOBAL *set, char **prod, char **cli) {
	
	FILE *fp = fopen(filename, "r");
	
	int max = biggest_line_in_file(filename);

	char *buffer = (char*) malloc(sizeof(char)*max);
	int validos = 0, i = 0;

	while (fgets(buffer, max, fp)) {
		if (verify_sell(buffer, prod, cli, set)) {
			sells = (char**) realloc(sells, (validos+1000)*sizeof(char*));
			sells[validos] = strdup(buffer);
			validos++;
		}
		i++;
	}
	
	free(buffer);

	set -> num_sells = i;
	set -> val_sells = validos;

	return sells;
}

void write_sells_on_file (char **sells, GLOBAL *set) {

	FILE *fp = fopen(VAL_SELL_PATH, "w");
	int i = 0, size = set->val_sells;

	while (i<size) {
		fprintf(fp, "%s", sells[i]);
		i++;
	}
}


//_______________________________________________________//


void print_sells (char **sells, GLOBAL *set) {

	int i=0, size = set -> val_sells;
	
	while (i < size) {
		printf("%s", sells[i]);
		i++;
	}
}

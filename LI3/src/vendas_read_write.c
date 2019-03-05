#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "global.h"
#include "produtos_read_write.h"
#include "clientes_read_write.h"

//_______________________________________________________//

char** tokenizeSELL_LINE (char *sell, char** campos) {

	int ind = 1;
	campos[0] = NULL;

	char *token = strtok(sell, " ");
	
	while (!(token==NULL)) {
	
		campos[ind] = strdup(token);
		token = strtok(NULL, " ");
		ind++;

	}

	return campos;
}

int verify_sell (char *sell, AVL* prod, AVL* client, GLOBAL *set) {
	
	int valid = 1;

	char *aux = strdup(sell);

	if (numb_spaces_in_string(aux) == 6) {

		char **campos = malloc(sizeof(char*) * CAMPOS_SELLS);
		campos = tokenizeSELL_LINE(aux, campos);

		valid = verify_product(campos[1]) && exist_element(prod, campos[1]);

		float price; sscanf(campos[2], "%f", &price);
		valid = valid && (price >= 0.0 && price <= 999.99);

		int sold = atoi (campos[3]);
		valid = valid && (sold >= 1 && sold <= 200); 
		
		valid = valid && (!strcmp(campos[4], "P") || !strcmp(campos[4], "N")); 
	
		valid = valid && verify_client(campos[5]) && exist_element(client, campos[5]);
		
		int month = atoi(campos[6]);
		valid = valid && (month >= 1 && month <= 12); 

		int filial = atoi(campos[7]);
		valid = valid && (filial >= 1 && filial <= 3); 

		free(campos);
	}

	return valid;
}

AVL* readNvalidate_sells (char* filename, AVL* sells, GLOBAL *set, AVL* prod, AVL* cli) {
	
	FILE *fp = fopen(filename, "r");
	
	int max = biggest_line_in_file(filename);
	int validos = 0, i = 0;

	char *buffer = (char*) malloc(sizeof(char)*max);

	while (fgets(buffer, max, fp)) {

		if (verify_sell(buffer, prod, cli, set)) {

			sells = updateAVL(sells, buffer);

			validos++;
		}

		i++;
	}
	
	free(buffer);

	set -> num_sells      = i;
	set -> val_sells      = validos;
	set -> max_line_sells = max;

	fclose(fp);

	return sells;
}
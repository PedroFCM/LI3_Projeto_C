#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "global.h"

/* -------------------ANOTACOES--------------------------

cat datafiles/Produtos.txt | uniq -u | wc -l

TODO:...

---------------------------------------------------------*/
//_______________________________________________________//

//ficheiros windows \r + \n
int biggest_line_in_file (char *filename) {

	FILE *fp = fopen(filename, "r");

	char *buffer = (char*) malloc(sizeof(char)*64);
	int biggest=0, current=0;

	while (fgets(buffer, 64, fp)) {

		current = 1 + strlen(buffer);

		if (current > biggest) biggest = current;
	}
	
	free(buffer);

	return biggest;
}

int numb_spaces_in_string (char *str) {

	int i, spaces = 0;
	
	for (i=0; str[i]; i++)
		if (str[i]==' ') spaces++;
	
	return spaces;
}

int exist_element (int flag, char *element, char **prod, char **cli, GLOBAL *set) {

	int i, size;

	switch (flag) {
		case 0: size = set -> val_prods;	
			for (i = 0; i < size; i++) {
				if (!strcmp(prod[i], element))
					return 1;
			}
			break;
	
		case 1: size = set -> val_clients;
			for (i = 0; i < size; i++) {
				if (!strcmp(cli[i], element))
					return 1;
			}
			break;
	
		default: break;
	}

	return 0;
}

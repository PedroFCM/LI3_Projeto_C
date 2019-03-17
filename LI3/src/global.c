/** @file global.c
*	@brief Ficheiro que contém funções auxiliares ao projeto.
*
*	@autor João Pedro Rodrigues Azevedo (A85227) 
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@bug Nenhum que tivessemos reparado.
*	
*/

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "global.h"
#include "avlstruct.h"

char** tokenize (char** campos, char* sell) {
		
		char *aux = strdup(sell);
	
		int ind = 1; 
		char *token;

		campos[0] = NULL;
		token = strtok(aux, " ");
		
		while (token) {	
			campos[ind++] = strdup(token);
			token = strtok(NULL, " ");
		}

		return campos;
}

char* string_cut_extra_char (char *entry) {

	entry[(strlen(entry))-1] = '\0';

	return entry;
}

int is_uppercase (char ch) {

	return (ch>='A' && ch <= 'Z');

}

int is_number (char ch) {

	return (ch>='0' && ch<='9'); 

}

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

int exist_element (AVL a, char *element) {
 
	int r = 0;
	
	char *aux;

	while (a != NULL) {
		
		aux = strndup(a->tag, strlen(element));
		
		r = strcmp(aux, element);
				
		if (r == 0) return 1;
		else if (r > 0) a = a -> left;
		else if (r < 0) a = a -> right;
		
		free(aux);
	}

	return 0;
}

void write_recursive (AVL a, FILE *fp) {

	if (a != NULL) {
		write_recursive (a -> left , fp);
		fprintf(fp, "%s", a -> tag);
		write_recursive (a -> right, fp);
	}
}

void write_inorder_avl_on_file (char *filepath, AVL a, GLOBAL set) {

	FILE *fp = fopen(filepath, "w");

	write_recursive (a, fp);

	fclose(fp);

}

void inorder_avl (AVL a) {

	if (a != NULL) {
		inorder_avl(a -> left);
		printf("%s", a -> tag);
		inorder_avl(a -> right);
	}
}
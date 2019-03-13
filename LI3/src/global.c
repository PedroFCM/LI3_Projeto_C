#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "global.h"
#include "avlstruct.h"
#include "hashtables.h"

/* -------------------ANOTACOES--------------------------

cat datafiles/Produtos.txt | uniq -u | wc -l

TODO:...

ficheiros windows \r + \n
*/

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

int exist_element (HashTable t, char *tag, int hsize, int key_hash) 
{ 
	return lookup(t, tag, hsize, key_hash);
}

void write_recursive (AVL a, FILE *fp) {

	if (a != NULL) {
		write_recursive (a -> left , fp);
		fprintf(fp, "%s", a -> tag);
		write_recursive (a -> right, fp);
	}
}

void write_inorder_avl_on_file (char *filepath, AVL a, GLOBAL *set) {

	FILE *fp = fopen(filepath, "w");

	write_recursive (a, fp);

	fclose(fp);

}

void write_HashTable(char* filepath, HashTable t, int hsize)
{
	FILE* fp = fopen(filepath,"w");
	int i = 0;


	while(i <  hsize)
	{
		if(t[i].status == USED)
			fprintf(fp, "%s\n", t[i].element);
		i++;
	}

	fclose(fp);
}


void inorder_avl (AVL a) {

	int i = 0;

	if (a != NULL) {
		inorder_avl(a -> left);
		printf("%s", a -> tag);
		inorder_avl(a -> right);
	}
}

void show_stats_vendas (GLOBAL *set) {
	printf("\nLinha mais longa venda : %d\n", set->max_line_sells);
	printf("Produtos envolvidos : %d\n", set->val_prods);
	printf("Clientes envolvidos : %d\n", set->val_clients);
	printf("Vendas efectivas (válidas) : %d\n", set->val_sells);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "global.h"
#include "avlstruct.h"

/* -------------------ANOTACOES--------------------------

cat datafiles/Produtos.txt | uniq -u | wc -l

TODO:...
*/

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

int exist_element (AVL *a, char *element) {
 
 	AVL *b = (AVL*) malloc(sizeof(struct avl));
	b = a;
	int len = 0, r = 0;
	
	char *aux = (char*) malloc(sizeof(char)*20);

	while (b != NULL) {
		
		strncpy(aux, b->tag, strlen(b->tag)-2);
		
		r = strcmp(aux, element);
				
		if (r == 0) return 1;
		else if (r > 0) b = b -> left;
		else if (r < 0) b = b -> right;

	}

	free(aux);
	free(b);

	return 0;
}

void write_recursive (AVL *a, FILE *fp) {

	if (a != NULL) {
		write_recursive (a -> left , fp);
		fprintf(fp, "%s", a -> tag);
		write_recursive (a -> right, fp);
	}
}

void write_inorder_avl_on_file (char *filepath, AVL *a, GLOBAL *set) {

	FILE *fp = fopen(filepath, "w");

	write_recursive (a, fp);

	fclose(fp);

}

void inorder_avl (AVL *a) {

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
	// printf("Ultimo cliente : %s\n", "TODO");
	// printf("Numero de vendas para este cliente: %d\n", 0);
	// printf("Numero de vendas na Filial 1 : %d\n", 0);
	// printf("Numero de vendas na Filial 2 : %d\n", 0);
	// printf("Numero de clientes c/ cod. começado por A, B,...\n");
	// printf("Faturação total : %d\n", 0);
}
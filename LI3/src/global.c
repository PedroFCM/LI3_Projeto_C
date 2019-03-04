#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "global.h"
#include "avlstruct.h"

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

int exist_element (AVL *a, char *element) {
 
	int len = 0, r = 0;

	while (a != NULL) {
		if (!strcmp(a->tag, element)) return 1;
		else if (strcmp(a->tag, element) > 0) a = a -> left;
		else if (strcmp(a->tag, element) < 0) a = a -> right;
	}

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
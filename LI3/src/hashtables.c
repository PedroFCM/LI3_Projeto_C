
/** @file hashtables.c
*	@brief Ficheiro que implementa uma hashtable para implementar procuras eficientes.
*
*	@autor João Pedro Rodrigues Azevedo 
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@bug Nenhum que tivessemos reparado.
*	
*/

/**MACRO para suprimir warnings de strdup do <string.h>*/
#define _GNU_SOURCE

/*----------------------------------------------------------------------*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*----------------------------------------------------------------------*/

#include "hashtables.h"

/*----------------------------------------------------------------------*/

/**
* Celula de uma HashTable.
*/
struct celula {
	/*@{*/
	char *entry; /**< elemento string. */
	int total_quant[3]; /**< array de quantidade vendida por filial. */
	int total_client[3]; /**< array de registos venda. */
	int final; /**< quantidade total. */
	int status; /**< macro para indicar se esta ocupada/free/deleted. */
	/*@}*/
};

/**
* Struct para representar o cabeçalho de uma hashtable.
*/
struct head_table {
	/*@{*/	
	int hsize; /**< size da hashtable. */
	HashTable content; /**< array de celulas == hashtable. */
	/*@}*/
};

/*----------------------------------------------------------------------*/

int getQuant (HEAD_TABLE h, int pos, int col) {
	return h->content[pos].total_quant[col];
}

void setFinal (HEAD_TABLE h, int pos, int val) {
	h->content[pos].final = val;
}

int getStatus(HEAD_TABLE h, int pos) {
	return h->content[pos].status;
}

int getSize (HEAD_TABLE h) {
	return h->hsize;
}

HEAD_TABLE initTable (HEAD_TABLE h, int hsize_in) {
	
	h = (HEAD_TABLE) malloc (sizeof(struct head_table));
	h -> content = (HashTable) malloc (sizeof(struct celula) * 200000);
	h -> hsize = hsize_in;

	int i;

	for (i = 0; i < hsize_in; i++) {
		h->content[i].status = FREE;
	}

	return h;
}

int hash_string (char *key, int hsize) {
	
	int k, res = 0;
	char *new = (char*) malloc(sizeof(char)*10);
			
	k = key[0] + key[1];
	sprintf(new, "%d%s", k, key+2);
 	res = atoi(new) - 66000;
 		
	free(new);
	
	return (res % hsize);
}

int find_quad_probe (HEAD_TABLE h, char* key) {
	
	int p = hash_string (key, h->hsize);
	int count, d=2;

	for (count = h->hsize; count > 0 && h->content[p].status!=DELETED && 
		h->content[p].status!=FREE && strcmp(key, h->content[p].entry)!=0; count--) {
		p = (p+d*d*d) % h->hsize; d++;
	}

	if (count == 0) p = -1;

	return p;
}

void update (HEAD_TABLE h, char *key, int filial, int new_quant, int nClientes) {

	int p = find_quad_probe (h, key);

	if (p < 0) return;
	else if (h->content[p].entry!=NULL && !strcmp(h->content[p].entry, key)) {
		h->content[p].total_quant[filial-1] += new_quant;
		h->content[p].total_client[filial-1] += nClientes;
		h -> content[p].final += new_quant;		
		h->content[p].status = USED;
	} else {
		h -> content[p].entry = strdup(key);
		h -> content[p].total_quant[filial-1] = new_quant;
		h -> content[p].total_client[filial-1] = 1;
		h -> content[p].final = new_quant;
		h -> content[p].status = USED;
	}
}

int lookup (HEAD_TABLE h, char* key, int hsize) {

	int found, p = find_quad_probe (h, key);

	if (p >= 0 && !strcmp(h->content[p].entry, key) &&
		h->content[p].status == USED) found = 1;
	else found = 0;

	return found;
}

void free_hashtable (HEAD_TABLE h) {

	int i = 0;
	while (i < h->hsize) {
		free(h->content[i].entry);
		i++;
	}

	free(h);
}

void printArrayTable (int *array) {
	int i;

	for (i = 0; i < 3; i++) {
		printf("|");
		printf("%d\t", array[i]);
	}

}

void printNfirstTableReverse (HEAD_TABLE h, int n) {

	int i, count = 0;

	printf("=> PRODUTOS\t  #Clientes [p/ filial]\t\t#Quantidade [p/ filial]\n");
	for (i = h->hsize; count < n && i > 0; i--) {
		if (count < 9) printf(" ");
		if (h->content[i].status!=FREE) {
			count++;
			printf("[#%d]  <%s>  ", count, h->content[i].entry);
			printArrayTable(h->content[i].total_client);
			printf("\t");
			printArrayTable(h->content[i].total_quant);
			printf("\n");
		}
	}
}

void printTable (HEAD_TABLE h) {

	int i;
	for (i = 0; i < h -> hsize; i++)
		if (h->content[i].status!=FREE) {
			printf("prod=%s ", h->content[i].entry);
			printf("\tQT_CLIENT: ");
			printArrayTable(h->content[i].total_client);
			printf(" \tQT_COMPR: ");
			printArrayTable(h->content[i].total_quant);
			printf("\n");
		}
}

void quicksort(HEAD_TABLE h, int first, int last){

   int i, j, pivot;
   HashTable temp = malloc(sizeof(struct celula));

   if (first < last) {

      pivot=first;
      i=first;
      j=last;

      while(i < j){
    
         while (h->content[i].final <= h->content[pivot].final && i < last)
            i++;
         while (h->content[j].final > h->content[pivot].final)
            j--;

         if(i<j){
            *temp=h->content[i];
            h->content[i]=h->content[j];
            h->content[j]=*temp;
         }
      }

      *temp = h->content[pivot];
      h->content[pivot] = h->content[j];
      h->content[j] = *temp;
      quicksort(h,first,j-1);
      quicksort(h,j+1,last);
   }
}

/*----------------------------------------------------------------------*/
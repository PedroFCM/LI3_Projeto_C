#define _GNU_SOURCE

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "hashtables.h"
 
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
		p = (p+d*d*d*d) % h->hsize; d++;
	}

	if (count == 0) p = -1;

	return p;
}

void update (HEAD_TABLE h, char *key, int filial, int new_quant) {

	int p = find_quad_probe (h, key);

	/*char *aux = strndup(key, strlen(key) - 2);*/

	if (p < 0) return;
	else if (h->content[p].entry!=NULL && !strcmp(h->content[p].entry, key)) {
		h->content[p].total_quant[filial] = new_quant;
		h->content[p].total_client[filial]++;
		h->content[p].status = USED;
	} else {
		h -> content[p].entry = strdup(key);
		h -> content[p].total_quant[filial] = new_quant;
		h -> content[p].total_client[filial]++;		
		h -> content[p].status = USED;
	}
}

int lookup (HEAD_TABLE h, char* key, int hsize, int key_hash) {

	int found, p = find_quad_probe (h, key);

	if (p >= 0 && !strcmp(h->content[p].entry, key) &&
		h->content[p].status == USED) found = 1;
	else found = 0;

	return found;
}

/*int deleteKey (HashTable t, char *key, int hsize, int key_hash) {

	int r = 0, p = find_quad_probe (t, key, hsize, key_hash);

	if (p > 0 && !strcmp(t[p].element, key) &&
		t[p].status == USED) {
		t[p].status = DELETED;
	} else r = 1;

	return r;
}
*/

void free_hashtable (HEAD_TABLE h) {

	int i = 0;
	while (i < h->hsize) {
		free(h->content[i].entry);
		i++;
	}
}

void printArrayTable (int *array) {
	int i;
	for (i = 0; i < 3; i++)
		printf("%d|", array[i]);
	printf(" ");
}

void printNfirstTableReverse (HEAD_TABLE h, int n) {

	int i, count = 0;
	for (i = h->hsize; count < n && i > 0; i--)
		if (h->content[i].status!=FREE) {
			count++;
			printf("prod=%s ", h->content[i].entry);
			printf("\tQT_CLIENT: ");
			printArrayTable(h->content[i].total_client);
			printf(" \tQT_COMPR: ");
			printArrayTable(h->content[i].total_quant);
			printf("\n");
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

void quicksort(HEAD_TABLE h, int first, int last, int filial){

   int i, j, pivot;
   HashTable temp = malloc(sizeof(struct celula));

   if (first < last) {

      pivot=first;
      i=first;
      j=last;

      while(i < j){
    
         while(h->content[i].total_quant[filial]<=h->content[pivot].total_quant[filial] && i<last)
            i++;
         while(h->content[j].total_quant[filial]>h->content[pivot].total_quant[filial])
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
      quicksort(h,first,j-1, filial);
      quicksort(h,j+1,last, filial);
   }
}
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "hashtables.h"
 
HashTable initTable (HashTable t, int hsize) {
	
	int i;

	t = (HashTable) malloc(sizeof(struct celula) * HSIZE_PRODS);

	for (i = 0; i < hsize; i++) {
		t[i].status = FREE;
		t[i].element = strdup(" ");
	}

	return t;
}

int hash_string (char *key, int hsize, int key_hash) {
	
	int k, res = 0;
	char *new = (char*) malloc(sizeof(char)*10);
			

	switch(key_hash) {
		
		//PRODUTOS
		case 0: 
			k = key[0] + key[1];
			sprintf(new, "%d%s", k, key+2);
 			res = atoi(new) - 666000;
 			break;
 		
 		//CLIENTES
 		case 1: 
			k = key[0];
			sprintf(new, "%d%s", k, key+1);
 			res = atoi(new) - 66000;
 			break;
		default: break;	
	}
	
	free(new);
	
	return (res % hsize);
}



int find_probe (HashTable t, char* key, int hsize, int key_hash) {
	
	int p = hash_string(key, hsize, key_hash), tmp;
	int count;

	for (count = hsize; count > 0 && t[p].status==USED && 
		strcmp(t[p].element, key)!=0; count--) {
		p = (p+1) % hsize;
	}

	if (strcmp(t[p].element, key)!=0)
		if (count == 0) p = -1;
		else {
			tmp = p;
			while (count > 0 && t[p].status!=FREE &&
					strcmp(t[p].element, key)!=0) {
				count--;
				p = (p+1) % hsize;
			}
			if (strcmp(t[p].element, key)!=0) p = tmp;
		}


	return p;
}

int find_quad_probe (HashTable t, char* key, int hsize, int key_hash) {
	
	int p = hash_string (key, hsize, key_hash), tmp;
	int count, d=2;

	char* aux = strndup(key, strlen(t[p].element));

	for (count = hsize; count > 0 && t[p].status!=DELETED && 
		t[p].status!=FREE && strcmp(key, t[p].element)!=0; count--) {
		p = (p+d*d*d*d) % hsize; d++;
	}

	if (count == 0) p = -1;

	return p;
}

HashTable update (HashTable t, char *key, int hsize, int key_hash) {

	int p = find_quad_probe (t, key, hsize, key_hash);
	int r;

	char *aux = strndup(key, strlen(key) - 2);

	if (p < 0) r = 0;
	else if (!strcmp(t[p].element, key)){
		t[p].status = USED; r = 1;
	} else {
		t[p].status = USED;
		t[p].element = strdup(aux);
		r = 2;
	}

	free(aux);

	return t;
}

int lookup (HashTable t, char* key, int hsize, int key_hash) {

	int found, p = find_quad_probe (t, key, hsize, key_hash);

	if (p >= 0 && !strcmp(t[p].element, key) &&
		t[p].status == USED) found = 1;
	else found = 0;

	return found;
}

int deleteKey (HashTable t, char *key, int hsize, int key_hash) {

	int r = 0, p = find_quad_probe (t, key, hsize, key_hash);

	if (p > 0 && !strcmp(t[p].element, key) &&
		t[p].status == USED) {
		t[p].status = DELETED;
	} else r = 1;

	return r;
}

void free_hashtable (HashTable t, int hsize) {

	int i;
	while (i < hsize) {
		free(t[i].element);
		i++;
	}
}
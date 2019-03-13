#ifndef _HASHTABLES_
#define _HASHTABLES_

#define HSIZE_PRODS 200000
#define HSIZE_CLIEN 20000

#define FREE 0
#define USED 1
#define DELETED 2

typedef struct celula {

	int status;
	char *element;

} *HashTable;


int hash_string (char *key, int hsize, int key_hash);

int find_probe (HashTable t, char* key, int hsize, int key_hash);

int find_quad_probe (HashTable t, char* key, int hsize, int key_hash);

HashTable update (HashTable t, char *key, int hsize, int key_hash);

int lookup (HashTable t, char* key, int hsize, int key_hash);

int deleteKey (HashTable t, char *key, int hsize, int key_hash);

HashTable initTable (HashTable t, int hsize);

void free_hashtable (HashTable t, int hsize);

#endif
#ifndef _HASHTABLES_
#define _HASHTABLES_

#define HSIZE_PRODS 200000
#define HSIZE_CLIEN 20000

#define FREE 0
#define USED 1
#define DELETED 2

typedef struct celula {

	char *entry;
	int total_quant[3];
	int total_client[3];
	int final;
	int status;

} *HashTable;

typedef struct head_table {
	
	int hsize;
	HashTable content;

} *HEAD_TABLE;



HEAD_TABLE initTable (HEAD_TABLE h, int hsize_in);

int hash_string (char *key, int hsize);

int find_quad_probe (HEAD_TABLE h, char* key);

void update (HEAD_TABLE h, char *key, int filial, int new_quant);

int lookup (HEAD_TABLE h, char* key, int hsize, int key_hash);

void free_hashtable (HEAD_TABLE h);

void printArrayTable (int *array);

void printTable (HEAD_TABLE h);

void quicksort(HEAD_TABLE h, int first, int last);

void printNfirstTableReverse (HEAD_TABLE h, int n);

#endif
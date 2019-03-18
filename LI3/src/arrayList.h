#ifndef _ARRAY_LIST_
#define _ARRAY_LIST_

typedef struct elementos {

	char *entry;
	int total_quant[3];
	int total_client[3];

} **ARRAY_LIST;

typedef struct head {
	
	int sp;
	int size;

	ARRAY_LIST content;

} *HEAD_LIST;

void initArrayList (HEAD_LIST h, int initial_size);

int isEmptyArrayList (HEAD_LIST h);

void pushArrayList (HEAD_LIST h, char *new_entry, int filial, int new_quant);

void doubleArrayList (HEAD_LIST h);

void freeArrayList (HEAD_LIST h);

void printArray (int *array);

void printArrayList (HEAD_LIST h);

#endif
#ifndef _AVL_
#define _AVL_

#define BAL   0
#define LEFT -1
#define RIGHT 1

typedef struct avl {
	int bal;
	char *tag;

	char *codProd;
	char *codClient;
	double precoUnit;
	int quantidade;
	char *tipo;
	int mes;
	int filial;

	struct avl *left, *right; 
} AVL;

AVL* rotateRight (AVL *a);

AVL* rotateLeft (AVL *b);

AVL* fixRight (AVL *a);

AVL* fixLeft (AVL *a);

AVL* updateAVLRec (AVL *a, char *tag_arg, int *g, int *u);

AVL* updateAVL (AVL *a, char *tag_arg);

#endif
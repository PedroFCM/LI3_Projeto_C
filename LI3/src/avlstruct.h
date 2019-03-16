#ifndef _AVL_
#define _AVL_

#define BAL   0
#define LEFT -1
#define RIGHT 1

typedef struct avl {
	int bal;
	char *tag;
	struct avl *left, *right; 
} *AVL;

void freeAVL (AVL a);

AVL rotateRight (AVL a);

AVL rotateLeft (AVL b);

AVL fixRight (AVL a);

AVL fixLeft (AVL a);

AVL initAVL (AVL a, char *arg, int *g);

AVL updateAVLRec (AVL a, char *arg, int *g);

AVL updateAVL (AVL a, char *arg);

#endif
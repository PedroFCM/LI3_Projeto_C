#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "avlstruct.h"

AVL* rotateRight (AVL *a) {
	AVL *b = a -> left;
	a -> left = b -> right;
	b -> right = a;
	
	return b;
}

AVL* rotateLeft (AVL *b) {
	AVL *a = b -> right;
	b -> right = a -> left;
	a -> left = b;

	return a;
}

AVL* fixRight (AVL *a){

	AVL *b, *c;
	b = a -> right;
	
	if(b -> bal == RIGHT) {
		
		a -> bal = b -> bal = BAL;
		
		a = rotateLeft(a);
	} else {
	
		c = b -> left;
	
		switch (c -> bal) {
			case LEFT: a -> bal = BAL;
					   b -> bal = RIGHT;
					   break;
			case RIGHT: a -> bal = LEFT;
					    b -> bal = BAL;
					    break;
			case BAL:   a -> bal = b -> bal = BAL;
						break;
		}
		c -> bal = BAL;
		a -> right = rotateRight(b);
		a = rotateLeft(a);
	}

	return a;
}

AVL* fixLeft (AVL *a){

	AVL *b, *c;
	b = a -> left;

	if(b -> bal == LEFT) {
		a -> bal = b -> bal = BAL;
		a = rotateRight(a);
	}
	else {
		c = b -> right;
		switch (c -> bal) {
			case LEFT: a -> bal = RIGHT;
					   b -> bal = BAL;
					   break;
			case RIGHT: a -> bal = BAL;
					    b -> bal = LEFT;
					    break;
			case BAL:   a -> bal = b -> bal = BAL;
						break;
		}
		c -> bal = BAL;
		a -> left = rotateLeft(b);
		a = rotateRight(a);
	}
	
	return a;
}


AVL* updateAVLRec (AVL *a, char *tag_arg, int *g, int *u) {
	
	if (a == NULL) {
	
		a = (AVL*) malloc(sizeof(struct avl));
		a -> tag = strdup(tag_arg);
		a -> left = a -> right = NULL;
		a -> bal = BAL;
		*g = 1; *u = 0;
	
	} else if (strcmp(a -> tag, tag_arg)==0) {
	
		*g = 0; *u = 1;  
	
	} else if (strcmp(a -> tag, tag_arg) > 0) {
	
		a->left = updateAVLRec (a -> left, tag_arg, g, u);
	
		if (*g == 1)
			switch (a->bal) {
				case LEFT: a = fixLeft(a); 
					 *g = 0; 
					 break;
	
				case BAL: 
					 a -> bal = LEFT; 
					 break;
	
				case RIGHT: a -> bal = BAL; 
					 *g = 0; 
					 break;
			}
	} else {
		
		a->right = updateAVLRec (a->right, tag_arg, g, u);
		
		if (*g == 1)
	
			switch (a->bal) {
				case RIGHT: a = fixRight(a); 
					 *g = 0; 
					 break;
	
				case BAL:   
					 a -> bal = RIGHT; 
					 break;
	
				case LEFT:  
					 a -> bal = BAL; 
					 *g = 0; 
					 break;
			}
	}

	return a;
}

AVL* updateAVL (AVL *a, char *tag_arg) {
	
	int g, u;
	
	a = updateAVLRec(a, tag_arg, &g, &u);
	
	return a;
}
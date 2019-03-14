#define _GNU_SOURCE

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "avlstruct.h"
#include "global.h"

void freeAVL (AVL a) {

	if (a != NULL) {
		freeAVL (a -> left);
		freeAVL (a -> right);
		free (a -> tag);
		free(a);
	}

}

AVL rotateRight (AVL a) {
	AVL b = a -> left;
	a -> left = b -> right;
	b -> right = a;
	
	return b;
}

AVL rotateLeft (AVL b) {
	AVL a = b -> right;
	b -> right = a -> left;
	a -> left = b;

	return a;
}

AVL fixRight (AVL a){

	AVL b, c;
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

AVL fixLeft (AVL a){

	AVL b, c;
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


AVL updateAVLRec (AVL a, char *arg, int *g) {
	
	if (a == NULL) {
	
		a = (AVL) malloc(sizeof(struct avl));
		
		arg  = string_cut_extra_char (arg);
		a -> tag = strdup(arg);
		
		a -> left = a -> right = NULL;
		a -> bal  = BAL;
		*g = 1;
	
	} else {
		
		int r = strcmp(a -> tag, arg);
		
		if (r >= 0) {
	
			a->left = updateAVLRec (a -> left, arg, g);
		
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
			
			} 

		else {
		
		a->right = updateAVLRec (a->right, arg, g);
		
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
	} 

	return a;
}

AVL updateAVL (AVL a, char *arg) {
	
	int g;
	
	a = updateAVLRec(a, arg, &g);
	
	return a;
}
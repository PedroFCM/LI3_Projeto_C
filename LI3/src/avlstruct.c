
/** @file avlstruct.c
*	@brief Ficheiro que implementa uma AVL.
*
*	@autor João Pedro Rodrigues Azevedo (A85227) 
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@bug Nenhum que tivessemos reparado.
*	
*/

/*MACRO para suprimir warnings de strdup do <string.h>*/
#define _GNU_SOURCE

/*_________________BIBLIOTECAS STD IMPORTADAS________________________*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*_________________BIBLIOTECAS IMPLEMENTADAS____________________________*/

#include "avlstruct.h"
#include "global.h"

/*______________________________________________________________________*/

AVL getEsq (AVL a) {
	return (a->left);
}

AVL getDir (AVL a) {
	return (a->right);
}

char* getCodProd (AVL a) {
	return (a->registo->codProd);
}

int getFilial (AVL a) {
	return (a->registo->filial);
}

int getQuantidade (AVL a) {
	return (a->registo->quantidade);
}

void freeAVL (AVL a, int flag) {

	if (a != NULL) {
		freeAVL (a -> left, flag);
		freeAVL (a -> right, flag);
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

AVL initAVL (AVL a, REGISTO novo, char *arg, int *g) {

	a = (AVL) malloc(sizeof(struct avl));
	
	arg  = string_cut_extra_char (arg);
	a -> tag = strdup(arg);
	
	if (novo != NULL) {
		a -> registo = (REGISTO) malloc(sizeof(struct registo));
		a -> registo = novo;	
	}	
	
	a -> left = a -> right = NULL;
	a -> bal  = BAL;
	*g = 1;

	return a;
}

AVL updateAVLRec (AVL a, REGISTO novo, char *arg, int *g) {
	
	if (a == NULL) a = initAVL(a, novo, arg, g);
	else {
		
		int r = strcmp(a -> tag, arg);
		
		if (r >= 0) {
	
			a->left = updateAVLRec (a -> left, novo, arg, g);
		
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
		
		a->right = updateAVLRec (a->right, novo, arg, g);
		
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

AVL updateAVL (AVL a, REGISTO novo, char *arg) {
	
	int g;
	
	a = updateAVLRec(a, novo, arg, &g);
	
	return a;
}
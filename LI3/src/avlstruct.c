
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

/*_________________BIBLIOTECAS STD IMPORTADAS___________________________*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*_________________BIBLIOTECAS IMPLEMENTADAS____________________________*/

#include "avlstruct.h"
#include "global.h"

/*______________________________________________________________________*/


/*ESTRUTURA QUE ARMAZENA O REGISTO DE UMA VENDA*/
struct registo {

	char* codProd;
	double preco;
	int quantidade;
	char tipo;
	char* codCli;
	int mes;
	int filial;

};

/*ESTRUTURA QUE DEFINE UMA AVL*/
struct avl {

	int bal;
	
	char* tag;
		
	REGISTO registo;

	struct avl *left, *right;

};

/*______________________________________________________________________*/

REGISTO initRegisto (REGISTO novo) {
	novo = (REGISTO) malloc(sizeof(struct registo));
	return novo;
}

void setFilial (REGISTO reg, int f) {
	reg -> filial = f;
}

void setMes (REGISTO reg, int m) {
	reg -> mes = m;
}

void setCodCliente (REGISTO reg, char* cliente) {
	reg -> codCli = strdup(cliente);
}

void setTipo (REGISTO reg, char tp) {
	reg -> tipo = tp;
}

void setQuantidade (REGISTO reg, int qt) {
	reg -> quantidade = qt;
}

void setPreco (REGISTO reg, double price) {
	reg->preco = price;
}

void setCodProd (REGISTO reg, char *prod) {
	reg->codProd = strdup(prod);
}

char getFirstLetterTag (AVL a) {
	return (a->tag[0]);
}

char getTipo (AVL a) {
	return (a->registo->tipo);
}

char* getCodCliente (AVL a) {
	return (a->registo->codCli);
}

int getMes (AVL a) {
	return (a->registo->mes);
}

double getPreco (AVL a) {
	return (a->registo->preco);
}

REGISTO getRegisto (AVL a) {
	return (a->registo);
}

char* getTag (AVL a) {
	return (a->tag);
}

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

AVL initAVL (AVL a, REGISTO novo, char *arg, int *g, int flag) {

	a = (AVL) malloc(sizeof(struct avl));
	
	if (flag==0) arg = string_cut_extra_char (arg);
	
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

AVL updateAVLRec (AVL a, REGISTO novo, char *arg, int *g, int flag) {
	
	if (a == NULL) a = initAVL(a, novo, arg, g, flag);
	else {
		
		int r = strcmp(a -> tag, arg);
		
		if (r >= 0) {
	
			a->left = updateAVLRec (a -> left, novo, arg, g, flag);
		
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
		
		a->right = updateAVLRec (a->right, novo, arg, g, flag);
		
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

AVL updateAVL (AVL a, REGISTO novo, char *arg, int flag) {
	
	int g;
	
	a = updateAVLRec(a, novo, arg, &g, flag);
	
	return a;
}
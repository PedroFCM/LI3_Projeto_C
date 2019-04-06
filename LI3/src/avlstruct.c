
/** @file avlstruct.c 
*	@brief Ficheiro que implementa uma AVL.
*          Usa assim os campos necessários ao trabalho,
*          guarda faturção, registo de venda e info da Filial.
*
*	@autor João Pedro Rodrigues Azevedo
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@bug Nenhum que tivessemos reparado.
*	
*/

/**MACRO para suprimir warnings de strdup do <string.h>*/
#define _GNU_SOURCE

/*----------------------------------------------------------------------*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*----------------------------------------------------------------------*/

#include "avlstruct.h"
#include "global.h"
#include "Faturacao.h"
#include "Filial.h"
#include "catVendas.h"

/*----------------------------------------------------------------------*/

/**
* Struct que representa uma AVL.
*/
struct avl {

	/*@{*/
	int bal; /**< Indicador de balancemaneto de uma AVL. */	
	char* tag; /**< key da AVL para efetuar a ordenação (**na maior parte dos casos). */
		
	REGISTO registo; /**< Struct registo do ficheiro catVendas.c. */
	FATURA fatura; /**< Struct faturacao do ficheiro Faturacao.c. */
	GESTAO_FILIAL gestaoFilial; /**< Struct Gestao de Filial do ficheiro Filial.c. */

	struct avl *left, *right; /**< Apontadores para a esquerda e direita da AVL. */
	/*@}*/
};

/*----------------------------------------------------------------------*/

/** @brief Função que faz uma rotação à direita de uma AVL.
 *
 *  @param a AVL.
 *  @param flag pode ser 0 ou 1, no caso de ser 1 indica que queremos fazer free às vendas
 *  @return AVL após rotação.
 */

static AVL rotateRight (AVL a);


/** @brief Função que faz uma rotação à esquerda de uma AVL.
 *
 *  @param a AVL.
 *  @return AVL após rotação.
 */

static AVL rotateLeft (AVL b);


/** @brief Função que resolver diferenças de altura à direita.
 *
 *  @param a AVL.
 *  @return AVL após o fix.
 */

static AVL fixRight (AVL a);


/** @brief Função que resolver diferenças de altura à esquerda.
 *
 *  @param a AVL.
 *  @return AVL após o fix.
 */

static AVL fixLeft (AVL a);


/** @brief Função que cria memória para uma AVL.
 *
 *  @param a AVL.
 *  @return AVL após o fix.
 */

static AVL initAVL (AVL a, REGISTO novo, FATURA f, GESTAO_FILIAL nova_gestao, char *arg, int *g, int flag);


/** @brief Função auxiliar que insere um elemento a uma AVL.
 *
 *  @param a AVL.
 *  @param novo novo registos.
 *  @param arg string de venda.
 *  @param g flag que indica se cresceu ou não a AVL após inserção
 *  @return AVL após inserção.
 */

static AVL updateAVLRec (AVL a, REGISTO novo, FATURA f,  GESTAO_FILIAL nova_gestao, char *arg, int *g, int flag);


/*----------------------------------------------------------------------*/

GESTAO_FILIAL getGestaoFilial(AVL filial){
	return filial -> gestaoFilial;
}

FATURA getFatura (AVL a) {
	return a->fatura;
}

REGISTO getRegisto (AVL a) {
	return (a->registo);
}

char getFirstLetterTag (AVL a) {
	return (a->tag[0]);
}

void freeAVLfaturacao (AVL a) {
	if (a != NULL) {
		freeAVLfaturacao (a -> left);
		freeAVLfaturacao (a -> right);
		freeFatura (a->fatura);
		free(a);
	}
}

void freeAVLregisto(AVL a) {
	if (a != NULL) {
		freeAVLregisto (a -> left);
		freeAVLregisto (a -> right);
		freeRegisto (a->registo);
	}

}

void freeAVLfil (AVL a) {
	if (a != NULL) {
		freeAVLfil (a -> left);
		freeAVLfil (a -> right);
		freeGestaoFilial (a->gestaoFilial);
	}
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

void freeAVL_andTag (AVL a) {

	if (a != NULL) {
		freeAVL_andTag (a -> left);
		freeAVL_andTag (a -> right);
		free (a -> tag);
		free(a);
	}

}

static AVL rotateRight (AVL a) {
	AVL b = a -> left;
	a -> left = b -> right;
	b -> right = a;
	
	return b;
}

static AVL rotateLeft (AVL b) {
	AVL a = b -> right;
	b -> right = a -> left;
	a -> left = b;

	return a;
}

static AVL fixRight (AVL a){

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

static AVL fixLeft (AVL a){

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

static AVL initAVL (AVL a, REGISTO novo, FATURA f, GESTAO_FILIAL nova_gestao, char *arg, int *g, int flag) {

	a = (AVL) malloc(sizeof(struct avl));
	
	if (flag==0) {
		arg = string_cut_extra_char (arg);
		a -> tag = strdup(arg);
	} else if (flag == 2) {
		a->fatura = f;
	} else if (flag == 3) {
		a->gestaoFilial = nova_gestao;
	}
	else a -> tag = strdup(arg);

	if (novo != NULL) {
		a -> registo = novo;	
	}	
	
	a -> left = a -> right = NULL;
	a -> bal  = BAL;
	*g = 1;

	return a;
}

static AVL updateAVLRec (AVL a, REGISTO novo, FATURA f,  GESTAO_FILIAL nova_gestao, char *arg, int *g, int flag) {
	
	if (a == NULL) a = initAVL(a, novo, f, nova_gestao, arg, g, flag);
	else {
		
		int r;

		if (flag == 2) r = strcmp(getProdFatura(a->fatura), arg);
		else if (flag == 3) r = strcmp(getClienteFilial(a->gestaoFilial), arg);
		else if(flag == 4) r = getQuantidade(a) - getQuantidadeReg(novo);
		else r = strcmp(a -> tag, arg);
		
		if (r >= 0) {
	
			a->left = updateAVLRec (a -> left, novo, f, nova_gestao, arg, g, flag);
		
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
		
		a->right = updateAVLRec (a->right, novo, f, nova_gestao, arg, g, flag);
		
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

AVL updateAVL (AVL a, REGISTO novo, FATURA f, GESTAO_FILIAL nova_gestao, char *arg, int flag) {
	
	int g;
	
	a = updateAVLRec(a, novo, f, nova_gestao, arg, &g, flag);
	
	return a;
}

/*----------------------------------------------------------------------*/
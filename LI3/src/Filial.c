
/** @file Filial.c
*	@brief Ficheiro que gere as operações numa filial.
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*_________________BIBLIOTECAS IMPLEMENTADAS____________________________*/

#include "Filial.h"
#include "catVendas.h"

/*______________________________________________________________________*/

struct filial {
	AVL filial;
};

struct gestaoFilial {
	char* codCliente;
	ELEM list;
};

struct elementos {
	
	char* produto;
	VENDAS numVendas;
	FAT_MES fatMes;
    struct elementos * next;
};

/*_______________________Funções PRINCIPAIS_________________________________*/

int existeNaLista (char* elem, ELEM l) {

	int r = 0;

	ELEM *pt = &l;

    while ((*pt) != NULL && r != 1) {

    	if (!strcmp(elem, (*pt) -> produto)) r = 1;
	    
	    pt = &((*pt) -> next);
    }

    return r;
}

ELEM pushLista (ELEM l, char* elem, char modo, int quant, float preco, int mes) {

	ELEM new = malloc (sizeof(struct elementos));
	ELEM *pt = &l;

    if(existeNaLista(elem, *pt)){
    	
	    while (strcmp(elem, (*pt) -> produto) != 0)
	    	pt = &((*pt) -> next);
   
	    switch (modo) {

			case 'N':
					setFatFilial(*pt, 0, mes-1, preco*quant);
					setVendasFilial(*pt, 0, mes-1);
					return l;

			case 'P':			
					setFatFilial(*pt, 1, mes-1, preco*quant);
					setVendasFilial(*pt, 1, mes-1);
					return l;

			default: break;
		}
	    

	} else {
	  
	    while (*pt != NULL) pt = &((*pt) -> next);
	    
	    int** v = (VENDAS)malloc(sizeof(int*)*2);
		float** f = (FAT_MES) malloc(sizeof(float*)*2);

		initFaturaFilial(f,v);			
		initMatrizFilial(new,f, v);

		switch (modo) {

		case 'N':
				setFatFilial(new, 0, mes-1, preco*quant);
				setVendasFilial(new, 0, mes-1);
				return l;

		case 'P':
				setFatFilial(new, 1, mes-1, preco*quant);
				setVendasFilial(new, 1, mes-1);
				return l;

		default: break;
		}

	    new -> produto = strdup(elem);

	    new -> next = *pt;
	    *pt = new;
	} 

	return l;
}

void updateGestaoFilial (AVL filial, AVL vendas, char *c, int *r) {
	
	if (filial != NULL) {

		int cmp = strcmp(c, getClienteFilial(*getGestaoFilial(filial)));

		if (!cmp) {

			*r = 1;

			setList(filial,pushLista(getList(*getGestaoFilial(filial)), getCodProd(vendas), getTipo(vendas), getQuantidade(vendas), getPreco(vendas), getMes(vendas)));

		} else if (cmp > 0)

			updateGestaoFilial (getDir(filial), vendas, c, r);
		
		else 
			updateGestaoFilial (getEsq(filial), vendas, c, r);
	}	
}

AVL* insereClienteFat (int fi, AVL *filial, AVL vendas) {

	int *r = malloc(sizeof(int));
 
	if (vendas != NULL) {

		if (fi == getFilial(vendas)) {

			*r = 0;

			updateGestaoFilial(*filial, vendas, getCodCliente(vendas), r);

			if (*r == 0) {

				GESTAO_FILIAL *new = (GESTAO_FILIAL*) malloc(sizeof(GESTAO_FILIAL));

				(*new) -> list = NULL;

				(*new) = setClienteFilial(getCodCliente(vendas), new);

				setList(*filial,pushLista((*new) -> list, getCodProd(vendas), getTipo(vendas), getQuantidade(vendas), getPreco(vendas), getMes(vendas)));
		
				updateGestaoFilial(*filial, vendas, getCodCliente(vendas), r);
				
				*filial = updateAVL(*filial, NULL, *new, getCodCliente(vendas), NULL, 3);

			}
		}
		
		filial = insereClienteFat (fi, filial, getEsq(vendas));
		filial = insereClienteFat (fi, filial, getDir(vendas));

	}

	return filial;
}

FILIAL initFilial (FILIAL nova, AVL clientes, AVL vendas) {

	int f1 = 1, f2 = 2, f3 = 3;

	nova = (FILIAL) malloc(sizeof(struct filial) * NUM_FILIAIS);
	
	AVL *filial1 = malloc(sizeof(AVL));
	AVL *filial2 = malloc(sizeof(AVL));
	AVL *filial3 = malloc(sizeof(AVL));
	
	*filial1 = NULL;
	*filial2 = NULL;
	*filial3 = NULL;

	insereClienteFat(f1, filial1, vendas);
	insereClienteFat(f2, filial2, vendas);
	insereClienteFat(f3, filial3, vendas);

 	nova[f1-1].filial = *filial1;	
 	nova[f2-1].filial = *filial2;	
 	nova[f3-1].filial = *filial3;	

	return nova;
}

/*_______________________Funções AUXILIARES_______________________________*/
void initFaturaFilial (FAT_MES f, VENDAS v) {

	int l, c;

	for (l = 0; l < 2; l++) {
		f[l] = malloc(sizeof(float) * NUM_MESES);
		v[l] = malloc(sizeof(int) * NUM_MESES);
		
		for (c = 0; c < NUM_MESES; c++) {
			f[l][c] = 0.0;
			v[l][c] = 0;
		}
	}
}

void initMatrizFilial(ELEM elem, FAT_MES f, VENDAS v){

		elem -> numVendas = v;
		elem -> fatMes = f;
}


GESTAO_FILIAL setClienteFilial (char *c, GESTAO_FILIAL *g) {
	(*g)->codCliente = strdup(c);
	return (*g);
}

char* getProdFilial (GESTAO_FILIAL filial, int i) {
	return filial -> list[i].produto;
}

void setFatFilial (ELEM elem, int l, int c, double val) {
	
	elem -> fatMes[l][c] += val;
}

void setVendasFilial (ELEM elem, int l, int c) {

	elem -> numVendas[l][c] +=1;
}

char* getClienteFilial(GESTAO_FILIAL filial) {
	return filial -> codCliente;
}

ELEM getList(GESTAO_FILIAL g){

	return g -> list;
}

void setList(AVL filial, ELEM l){

	(*getGestaoFilial(filial)) -> list  = l;
}

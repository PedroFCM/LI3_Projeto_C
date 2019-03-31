
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
	ELEM *list;
	int size;
};

struct elementos {
	char* produto;
	VENDAS numVendas;
	FAT_MES fatMes;
};

/*_______________________Funções PRINCIPAIS_________________________________*/

void insereNaFilial (GESTAO_FILIAL filial, char *p, char modo, float preco, int quant, int mes) {

	int i;
	for (i = 0; i < getSizeGF(filial); i++) {

		if (!strcmp(p, getProdFilial(filial, i))) {
		
			switch (modo) {

				case 'N':
						setFatFilial(filial, i, 0, mes-1, preco*quant);
						setVendasFilial(filial, i, 0, mes-1);
						return;

				case 'P':			
						setFatFilial(filial, i, 1, mes-1, preco*quant);
						setVendasFilial(filial, i, 1, mes-1);
						return;

				default: break;
			}
		}
	}

	/*Caso chegue aqui o produto não existe 
	ou ainda não foi adicinado nenhum*/

	pushProdutoFilial(p, filial);

	switch (modo) {

		case 'N':
				setFatFilial(filial, getSizeGF(filial), 0, mes-1, preco*quant);
				setVendasFilial(filial, getSizeGF(filial), 0, mes-1);
				return;

		case 'P':
				setFatFilial(filial, getSizeGF(filial), 1, mes-1, preco*quant);
				setVendasFilial(filial, getSizeGF(filial), 1, mes-1);
				return;

		default: break;
	}

}

void updateGestaoFilial (AVL filial, AVL vendas, char *c, int *r) {
	
	if (filial != NULL) {

		int cmp = strcmp(c, getClienteFilial(getGestaoFilial(filial)));

		if (!cmp) {

			*r = 1;

			insereNaFilial(getGestaoFilial(filial), 
						   getCodProd(vendas), 
						   getTipo(vendas),
						   getPreco(vendas), 
						   getQuantidade(vendas), 
						   getMes(vendas));

		} else if (cmp > 0)

			updateGestaoFilial (getDir(filial), vendas, c, r);
		
		else 
			updateGestaoFilial (getEsq(filial), vendas, c, r);
	}	
}

void insereClienteFat (int fi, AVL *filial, AVL vendas) {

	int *r = malloc(sizeof(int));

	if (vendas != NULL) {

		if (fi == getFilial(vendas)) {

			*r = 0;

			updateGestaoFilial(*filial, vendas, getCodCliente(vendas), r);

			if (*r == 0) {

				GESTAO_FILIAL new = (GESTAO_FILIAL) malloc(sizeof(GESTAO_FILIAL));
				new -> list = malloc(sizeof(struct elementos) * 10);

				initFaturaFilial (new);				

				new = setClienteFilial(getCodCliente(vendas),&new);

				printf("%f\n", new -> list[0]->fatMes[1][1]);
	
				*filial = updateAVL(*filial, NULL, new, getCodCliente(vendas), NULL, 3);

				updateGestaoFilial(*filial, vendas, getCodCliente(vendas), r);
				
				getGestaoFilial(*filial) -> size++;
			}
		}
		
		insereClienteFat (fi, filial, getEsq(vendas));
		insereClienteFat (fi, filial, getDir(vendas));

	}
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

void initFaturaFilial (GESTAO_FILIAL new) {

	int l, c;

	new -> list[0] -> fatMes = (FAT_MES) malloc(sizeof(float*) * 2);
	new -> list[0] -> numVendas = (VENDAS)malloc(sizeof(int*) * 2);
	
	for (l = 0; l < 2; l++) {
		new -> list[0] -> fatMes[l]    = malloc(sizeof(float) * NUM_MESES);
		new -> list[0] -> numVendas[l] = malloc(sizeof(int) * NUM_MESES);
		
		for (c = 0; c < NUM_MESES; c++) {
			new -> list[0] -> fatMes[l][c] = 0.0;
			new -> list[0] -> numVendas[l][c] = 0;
		}
	}
}

void initMatrizFilial(GESTAO_FILIAL fat, FAT_MES f, VENDAS v, int prod){

		fat -> list[prod] -> numVendas = v;
		fat -> list[prod] -> fatMes = f;
}

GESTAO_FILIAL setClienteFilial (char *c, GESTAO_FILIAL *g) {
	(*g)->codCliente = strdup(c);
	return (*g);
}

void setSizeGF (GESTAO_FILIAL f, int new_size) {
	f -> size = new_size;
}

int getSizeGF(GESTAO_FILIAL filial) {
	return filial -> size;
}

char* getProdFilial (GESTAO_FILIAL filial, int i) {
	return filial -> list[i] -> produto;
}

void setFatFilial (GESTAO_FILIAL g, int prod, int l, int c, double val) {
	g->list[prod] -> fatMes[l][c] += val;
}

void setVendasFilial (GESTAO_FILIAL g, int prod, int l, int c) {
	g->list[prod] -> numVendas[l][c] +=1;
}
void pushProdutoFilial (char *p, GESTAO_FILIAL filial) {
	filial -> list[filial->size] -> produto = strdup(p);	
}

char* getClienteFilial(GESTAO_FILIAL filial) {
	return filial -> codCliente;
}

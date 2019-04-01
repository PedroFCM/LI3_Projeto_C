
/** @file Faturacao.c
*	@brief Ficheiro que implementa a faturacao.
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
#include <string.h>
#include <stdlib.h>

/*_________________BIBLIOTECAS IMPLEMENTADAS____________________________*/

#include "Faturacao.h"
#include "catVendas.h"

/*______________________________________________________________________*/

/*ESTRUTURA QUE ARMAZENA A FATURAÇÃO DE UM */

struct listagem {

	FAT_PRECO precario;
	FAT_QUANT quantidade;

};

struct faturacao {

	AVL faturacao;

};

struct fatura {

	char* codProd;
	FAT_MES fatMes;
	VENDAS numVendas;

};

/*_______________________Funções PRINCIPAIS_________________________________*/

void insereNaFatura (FATURA f, double preco, int quant, char modo, int mes) {

	switch (modo) {

		case 'N':
				setFatMes (f, 0, mes-1, preco*quant);
				setVendas (f, 0, mes-1);
				break;
		case 'P':				
				setFatMes(f, 1, mes-1, preco*quant);
				setVendas (f, 1, mes-1);
				break;

		default: break;
	}
}

void updateFatura (AVL fatFilial, AVL vendas, char *p, int *r) {
	
	if (fatFilial != NULL) {

		int cmp = strcmp(p, getProdFatura(getFatura(fatFilial)));
		
		if (!cmp) {

			*r = 1;

			insereNaFatura(getFatura(fatFilial), getPreco(vendas)
							  , getQuantidade(vendas)
							  , getTipo(vendas)
							  , getMes(vendas));

		} else if (cmp > 0)
			updateFatura(getDir(fatFilial), vendas, p, r);
		else 
			updateFatura(getEsq(fatFilial), vendas, p, r);
	}	
}

void insereProdFat (int filial, AVL *fatFilial, AVL vendas) {

	int *r = malloc(sizeof(int));

	if (vendas != NULL) {

		if (filial == getFilial(vendas)) {

			*r = 0;

			updateFatura(*fatFilial, vendas, getCodProd(vendas), r);

			if (*r == 0) {

				FATURA new = (FATURA) malloc(sizeof(FATURA));
				int** v = (VENDAS)malloc(sizeof(int*)*2);
				float** f = (FAT_MES) malloc(sizeof(float*)*2);

				initFatura(f, v);
				initMatriz(new,f,v);
				setProdFatura(getCodProd(vendas), new);

				*fatFilial = updateAVL(*fatFilial, NULL, new, getCodProd(vendas), 2);

				updateFatura(*fatFilial, vendas, getCodProd(vendas), r);
		
			}
		}
		
		insereProdFat (filial, fatFilial, getEsq(vendas));
		insereProdFat (filial, fatFilial, getDir(vendas));

	}
}

FAT_FILIAL initFaturacao (FAT_FILIAL nova, AVL prod, AVL vendas) {

	int f1 = 1, f2 = 2, f3 = 3;

	nova = (FAT_FILIAL) malloc(sizeof(struct faturacao) * 3);
	
	AVL *filial1 = malloc(sizeof(AVL));
	AVL *filial2 = malloc(sizeof(AVL));
	AVL *filial3 = malloc(sizeof(AVL));
	
	*filial1 = NULL;
	*filial2 = NULL;
	*filial3 = NULL;

	insereProdFat(f1, filial1, vendas);
	insereProdFat(f2, filial2, vendas);
	insereProdFat(f3, filial3, vendas);

 	nova[f1-1].faturacao = *filial1;	
 	nova[f2-1].faturacao = *filial2;	
 	nova[f3-1].faturacao = *filial3;	

 	printFaturacao(nova[f3-1].faturacao);

	return nova;
}

/*_______________________Funções AUXILIARES_______________________________*/

void printMATRIX (FAT_MES f, VENDAS v, int opcao) {

	int i, j;

	switch(opcao) {

		/*MATRIZ DE FLOATS*/
		case 0: 

			printf("FAT:\n");
			for (i = 0; i < 2; i++) {
				if (i==0) printf("N:");
				if (i==1) printf("P:");
				for (j = 0; j < 12; j++) {
					printf(" %.2f |", f[i][j]);
				}
				printf("\n");
			}

			break;

		/*MATRIZ DE INTS*/
		case 1:

			printf("VENDAS:\n");
			for (i = 0; i < 2; i++) {
				if (i==0) printf("N:");
				if (i==1) printf("P:");
				for (j = 0; j < 12; j++) {
					printf(" %d |", v[i][j]);
				}
				printf("\n");
			}	

			break;

		default: break;
	}
}

void printFaturacao (AVL fat) {

	if (fat != NULL) {

		printFaturacao(getEsq(fat));		

		printf("\nPRODUTO: %s.\n", (getFatura(fat))->codProd);
		printMATRIX((getFatura(fat))->fatMes,
					(getFatura(fat))->numVendas, 0);
		printMATRIX((getFatura(fat))->fatMes,
					(getFatura(fat))->numVendas, 1);

		printFaturacao(getDir(fat));

	}
}

void initFatura (FAT_MES f, VENDAS v) {

	int l, c;

	for (l = 0; l < 2; l++) {
		f[l] = malloc(sizeof(float) * 12);
		v[l] = malloc(sizeof(int) * 12);
		
		for (c = 0; c < 12; c++) {
			f[l][c] = 0.0;
			v[l][c] = 0;
		}
	}
}

void setFatMes (FATURA f, int l, int c, double val) {
	f->fatMes[l][c] += val;
}

void setVendas (FATURA f, int l, int c) {
	f->numVendas[l][c]++;
}

VENDAS getNumVendas (FATURA f) {
	return f->numVendas;
}

FAT_MES getFatMes (FATURA f) {
	return f->fatMes;
}

void initMatriz(FATURA fat, FAT_MES f,VENDAS v){

	fat -> numVendas = v;
	fat -> fatMes = f;
}

void setProdFatura (char* p, FATURA f) {
	f -> codProd = strdup(p);
}

char* getProdFatura (FATURA f) {
	return f->codProd;
}

/*_________________OUTRAS FUNÇÕES_______________________________________*/

int getQuantPos (FAT f, int l, int c) {
	return f->quantidade[l][c];
}

double getPrecoPos(FAT f, int l, int c) {
	return f->precario[l][c];
}

FAT initFatProduto (FAT new) {

	int l, c;

	new = malloc(sizeof(struct listagem));

	FAT_PRECO prec = (float**) malloc(sizeof(float*) * 2);
	FAT_QUANT n_vendas  = (int**)   malloc(sizeof(int*)   * 2);
		
	for (l = 0; l < 2; l++) {
		n_vendas[l]  = malloc(sizeof(int)*3);
		prec[l] = malloc(sizeof(float)*3);
		for (c = 0; c < 3; c++) {
			n_vendas[l][c]  = 0;
			prec[l][c] = 0.0;
		}
	}
	new -> precario = prec;
	new -> quantidade = n_vendas;

	return new;
}

void geraFaturacaoProduto (AVL vendas, char* prod, int mes, FAT f) {

	if (vendas != NULL) {
			
		if (!strcmp(getCodProd(vendas), prod) && mes == getMes(vendas)) {
			
			switch (getTipo(vendas)) {

				case 'P': 
					f -> quantidade[0][getFilial(vendas)-1]++;
					f -> precario[0][getFilial(vendas)-1]+=getQuantidade(vendas)*
														   getPreco(vendas);
				
				  break;

				case 'N': 
					f -> quantidade[1][getFilial(vendas)-1]++;
					f -> precario[1][getFilial(vendas)-1]+=getQuantidade(vendas)*
															getPreco(vendas);
				
				 	break;
				
				default: break;
			}
		}

		geraFaturacaoProduto(getEsq(vendas), prod, mes, f);
		geraFaturacaoProduto(getDir(vendas), prod, mes, f);
	}
}

void faturacaoMes (int min, int max, AVL vendas, FAT f){
	
	if(vendas != NULL) {
	
		int month = getMes(vendas);
		int sold;
		double price;
	
		if(month >= min && month <= max) {
			
			sold  = getQuantidade(vendas);
			price = getPreco(vendas);

			*(f -> precario[0]) += sold * price;
			*(f -> quantidade[0])+=1;
		}

		faturacaoMes(min, max, getEsq(vendas), f);
		faturacaoMes(min, max, getDir(vendas), f);

	}
}

void freeFat (FAT f) {
	free(f->quantidade);
	free(f->precario);
	free(f);
}

/*______________________________________________________________________*/

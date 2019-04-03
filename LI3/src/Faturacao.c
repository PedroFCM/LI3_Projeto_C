
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

/*-----------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*-----------------------------------------------------------------------*/

#include "Faturacao.h"
#include "catVendas.h"

/*-----------------------------------------------------------------------*/

/**
* Struct que representa um array de AVL' faturacao.
*/
struct faturacao {
	AVL faturacao;
};

/**
* Struct que representa a faturacao de um produto num AVL faturacao.
*/
struct fatura {
	/*@{*/
	char* codProd; /**< Código do produto vendido. */
	FAT_MES fatMes; /**< faturacao do produto por mes. */
	VENDAS numVendas; /**< numero de vendas do produto por mes. */
	/*@}*/
};

/*-----------------------------------------------------------------------*/

void vendasEntreMeses(AVL fat, int min, int max, float* faturacao, int* total_vendas)
{
	if(fat != NULL)
	{
		int i,j;

		for(i = 0; i < 2; i++)
			for(j = 0; j < 12; j++)
				if(j >= min && j <= max)
				{
					*faturacao +=  getFatMes(getFatura(fat))[i][j];
					*total_vendas +=  getNumVendas(getFatura(fat))[i][j];
				}
		
		vendasEntreMeses(getEsq(fat), min, max, faturacao, total_vendas);
		vendasEntreMeses(getDir(fat), min, max, faturacao, total_vendas);
	}
}

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

				*fatFilial = updateAVL(*fatFilial, NULL, new, NULL, getCodProd(vendas), 2);

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

	return nova;
}

void vendasNoMes (AVL faturacao, int filial, char* prod, int mes, FAT_MES f, VENDAS v) 
{
	if(faturacao != NULL) 
	{		
		int equal = strcmp(getProdFatura(getFatura(faturacao)), prod);
		int i;

		if(!equal) 
			for(i = 0; i < 2; i++)
			{	
				f[i][filial] += getFatMes(getFatura(faturacao))[i][mes];
				v[i][filial] += getNumVendas(getFatura(faturacao))[i][mes];
			}

		else
		{
			if(equal > 0)
				vendasNoMes(getEsq(faturacao), filial, prod, mes, f, v);
			else
				vendasNoMes(getDir(faturacao), filial, prod, mes, f, v);
		}
	}
}

int existFaturacao(AVL fat, char* produto)
{
	int r = 0;

	if(fat != NULL)
	{
		int equal = strcmp(getProdFatura(getFatura(fat)), produto);

		if(!equal)
			r++;

		else
		{	
			if(equal > 0)
				r += existFaturacao(getEsq(fat), produto);
			else
				r += existFaturacao(getDir(fat), produto);
		}
	}

	return r;
}

void prodNinguemComprou(FAT_FILIAL fat, AVL produtos, AVL* produtoFilial1, AVL* produtoFilial2, AVL* produtoFilial3, int opcao)
{
	if(produtos != NULL)
	{
		getTag(produtos)[6] = '\0';
		
		switch(opcao)
		{
		case 0: if( !existFaturacao(getFaturacao(fat, 0), getTag(produtos)) && !exist_element(*produtoFilial1, getTag(produtos)) )
					*produtoFilial1 = updateAVL(*produtoFilial1, NULL, NULL, NULL, getTag(produtos), 1);	

				else
				{	
					if( !existFaturacao(getFaturacao(fat, 1), getTag(produtos)) && !exist_element(*produtoFilial2, getTag(produtos)) )
						*produtoFilial2 = updateAVL(*produtoFilial2, NULL, NULL, NULL, getTag(produtos), 1);	
			
					else
						if( !existFaturacao(getFaturacao(fat, 2), getTag(produtos)) && !exist_element(*produtoFilial3, getTag(produtos)) )
							*produtoFilial3 = updateAVL(*produtoFilial3, NULL, NULL, NULL, getTag(produtos), 1);	
				}
				break;
		
		case 1: if(!existFaturacao(getFaturacao(fat, 0), getTag(produtos)) && !existFaturacao(getFaturacao(fat, 1), getTag(produtos)) 
					&& !existFaturacao(getFaturacao(fat, 2), getTag(produtos)))
					*produtoFilial1 = updateAVL(*produtoFilial1, NULL, NULL, NULL, getTag(produtos), 1);
				break;
		}

		prodNinguemComprou(fat, getEsq(produtos), produtoFilial1, produtoFilial2, produtoFilial3, opcao);
		prodNinguemComprou(fat, getDir(produtos), produtoFilial1, produtoFilial2, produtoFilial3, opcao);		
	}
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

AVL getFaturacao(FAT_FILIAL f, int i) {
	return f[i].faturacao;
}

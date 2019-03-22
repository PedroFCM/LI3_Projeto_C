
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

/*______________________________________________________________________*/

/*ESTRUTURA QUE ARMAZENA A FATURAÇÃO DE UM */

struct faturacao {

	FAT_PRECO precario;
	FAT_QUANT quantidade;

};

/*______________________________________________________________________*/

int getQuantPos (FAT f, int l, int c) {
	return f->quantidade[l][c];
}

double getPrecoPos(FAT f, int l, int c) {
	return f->precario[l][c];
}

FAT initFatProduto (FAT new) {

	int l, c;

	new = malloc(sizeof(struct faturacao));

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
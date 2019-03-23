
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
#include "avlstruct.h"
#include "hashtables.h"

/*______________________________________________________________________*/

void procuraNaFilial (AVL vendas, int filial[], char* cliente) {

	if( (filial[0]+filial[1]+filial[2] < 3) && vendas != NULL) {

		if( !strcmp(getCodCliente(vendas), cliente) )
			filial[getFilial(vendas) - 1] = 1;

		procuraNaFilial(getEsq(vendas), filial, cliente);
		procuraNaFilial(getDir(vendas), filial, cliente);

	}
}

void compraramEmTodas (AVL vendas, AVL* clie_filiais) {

	if(vendas != NULL) {

		int filial[3], i;

		for(i = 0; i < 3; i++)
			filial[i] = 0;

		procuraNaFilial(vendas, filial, getCodCliente(vendas));
		
		getCodCliente(vendas)[(strlen(getCodCliente(vendas)))] = ' ';  
		/* por causa do 'cut_extra_char' */

		if(filial[0]+filial[1]+filial[2] == 3)
			*clie_filiais = updateAVL(*clie_filiais, NULL, getCodCliente(vendas)); 

		compraramEmTodas(getEsq(vendas), clie_filiais);
		compraramEmTodas(getDir(vendas), clie_filiais);
	}
}

void compraramNaFilial (AVL vendas, char* prod, int filial, Stack clientesN, Stack clientesP) {
	
	char tipo;
	char* cliente;

	if (vendas != NULL) {
		
		tipo = getTipo(vendas);
		cliente = getCodCliente(vendas);

		if (!strcmp(prod, getCodProd(vendas)) && getFilial(vendas) == filial) 
		{
			if (tipo == 'N') clientesN = push(clientesN, cliente); 			

			if (tipo == 'P') clientesP = push(clientesP, cliente); 
			
		}
		compraramNaFilial(getDir(vendas), prod, filial, clientesP, clientesN);
		compraramNaFilial(getEsq(vendas), prod, filial, clientesP, clientesN); 
	}
}

void juntaQuantFilial (HEAD_TABLE h) {
	
	int val, i, size = getSize(h);
	
	for (i = 0; i < size; i++) {	
		if (getStatus(h, i)!=FREE) {
			
			val = getQuant(h, i, 0) +
				  getQuant(h, i, 1) +
				  getQuant(h, i, 2);

			setFinal(h, i, val);
		}
	}
}
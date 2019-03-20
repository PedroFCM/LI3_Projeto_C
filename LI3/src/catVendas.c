#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "global.h"
#include "avlstruct.h"

int verify_sell (AVL vendas, AVL prod, AVL client, GLOBAL set, char *sell, REGISTO reg) {
	
	int r = 1;

	char **campos = (char**) malloc(sizeof(char*) * CAMPOS_SELLS);	
	campos = tokenize(campos, sell);

	if (numb_spaces_in_string(sell) == 6) {

		/*VERIFICAR SE O PRODUTO EXISTE NA AVL PRODUTOS*/
		r = r && exist_element(prod, campos[1]);
		
		/*VERIFICAR SE O PRECO É VÁLIDO*/
		double price;
		sscanf(campos[2], "%lf", &price);
		r = r && (price >= 0.0 && price <= 999.99);

		/*VERIFICAR SE A QUANTIDADE COMPRADA É VÁLIDA*/
		int sold = atoi (campos[3]);
		r = r && (sold >= 1 && sold <= 200); 

		/*VERIFICAR SE O MODO DE COMPRA É VÁLIDO*/
		r = r && (campos[4][0] == 'P' || campos[4][0] == 'N');

		/*VERIFICAR SE O CLIENTE EXISTE NA AVL CLIENTES*/
		r = r && exist_element(client, campos[5]);
	
		/*VERIFICAR SE O MÊS DE COMPRA É VÁLIDO*/
		int month = atoi(campos[6]);
		r = r && (month >= 1 && month <= 12); 

		/*VERIFICAR SE A FILIAL É VÁLIDA*/
		int filial = atoi(campos[7]);
		r = r && (filial >= 1 && filial <= 3); 

		/*CRIA NOVO REGISTO CASO A VENDA SEJA VÁLIDA*/
		if (r == 1) { 

			reg -> codProd = strdup(campos[1]);
			reg -> preco = price;
			reg -> quantidade = sold;
			reg -> tipo = campos[4][0];
			reg -> codCli = strdup(campos[5]);
			reg -> mes = month;
			reg -> filial = filial;
		
		}
	}

	free(campos);

	return r;
}

AVL readNvalidate_sells (char* filename, AVL sells, GLOBAL set, AVL prod, AVL cli) {

	FILE *fp = fopen(filename, "r");
	
	int max = biggest_line_in_file(filename);	
	
	set -> max_line_sells = max;
	set -> num_sells      =   0;
	set -> val_sells      =   0;

	char *buffer = (char*) malloc(sizeof(char) * (2* max));

	while (fgets(buffer, max, fp)) {
		
		REGISTO novo_registo = (REGISTO) malloc(sizeof(struct registo));

		if (verify_sell(sells, prod, cli, set, buffer, novo_registo)) {
			
			sells = updateAVL(sells, novo_registo, buffer);

			set -> val_sells++;
		
		} else free(novo_registo);

		set -> num_sells++;
	}
	
	free(buffer);

	fclose(fp);
	
	return sells;
}
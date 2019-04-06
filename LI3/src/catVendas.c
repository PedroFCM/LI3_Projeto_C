
/** @file catVendas.c
*	@brief Ficheiro que efetua a leitura e validação das vendas.
*		   Contém também getters e setters essenciais ao programa.
*
*	@autor João Pedro Rodrigues Azevedo
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@bug Nenhum que tivessemos reparado.
*	
*/

/*----------------------------------------------------------------------*/

/**Macro usada para suprimir warnings de strdup do <string.h>*/
#define _GNU_SOURCE

/*----------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*----------------------------------------------------------------------*/

#include "global.h"
#include "avlstruct.h"
#include "catVendas.h"

/*----------------------------------------------------------------------*/

/**
* Struct para representar o registo de uma venda válida.
*/
struct registo {
	/*@{*/
	PRODUTO codProd; /**< Código do produto vendido. */
	double preco; /**< Preco do produto. */
	int quantidade; /**< Quantidade comprada. */
	char tipo; /**< Tipo da venda [N ou P]. */
	CLIENTE codCli; /**< Código do cliente que comprou. */
	int mes; /**< Mês da venda. */
	int filial; /**< Filial na qual foi feita a venda */
	/*@}*/
};

/*----------------------------------------------------------------------*/

/** @brief Função que insere uma filial num registo de venda.
 *
 *  @param reg Registo de venda.
 *  @param f filial para inserção
 *  @return void
*/

static void setFilial (REGISTO reg, int f);

/*----------------------------------------------------------------------*/

/** @brief Função que insere o mes de compra num registo.
 *
 *  @param reg Registo de venda.
 *  @param mes mes para inserção
 *  @return void
*/

static void setMes (REGISTO reg, int m);

/*----------------------------------------------------------------------*/

/** @brief Função que insere um cliente num registo.
 *
 *  @param reg Registo de venda.
 *  @param cliente cliente para inserção
 *  @return void
*/

static void setCodCliente (REGISTO reg, char* cliente);

/*----------------------------------------------------------------------*/

/** @brief Função que insere um tipo de compra a um registo.
 *
 *  @param reg Registo de venda.
 *  @param tp tipo de compra para inserção
 *  @return void
*/

static void setTipo (REGISTO reg, char tp);

/*----------------------------------------------------------------------*/

/** @brief Função que insere o preco de um produto a um registo.
 *
 *  @param reg Registo de venda.
 *  @param price preco para inserção
 *  @return void
*/

static void setPreco (REGISTO reg, double price);

/*----------------------------------------------------------------------*/

/** @brief Função que insere um produto a um registo.
 *
 *  @param reg Registo de venda.
 *  @param prod produto para inserção
 *  @return void
*/

static void setCodProd (REGISTO reg, char *prod);


/*----------------------------------------------------------------------*/

int verify_sell (CAT_VENDAS vendas, CAT_PRODUTOS prod, CAT_CLIENTES client, 
				 GLOBAL set, char *sell, REGISTO reg) {
	
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
			setCodProd(reg, campos[1]);
			setPreco(reg, price);
			setQuantidade(reg, sold);
			setTipo(reg, campos[4][0]);
			setCodCliente(reg, campos[5]);
			setMes(reg, month);
			setFilial(reg, filial);
		}
	}

	free(campos);

	return r;
}

CAT_VENDAS readNvalidate_sells (char* filename, CAT_VENDAS sells, GLOBAL set, 
								CAT_PRODUTOS prod, CAT_CLIENTES cli) {

	FILE *fp = fopen(filename, "r");
	
	if (fp==NULL) return NULL;

	int max = biggest_line_in_file(filename);	
	
	set -> max_line_sells = max;
	set -> num_sells      =   0;
	set -> val_sells      =   0;

	char *buffer = (char*) malloc(sizeof(char) * (2* max));

	while (fgets(buffer, max, fp)) {
		
		REGISTO novo_registo = NULL;
		novo_registo = initRegisto(novo_registo);

		if (verify_sell(sells, prod, cli, set, buffer, novo_registo)) {
			
			sells = updateAVL(sells, novo_registo, NULL, NULL, buffer, 0);
			set -> val_sells++;
		
		} else free(novo_registo);

		set -> num_sells++;
	}
	
	free(buffer);

	fclose(fp);
	
	return sells;
}

/*----------------------------------------------------------------------*/
						/*Getters & Setters*/

int getQuantidadeReg(REGISTO reg)
{
	return reg -> quantidade;
}

REGISTO initRegisto (REGISTO novo) {
	novo = (REGISTO) malloc(sizeof(struct registo));
	return novo;
}

int getFilial (AVL a) {
	return (getRegisto(a)->filial);
}

int getQuantidade (AVL a) {
	return (getRegisto(a)->quantidade);
}

char* getCodProd (AVL a) {
	return (getRegisto(a)->codProd);
}

char getTipo (AVL a) {
	return (getRegisto(a)->tipo);
}

CLIENTE getCodCliente (AVL a) {
	return (getRegisto(a)->codCli);
}

int getMes (AVL a) {
	return (getRegisto(a)->mes);
}

double getPreco (AVL a) {
	return (getRegisto(a)->preco);
}

void setQuantidade (REGISTO reg, int qt) {
	reg -> quantidade = qt;
}

/*----------------------------------------------------------------------*/
/*Setters privados*/

static void setFilial (REGISTO reg, int f) {
	reg -> filial = f;
}

static void setMes (REGISTO reg, int m) {
	reg -> mes = m;
}

static void setCodCliente (REGISTO reg, char* cliente) {
	reg -> codCli = strdup(cliente);
}

static void setTipo (REGISTO reg, char tp) {
	reg -> tipo = tp;
}

static void setPreco (REGISTO reg, double price) {
	reg->preco = price;
}

static void setCodProd (REGISTO reg, char *prod) {
	reg->codProd = strdup(prod);
}

void freeRegisto (REGISTO r) {
	free(r -> codProd);
	free(r -> codCli);
	free(r);
}
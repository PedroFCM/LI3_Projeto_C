#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "ler.h"

int numb_spaces_in_string (char *str) {

	int i, spaces = 0;
	for (i=0; str[i]; i++)
		if (str[i]==' ') spaces++;
	return spaces;
}

int verify_sell (char *sell) {
	
	int valid = 0;

	char *aux = strdup(sell);
	
	if (numb_spaces_in_string(aux) == 6) {

		char *store;

		store = strtok(aux, " ");
		valid = verify_product(store); 
		
		store = strtok(NULL, " ");
		float price;
		sscanf(store, "%f", &price);
		valid = valid && (price >= 0.0 && price <= 999.99); 
		
		store = strtok(NULL, " ");
		int sold = atoi (store);
		valid = valid && (sold >= 1 && sold <= 200); 
		
		store = strtok(NULL, " ");
		valid = valid && (!strcmp(store, "P") || !strcmp(store, "N")); 
		
		store = strtok(NULL, " ");
		valid = valid && verify_client(store); 
		
		store = strtok(NULL, " ");
		int month = atoi(store);
		valid = valid && (month >= 1 && month <= 12); 

		store = strtok(NULL, " ");
		int filial = atoi(store);
		valid = valid && (filial >= 1 && filial <= 3); 
	}

	return valid;
}

void readNvalidate_sells (char* filename, char *sells[], FILE_SETTINGS *set) {

	FILE *fp = fopen(filename, "r");
	char *buffer = (char*) malloc(sizeof(char)*64);
	int validos = 0, i = 0;

	while (fgets(buffer, 64, fp)) {
		if (verify_sell(buffer)) {
			sells[validos] = strdup(buffer);
			validos++;
		}
		i++;
	}
	
	free(buffer);

	set -> num_sells = i;
	set -> val_sells = validos;
}

int verify_client (char *client) {
	
	char *aux = strdup(client);
	int numb = atoi (aux+1);

		if (numb >= 1000 && numb <= 5000)
			if (isupper(aux[0]) &&
				isdigit(aux[1]) && isdigit(aux[2]) &&
				isdigit(aux[3]) && isdigit(aux[4]))
					return 1;
				else return 0;
		else return 0;
}

void readNvalidate_clients (char *filename, char *clientes[], FILE_SETTINGS *set) {

	FILE *fp = fopen(filename, "r");
	char *buffer = (char*) malloc(sizeof(char)*64);
	int validos = 0, i=0;

	while (fgets(buffer, 64, fp)) {
		if (verify_client(buffer)) {
			clientes[validos] = strdup(buffer);
			validos++;
		}
		i++;
	}
	
	free(buffer);

	set -> num_clients = i;
	set -> val_clients = validos;

}

int verify_product (char *product) {

	char *aux = strdup(product);

	int numb = atoi (aux+2);
		if (numb >= 1000 && numb <= 9999)
			if (isupper(aux[0]) && isupper(aux[1]) &&
				isdigit(aux[2]) && isdigit(aux[3]) &&
				isdigit(aux[4]) && isdigit(aux[5]))
					return 1;
				else return 0;
		else return 0;
}

void readNvalidate_products (char* filename, char *produtos[], FILE_SETTINGS *set) {

	FILE *fp = fopen(filename, "r");
	char *buffer = (char*) malloc(sizeof(char)*64);
	int validos = 0, i=0;

	while (fgets(buffer, 64, fp)) {
		if (verify_product(buffer)) {
			produtos[validos] = strdup(buffer);
			validos++;
		} else set->nulo = i+1;
		i++;
	}
	
	free(buffer);

	set->num_prods = i;
	set->prods_val = validos;
}

void print_sells (char *sells[], FILE_SETTINGS *set) {

	int i=0, size = set -> val_sells;
	
	while (i < size) {
		printf("%s", sells[i]);
		i++;
	}

	printf("\nNº de readed lines: %d\n",        set->num_sells);
	printf("Nº of valid sells (printed): %d\n", set->val_sells);
	printf("Linha invalida: %d\n", set->nulo);
	
}

void print_clients (char *clients[], FILE_SETTINGS *set) {

	int i=0, size = set -> val_clients;
	
	while (i < size) {
		printf("%s", clients[i]);
		i++;
	}

	printf("\nNº de readed lines: %d\n",        set->num_clients);
	printf("Nº of valid clients (printed): %d\n", set->val_clients);
	printf("Linha invalida: %d\n", set->nulo);
	
}

void print_products (char *produtos[], FILE_SETTINGS *set) {

	int i=0, size = set->prods_val;
	
	while (i < size) {
		printf("%s", produtos[i]);
		i++;
	}

	printf("\nNº de readed lines: %d\n",        set->num_prods);
	printf("Nº of valid products (printed): %d\n", set->prods_val);
	printf("Linha invalida: %d\n", set->nulo);
	
}

void write_products_on_file (char *produtos[], FILE_SETTINGS *set) {

	FILE *fp = fopen("validData/Produtos(validados).txt", "w");
	int i = 0, size = set->prods_val;

	while (i<size) {
		fprintf(fp, "%s", produtos[i]);
		i++;
	}

}

void write_clients_on_file (char *clients[], FILE_SETTINGS *set) {

	FILE *fp = fopen("validData/Clientes(validados).txt", "w");
	int i = 0, size = set->val_clients;

	while (i<size) {
		fprintf(fp, "%s", clients[i]);
		i++;
	}

}

void write_sells_on_file (char *sells[], FILE_SETTINGS *set) {

	FILE *fp = fopen("validData/Vendas(validadas).txt", "w");
	int i = 0, size = set->val_sells;

	while (i<size) {
		fprintf(fp, "%s", sells[i]);
		i++;
	}

}
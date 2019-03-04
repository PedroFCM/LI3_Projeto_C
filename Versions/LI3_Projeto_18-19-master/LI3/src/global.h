#ifndef _LER_
#define _LER_

//_______________________________________________________//

#define PROD_PATH "datafiles/Produtos.txt"
#define CLIE_PATH "datafiles/Clientes.txt"
#define SELL_PATH "datafiles/Vendas_1M.txt"

//_______________________________________________________//

#define VAL_PROD_PATH "validData/Produtos(validados).txt"
#define VAL_CLIE_PATH "validData/Clientes(validados).txt"
#define VAL_SELL_PATH "validData/Vendas(validadas).txt"

//_______________________________________________________//

typedef struct settings {

	int num_prods, num_clients, num_sells;
	
	int val_prods, val_clients, val_sells;

	int max_line_prods, max_line_clients, max_line_sells;

} GLOBAL;

//_______________________________________________________//

int biggest_line_in_file (char *filename);

int numb_spaces_in_string (char *str);

int exist_element (int flag, char *element, char **prod, char **cli, GLOBAL *set);

#endif
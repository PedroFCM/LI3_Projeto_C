
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

/**MACRO para suprimir warnings de strdup do <string.h>*/
#define _GNU_SOURCE

/*---------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*---------------------------------------------------------------------------------------------*/

#include "Filial.h"
#include "avlstruct.h"
#include "hashtables.h"
#include "catVendas.h"
#include "lstring.h"

/*---------------------------------------------------------------------------------------------*/

/**
* Struct que representa um array de AVL para representar
* os registo dos clientes, por filial e a faturacao dos produtos
* vendidos.
*/
struct filial {
	/*@{*/
	AVL filial; /**< AVL para guardar a gestão de filial. */
	/*@}*/
};

/**
* Struct que representa um registo de um cliente e os produtos comprados.
*/
struct gestaoFilial {
	/*@{*/
	char* codCliente; /**< Registo do cliente (string). */
	ELEM list; /**< Lista de produtos comprados contendo a sua faturacao e quantidade vendida. */
	/*@}*/
};

/**
* Struct que representa a lista linked de produtos comprados por um dado cliente.
*/
struct elementos {
	/*@{*/
	char* produto; /**< Registo do produto comprado pelo cliente (string). */
	VENDAS numVendas; /**< Matriz com a quantidade vendida desse produto por mes e tipo (N/P). */
	FAT_MES fatMes; /**< Matriz com a faturacao desse produto por mes e tipo (N/P). */
    struct elementos * next;
	/*@}*/
};

/*-----------------------------------------------------------------------*/

/** @brief Função que insere um novo produto na lista de comprados pelo cliente.
 *
 *  @param l Lista de elementos comprados.
 *  @param elem elemento a inserir.
 *  @param modo tipo de compra.
 *  @param quant quantidade comprada.
 *  @param preco preco de venda.
 *  @param mes mes no qual foi vendido.
 *  @return Lista apos update/insercao.
 */

static ELEM pushLista (ELEM l, char* elem, char modo, int quant, float preco, int mes);

/*-----------------------------------------------------------------------*/

/** @brief Função que faz update/insercao de um cliente numa AVL filial
 *
 *  @param filial AVL para inserção.
 *  @param vendas AVL de vendas para procurar o produto comprado pelo cliente c.
 *  @param c cliente de procura.
 *  @param r flag, se estiver a 0 indica que o cliente não existe e por isso cria uma nova gestao de cliente na filial.
 *  @return Lista apos update/insercao.
 */

static void updateGestaoFilial (AVL filial, AVL vendas, char *c, int *r);

/*-----------------------------------------------------------------------*/

/** @brief Função que cria uma nova struct gestao de filial caso o cliente nao exista
 *         out atualiza-o caso já exista.
 *
 *  @param filial AVL para inserção.
 *  @param vendas AVL de vendas para procurar o produto comprado pelo cliente c.
 *  @param c cliente de procura.
 *  @param r flag, se estiver a 0 indica que o cliente não existe e por isso cria uma nova gestao de cliente na filial.
 *  @return Lista apos update/insercao.
 */

static void insereClienteFat (int fi, AVL *filial, AVL vendas);





/*-----------------------------------------------------------------------*/


static ELEM pushLista (ELEM l, char* elem, char modo, int quant, float preco, int mes) {

	ELEM new = malloc (sizeof(struct elementos));
	ELEM *pt = &l;

    if(existeNaLista(elem, *pt)){

	    while (strcmp(elem, (*pt) -> produto) != 0)
	    	pt = &((*pt) -> next);
   
	    switch (modo) {

			case 'N':
					setFatFilial(*pt, 0, mes-1, preco*quant);
					setVendasFilial(*pt, 0, mes-1, quant);
					return l;

			case 'P':			
					setFatFilial(*pt, 1, mes-1, preco*quant);
					setVendasFilial(*pt, 1, mes-1, quant);
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
				setVendasFilial(new, 0, mes-1, quant);
				break;

		case 'P':
				setFatFilial(new, 1, mes-1, preco*quant);
				setVendasFilial(new, 1, mes-1, quant);
				break;

		default: break;
		}

	    new -> produto = strdup(elem);
	    new -> next = *pt;   
	    *pt = new;
	} 

	return l;
}

static void updateGestaoFilial (AVL filial, AVL vendas, char *c, int *r) {
	
	if (filial != NULL) {

		int cmp = strcmp(c, getClienteFilial(getGestaoFilial(filial)));

		if (!cmp) {

			*r = 1;

		getGestaoFilial(filial) -> list = pushLista(getList(getGestaoFilial(filial)), getCodProd(vendas), getTipo(vendas), getQuantidade(vendas), getPreco(vendas), getMes(vendas));

		} else if (cmp > 0)

			updateGestaoFilial (getDir(filial), vendas, c, r);
		
		else 
			updateGestaoFilial (getEsq(filial), vendas, c, r);
	}	
}

static void insereClienteFat (int fi, AVL *filial, AVL vendas) {

	int *r = malloc(sizeof(int));
 
	if (vendas != NULL) {

		if (fi == getFilial(vendas)) {

			*r = 0;

			updateGestaoFilial(*filial, vendas, getCodCliente(vendas), r);

			if (*r == 0) {

				GESTAO_FILIAL gfilial = (GESTAO_FILIAL) malloc(sizeof(GESTAO_FILIAL));
				ELEM* new = (ELEM*) malloc(sizeof(ELEM));
				*new = NULL;
				
				setClienteFilial(getCodCliente(vendas), gfilial);

				gfilial -> list = *new;

				*filial = updateAVL(*filial, NULL, NULL, gfilial, getCodCliente(vendas), 3);

				updateGestaoFilial(*filial, vendas, getCodCliente(vendas), r);

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

int existeNaLista (char* elem, ELEM l) {

	int r = 0;

	ELEM *pt = &l;

    while ((*pt) != NULL && r != 1) {

    	if (!strcmp(elem, (*pt) -> produto)) r = 1;
	    pt = &((*pt) -> next);
    }

    return r;
}

int exist_elementFilial (AVL a, char *element) {
 
    int r = 0;

    while (a != NULL) {

        r = strcmp(getClienteFilial(getGestaoFilial(a)), element);

        if (r == 0) return 1;
        else if (r > 0) return exist_elementFilial(getDir(a), element);
        else if (r < 0) return exist_elementFilial(getEsq(a), element);
    }

    return 0;
}

AVL compraramEmTodas(FILIAL filial, AVL clientes, AVL *compramEmTodas){

    if(clientes != NULL)
    {

        if (exist_elementFilial(getAVLfilial(filial,1), getTag(clientes)) == 0 &&
       	 	exist_elementFilial(getAVLfilial(filial,2), getTag(clientes)) == 0 &&
        	exist_elementFilial(getAVLfilial(filial,3), getTag(clientes)) == 0) 
        	*compramEmTodas = updateAVL (*compramEmTodas, NULL, NULL, NULL, getTag(clientes), 5);

        *compramEmTodas = compraramEmTodas(filial, getEsq(clientes), compramEmTodas);
        *compramEmTodas = compraramEmTodas(filial, getDir(clientes), compramEmTodas);
    }

    return *compramEmTodas;
}

LString top3Compras_do_cliente (AVL filial, char* cliente, LString produtos) {

	if (filial != NULL) {

		if (strcmp(getClienteFilial(getGestaoFilial(filial)), cliente) == 0) {

			produtos = insereNaListDeProdutosComprados(getList((getGestaoFilial(filial))), produtos); 
			
		}

		produtos = top3Compras_do_cliente(getEsq(filial), cliente,produtos);		
		produtos = top3Compras_do_cliente(getDir(filial), cliente,produtos);

	}

	return produtos;
}

void acumVendas(AVL filial, AVL *prodMaisComprad, int mes)
{
	int i, r;
	ELEM *pt = &(getGestaoFilial(filial) -> list);   
			
	while(*pt != NULL)
	{
		r = 0;

		for(i = 0; i < 2; i++)
			r += ((*pt) -> numVendas)[i][mes];
		
		REGISTO regist = NULL;
		regist = initRegisto(regist); 
		setQuantidade(regist, r);

		if(r)
			*prodMaisComprad = updateAVL(*prodMaisComprad, regist, NULL, NULL, getProdutoFilial(*pt), 4);

		pt = &((*pt) -> next);
	}
}

void clientesSemCompra (FILIAL fil, AVL clientes, int *clientesSC) {

	if (clientes != NULL) {

		if (!existeClienteNaAVLFilial(getAVLfilial(fil, 1), getTag(clientes)) &&
			!existeClienteNaAVLFilial(getAVLfilial(fil, 2), getTag(clientes)) &&
			!existeClienteNaAVLFilial(getAVLfilial(fil, 3), getTag(clientes))) {
			*clientesSC += 1;
		}

		clientesSemCompra(fil, getEsq(clientes), clientesSC);
		clientesSemCompra(fil, getDir(clientes), clientesSC);
	}

}

int existeClienteNaAVLFilial (AVL a, char* elem) {

	int r;

	if (a != NULL) {

		r = strcmp(elem, getClienteFilial(getGestaoFilial(a)));

		if (r==0) return 1;
		else if (r > 0) return existeClienteNaAVLFilial(getDir(a), elem);
		else return existeClienteNaAVLFilial(getEsq(a), elem);

	}

	return r;
}

int** tabelaComprasFilial (AVL filial, char* cliente, int** nProd, int flag) {

	if (filial != NULL) {

		if (strcmp(getClienteFilial(getGestaoFilial(filial)), cliente) == 0) {
			somaVendas(nProd, getList(getGestaoFilial(filial)), flag);
		}

		nProd = tabelaComprasFilial(getEsq(filial), cliente, nProd, flag);		
		nProd = tabelaComprasFilial(getDir(filial), cliente, nProd, flag);

	}

	return nProd;
}

char* getProdutoFilial(ELEM filial){

	return filial->produto;
}

LString insereNaListDeProdutosComprados (ELEM elem, LString l){

	ELEM *pt = &elem;

	while (*pt != NULL) {
		
		l = insertLString2(l, getProdutoFilial(*pt), sumatorioMatriz(getFatMesElem(*pt))); 
		pt = &((*pt) -> next);
	}	

	return l;
}

float sumatorioMatriz(float **matriz){

	float res;
	int i,j;
	res = i= j = 0;
	
	for(i = 0; i < 2; i++)
		for(j = 0; j < 12; j++) 
			res += matriz[i][j];

	return res;

}

FAT_MES getFatMesElem (ELEM elem) {
	return elem->fatMes;
}
AVL getAVLfilial (FILIAL f, int fi) {
	return f[fi-1].filial;
}

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


void setClienteFilial (char *c, GESTAO_FILIAL g) {
	g->codCliente = strdup(c);

}


void setFatFilial (ELEM elem, int l, int c, double val) {
	
	elem -> fatMes[l][c] += val;
}

void setVendasFilial (ELEM elem, int l, int c, int quant) {

	elem -> numVendas[l][c] += quant;
}

char* getClienteFilial(GESTAO_FILIAL filial) {
	return filial -> codCliente;
}

ELEM getList(GESTAO_FILIAL g){

	return g -> list;
}

void setList(AVL filial, ELEM l){

	(getGestaoFilial(filial)) -> list  = l;
}

void printMATRIXFilial (FAT_MES f, VENDAS v, int opcao) {

	int i, j;

	switch(opcao) {

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

void printElem(ELEM elementos){

	ELEM *pt = &elementos;
	
	while ((*pt) != NULL) {

		printf("%s\n", (*pt) -> produto);
		printMATRIXFilial((*pt) -> fatMes, (*pt) -> numVendas, 0);
		printMATRIXFilial((*pt) -> fatMes, (*pt) -> numVendas, 1);
		pt = &((*pt) -> next);
	
	}
		
}

void printFilial (AVL filial) {

	if (filial != NULL) {

		printFilial(getEsq(filial));		

		printf("\nCliente: %s.\n", (getClienteFilial(getGestaoFilial(filial))));
		
		printf("Produto:\n");
		printElem(getGestaoFilial(filial) -> list);

		printFilial(getDir(filial));

	}
}

void somaMatrizes(int **nProd, int **atual, int flag){

	int j = 0;

	for (j = 0; j < 12; j++){
		
			nProd[j][flag-1] += atual[0][j] + atual[1][j];
		}

}

void somaVendas(int **nProd, ELEM elem, int flag){
	
	ELEM *pt = &elem;

	while (*pt != NULL) {
		somaMatrizes(nProd, getNumVendasElem(*pt), flag);
		pt = &((*pt) -> next);
	}
}


VENDAS getNumVendasElem (ELEM elem) {
	return elem->numVendas;
}

void procuraNaFilial (AVL vendas, int filial[], char* cliente) {

	if( (filial[0]+filial[1]+filial[2] < 3) && vendas != NULL) {

		if( !strcmp(getCodCliente(vendas), cliente) )
			filial[getFilial(vendas) - 1] = 1;

		procuraNaFilial(getEsq(vendas), filial, cliente);
		procuraNaFilial(getDir(vendas), filial, cliente);

	}
}

int sumatorioMatrizInt(int **matriz){

	int res;
	int i,j;
	res = i= j = 0;
	
	for(i = 0; i < 2; i++)
		for(j = 0; j < 12; j++) 
			res += matriz[i][j];

	return res;

}

void updateQuantidadesProduto(ELEM l, HEAD_TABLE h, int flag){

	ELEM *pt = &l;
	int r = 0;

	while (*pt != NULL && r != 1) {

		update (h, getProdutoFilial(*pt), flag, sumatorioMatrizInt(getNumVendasElem(*pt)), 1);

		pt = &((*pt) -> next);
	}
	
}

void cria_avl_produtos_Comprados(AVL filial, AVL* prodMaisComprad, char* cliente, int mes) 
{
	if(filial != NULL)
	{
		int equal = strcmp(getClienteFilial(getGestaoFilial(filial)), cliente);

		if(!equal)
			acumVendas(filial, prodMaisComprad, mes);

		else
		{
			if(equal > 0)
				cria_avl_produtos_Comprados(getEsq(filial), prodMaisComprad, cliente, mes);
			else
				cria_avl_produtos_Comprados(getDir(filial), prodMaisComprad, cliente, mes);
		}

	}
}


void freeFilial (FILIAL fil) {
	freeAVLfil(fil[0].filial);
	freeAVLfil(fil[1].filial);
	freeAVLfil(fil[2].filial);
}

void freeGestaoFilial (GESTAO_FILIAL g) {
	free(g->codCliente);
	free(g->list);
}

/*-----------------------------------------------------------------------*/
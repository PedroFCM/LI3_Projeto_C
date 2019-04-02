
/** @file queries.h
*	@brief Header file de queries.c
*
*	@autor João Pedro Rodrigues Azevedo (A85227) 
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@bug Nenhum que tivessemos reparado.
*	
*/

/*______________________________________________________________________*/

#ifndef _QUERIES_
#define _QUERIES_

/*_________________BIBLIOTECAS IMPLEMENTADAS____________________________*/

#include "stack.h"
#include "lstring.h"
#include "hashtables.h"
#include "Faturacao.h"
#include "Filial.h"
/*______________________________________________________________________*/

void query6 (FAT_FILIAL fat, FILIAL fil, AVL produtos, AVL clientes);
void clientesQuery6 (FILIAL fil, AVL clientes, int filial, int *clientesSC);
int existeClienteNaAVLFilial (AVL a, char* elem);
void produtosQuery6 (FILIAL fil, AVL clientes, int filial, int *produtosNC);
int existeProdutoNaAVLFilial (AVL a, char* elem);
/** @brief Função que gere a query1.
 *
 *  @param set Struct que contém as informações de leitura.
 *  @return void.
*/

void query1 (GLOBAL set);


/** @brief Função que implementa a query2.
 *
 *  @param ls Lista de produtos para inserção.
 *  @param produtos AVL que guarda os produtos validos.
 *  @param c letra que o user pretende para guardar os produtos
 *		     que se iniciam por essa letra.
 *  @return A lista dos produtos iniciados por essa letra.
*/

LISTA_PROD query2 (LISTA_PROD ls, AVL produtos, char c);

void query3 (FAT_FILIAL fat, int mes, char *produto, int opcao);
void recursive_query3(AVL faturacao, int filial, char* prod, int mes, FAT_MES f, VENDAS v);
void showStatGlobal(VENDAS n_vendas, FAT_MES faturacao);
void showStatPorFilial(VENDAS n_vendas, FAT_MES faturacao);

/** @brief Função para apresentacao de resultados da query3.
 *
 *  @param f struct faturacao.
 *  @return void.
*/

/*void showFaturacaoGlobal_query3 (FAT f);*/


/** @brief Função para apresentacao de resultados da query3.
 *
 *  @param f struct faturacao.
 *  @return void.
*/
/*
void showFaturacaoPorFilial_query3 (FAT prod);
*/

/** @brief Função que implementa a query3.
 *
 *  @param vendas AVL que guarda as vendas validas.
 *  @param mes variavel de procura mes.
 *  @param produto produto para procura 
 *  @param opcao flag, 0: resultado por filial, 1: resultado global 
 *  @return void.
*/
/*
void query3 (AVL vendas, int mes, char *produto, int opcao);
*/

/** @brief Função que implementa a query5.
 *
 *  @param vendas AVL que armazena as vendas validas
 *  @return void.
*/
int existFaturacao(AVL fat, char* produto);
void recursive_query4(FAT_FILIAL fat, AVL produtos, AVL* produtoFilial1, AVL* produtoFilial2, AVL* produtoFilial3);
void query4(FAT_FILIAL fat, AVL produtos);
void query5(FILIAL filial, AVL clientes);
AVL recursive_query5(FILIAL filial, AVL clientes, AVL *compramEmTodas);
int exist_elementFilial (AVL a, char *element);

/** @brief Função que implementa a query7.
 *
 *  @param cliente cliente para procura.
 *  @param vendas AVL que armazena as vendas validas
 *  @return void.
*/

void query7(AVL vendas, char* cliente);


/** @brief Função que auxilia a query7.
 *
 *  @param cliente cliente de procura.
 *  @param nProd array que armazena o resultado da função.
 *  @param vendas AVL que armazena as vendas validas
 *  @return void.
*/

void recursive_query7 (AVL vendas, char* cliente, int** nProd);

void recursive_query8(AVL fat, int min, int max, float* faturacao, int* total_vendas);
void query8(FAT_FILIAL fat, int min, int max);

void query9 (AVL vendas, char* produto, int filial);

/** @brief Função que implementa a query9.
 *
 *  @param produto produto de pesquisa.
 *  @param filial filial de procura.
 *  @param vendas AVL que armazena as vendas validas
 *  @return void.
*//*
void query9 (FILIAL fil, char *codProd, int filial);
void geraClientesFilial (AVL fil, char *codProd, LString comprasN, LString comprasP);
int matrizAzeros (float **f, int flag);
*/
/** @brief Função auxilial da query10.
 *         Utiliza uma lista como struct de apoio à procura e armazenamento de dados.
 *
 *  @param cliente cliente de procura.
 *  @param mes mes de procura.
 *  @param produtos LString para guardar resultados de leitura (não nula).
 *  @return void.
*/

LString recursive_query10 (AVL vendas, char* cliente, int mes, LString produtos);


/** @brief Função que implementa a query10.
 *
 *  @param mes mes de procura.
 *  @param vendas AVL que armazena as vendas validas
 *  @param cliente cliente de procura na AVL vendas.
 *  @return void.
*/

void query10 (AVL vendas, char* cliente, int mes);


/** @brief Função que auxilia a query11.
 *		   Usa uma hashtable e gera na mesma os resultados.
 *  @param vendas AVL de vendas validas.
 *  @param h HashTable para armazenar os resultados.
 *  @return void.
*/

void recursive_query11(AVL vendas, HEAD_TABLE h);


/** @brief Função que implementa a query11.
 *
 *  @param vendas AVL de vendas validas.
 *  @param n número de elementos para imprimir da hashtable.
 *  @return void.
*/

void query11 (AVL vendas, int n);


/** @brief Função que auxilia a query11.
 *
 *  @param vendas AVL de vendas validas.
 *  @param cliente CLIENTE de procura.
 *  @param produtos Lista de armazenamento de produtos
 *  @return lista com os produtos armazenados.
*/

LString recursive_query12 (AVL vendas, char* cliente, LString produtos);


/** @brief Função que implementa a query12.
 *
 *  @param vendas AVL de vendas validas.
 *  @param cliente CLIENTE de procura.
 *  @return void.
*/

void query12 (AVL vendas, char* cliente);

#endif
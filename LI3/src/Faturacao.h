
/** @file Faturacao.h
*	@brief Ficheiro header de .
*
*	@autor João Pedro Rodrigues Azevedo
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@bug Nenhum que tivessemos reparado.
*	
*/

/*-----------------------------------------------------------------------*/

#ifndef _FATURACAO_
#define _FATURACAO_

/*-----------------------------------------------------------------------*/

#include "avlstruct.h"

/*-----------------------------------------------------------------------*/

/** Type para definir um float** */
typedef float** FAT_PRECO;
/** Type para definir um int** */
typedef int** FAT_QUANT;
/** Type para definir um array de structs faturacao** */
typedef struct faturacao *FAT_FILIAL;
/** Type para definir uma struct fatura** */
typedef struct fatura *FATURA;
/** Type para definir um float** */
typedef float** FAT_MES;
/** Type para definir um int** */
typedef int** VENDAS;

/*-----------------------------------------------------------------------*/

/** @brief Função mais generica que verifica se um produto existe numa Faturacao.
 *
 *  @param fat AVL faturacao.
 *  @param produto elemento para procurar.
 *  @return 1 caso exista.
 */

int existFaturacao(AVL fat, char* produto);

/*-----------------------------------------------------------------------*/


/** @brief Função mais generica que gera a faturacao num mes dada uma filial e um produto.
 *
 *  @param fat AVL faturacao.
 *  @param prod produto para procurar.
 *  @return void.
 */

void vendasNoMes (AVL faturacao, int filial, char* prod, int mes, FAT_MES f, VENDAS v);

/*-----------------------------------------------------------------------*/


/** @brief Função que gera a lista de produtos que ninguem comprou por filial ou o caso geral.
 *
 *  @param fat Array com a faturacao por filial.
 *  @param produtos AVL de produtos validos.
 *  @param produtoFilial1 AVL de produtos nao comprados na filial 1 (para guarda-los).
 *  @param produtoFilial2 AVL de produtos nao comprados na filial 2 (para guarda-los).
 *  @param produtoFilial3 AVL de produtos nao comprados na filial 3 (para guarda-los).
 *  @param opcao selecionar 1 se quiser o caso global (nas 3 filiais)
 *  @return void.
 */

void prodNinguemComprou(FAT_FILIAL fat, AVL produtos, AVL* produtoFilial1, AVL* produtoFilial2, AVL* produtoFilial3, int opcao);

/*-----------------------------------------------------------------------*/

/** @brief Função que qera a faturacao num intervalo de meses.
 *
 *  @param fat AVL faturacao de uma filial.
 *  @param min mes inferior.
 *  @param max mes superior.
 *  @param faturacao para guardar a faturacao.
 *  @param total_vendas para guardar a quantidade.
 *  @return void.
 */

void vendasEntreMeses(AVL fat, int min, int max, float* faturacao, int* total_vendas);

/*-----------------------------------------------------------------------*/

/** @brief Função que que retorna a matriz faturacao de uma AVL.
 *
 *  @param f array de faturacao por filial.
 *  @param i filial pretendida.
 *  @return AVL de faturacao escolhida.
 */

AVL getFaturacao(FAT_FILIAL f, int i);

/*-----------------------------------------------------------------------*/

/** @brief Função que imprime a AVL faturacao (para debug).
 *
 *  @param fat AVL de faturacao.
 *  @return void.
 */

void printFaturacao (AVL fat);

/*-----------------------------------------------------------------------*/

/** @brief Função que imprime uma matriz (de floats ou ints).
 *
 *  @param fat AVL de faturacao.
 *  @return void.
 */

void printMATRIX (FAT_MES f, VENDAS v, int opcao);

/*-----------------------------------------------------------------------*/

/** @brief Função que inicializa as matrizes da fatura.
 *
 *  @param f matriz de faturacao.
 *  @param v matriz de vendas. 
 *  @return void.
 */

void initFatura (FAT_MES f, VENDAS v);

/*-----------------------------------------------------------------------*/

/** @brief Função que coloca um elemento val num posicao l, c das matrizes da fatura.
 *
 *  @param f Struct fatura.
 *  @param l linha. 
 *  @param c coluna.
 *  @return void.
 */

void setFatMes (FATURA f, int l, int c, double val);

/*-----------------------------------------------------------------------*/

/** @brief Função que coloca um elemento val num posicao l, c das matrizes da fatura.
 *
 *  @param f Struct fatura.
 *  @param l linha. 
 *  @param c coluna.
 *  @return void.
 */

void setVendas (FATURA f, int l, int c);

/*-----------------------------------------------------------------------*/

/** @brief Função que retorna a matriz de vendas de uma fatura.
 *
 *  @param f Struct fatura.
 *  @return matriz de vendas.
 */

VENDAS getNumVendas (FATURA f);

/*-----------------------------------------------------------------------*/


/** @brief Função que retorna a matriz de faturacao de uma fatura.
 *
 *  @param f Struct fatura.
 *  @return matriz de faturacao.
 */

FAT_MES getFatMes (FATURA f);

/*-----------------------------------------------------------------------*/


/** @brief Função que inicializa as matrizes com zeros.
 *
 *  @param fat fatura.
 *  @param f matriz de faturacao.
 *  @param v matriz de vendas.
 *  @return void.
 */

void initMatriz(FATURA fat, FAT_MES f,VENDAS v);

/*-----------------------------------------------------------------------*/

/** @brief Função que retorna o produto de uma fatura.
 *
 *  @param f fatura.
 *  @return o produto.
 */

char* getProdFatura (FATURA f);

/*-----------------------------------------------------------------------*/

/** @brief Função que imprime uma AVL de faturacao.
 *
 *  @param fat fatura.
 *  @return void.
 */

void printFaturacao (AVL fat);

/*-----------------------------------------------------------------------*/

/** @brief Função que retorna a AVL de um array de AVL's de Filiais.
 *
 *  @param f array de filiais.
 *  @param filial filial para escolha.
 *  @return AVL de faturacao.
 */

AVL getFaturacao (FAT_FILIAL f, int filial);

/*-----------------------------------------------------------------------*/

/** @brief Função que retorna um produto de uma fatura.
 *
 *  @param f fatura.
 *  @return o produto.
 */

char* getProdFatura (FATURA f);

/*-----------------------------------------------------------------------*/


/** @brief Função que insere novos campos numa nova fatura.
 *
 *  @param f fatura.
 *  @param preco double preco para adicionar.
 *  @param quant quantidade vendida.
 *  @param modo tipo da venda.
 *  @param mes mes de venda.
 *  @return void.
 */

void insereNaFatura (FATURA f, double preco, int quant, char modo, int mes);

/*-----------------------------------------------------------------------*/


/** @brief Função que insere uma produto num AVL de faturacao de uma filial.
 *
 *  @param filial a filial pretendida.
 *  @param fatFilial AVL nova para inserção.
 *  @param vendas AVL catalogo de vendas validas.
 *  @return void.
 */

void insereProdFat (int filial, AVL *fatFilial, AVL vendas);

/*-----------------------------------------------------------------------*/


/** @brief Função que inicializa a faturacao de um produto.
 *
 *  @param nova Array de faturacao (AVL's).
 *  @param prod AVL de produtos para adicionar.
 *  @param vendas AVL catalogo de vendas validas.
 *  @return array apos insercao.
 */

FAT_FILIAL initFaturacao (FAT_FILIAL nova, AVL prod, AVL vendas);

/*-----------------------------------------------------------------------*/

/** @brief Função que insere uma nova fatura ou atualiza uma existente.
 *
 *  @param fatFilial AVL nova para inserção.
 *  @param vendas AVL catalogo de vendas validas.
 *  @param vendas AVL catalogo de vendas validas.
 *  @param p novo produto
 *  @param r variavel para indicar se o produto ja existe ou nao
 *  @return void.
 */

void updateFatura (AVL fatFilial, AVL vendas, char *p, int *r);

/*-----------------------------------------------------------------------*/

/** @brief Função que insere um produto numa fatura.
 *
 *  @param p produto para insercao.
 *  @param f fatura.
 *  @return void.
 */

void setProdFatura (char* p, FATURA f);

#endif
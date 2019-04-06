
/** @file Filial.h
*	@brief Ficheiro header para o Filial.c.
*
*	@autor João Pedro Rodrigues Azevedo
*	@autor Paulo Jorge da Silva Araújo 
*	@autor Pedro Filipe Costa Machado 
*
*	@bug Nenhum que tivessemos reparado.
*	
*/

#ifndef _FILIAL_
#define _FILIAL_

/*---------------------------------------------------------------------------------------------*/

#include "avlstruct.h"
#include "hashtables.h"
#include "lstring.h"

/*---------------------------------------------------------------------------------------------*/

/** Define um array de AVL filiais.*/
typedef struct filial *FILIAL;

/** Define uma matriz de floats.*/
typedef float** FAT_MES;

/** Define uma matriz de ints.*/
typedef int** VENDAS;

/** Define uma AVL.*/
typedef struct avl *AVL;

/** Define uma celula de uma AVL, uma gestao de filial.*/
typedef struct gestaoFilial* GESTAO_FILIAL;

/** Define uma lista linked de produtos comprados por um cliente.*/
typedef struct elementos* ELEM;

/*-----------------------------------------------------------------------*/

/** @brief Função que liberta memoria de uma filial
 *
 *  @param fil array de avl filial
 *  @return void.
 */

void freeFilial (FILIAL fil);

/*-----------------------------------------------------------------------*/

/** @brief Função que liberta memoria de uma gestao de filial
 *
 *  @param g gestao de filial
 *  @return void.
 */

void freeGestaoFilial (GESTAO_FILIAL g);

/*-----------------------------------------------------------------------*/

/** @brief Função que atualiza a AVL prodMaisComprad com os produtos comprados por um dado cliente
 *
 *  @param filial AVL Avl filial para procurar o cliente.
 *  @param prodMaisComprad Avl que contem os produtos comprados por um dado cliente.
 *  @param mes flag para filtrar o resultado pretendido (apenas num dado mes).
 *  @return void.
 */

void acumVendas(AVL filial, AVL *prodMaisComprad, int mes);

/*-----------------------------------------------------------------------*/


/** @brief Função que cria a AVL dos clientes que compram em todas as Filiais
 *
 *  @param filial array de AVL de filiais.
 *  @param clientes AVL de clientes.
 *  @param compramEmTodas AVL para guardar o resultado.
 *  @return uma AVL.
 */

AVL compraramEmTodas(FILIAL filial, AVL clientes, AVL *compramEmTodas);

/*-----------------------------------------------------------------------*/


/** @brief Função contabiliza numa flag clientesSC quantos clientes (dos registados) não compraram nada
 *
 *  @param fil array de AVL de filiais.
 *  @param clientes AVL de clientes registados.
 *  @param clientesSC counter que será incrementado.
 *  @return void.
 */

void clientesSemCompra (FILIAL fil, AVL clientes, int *clientesSC);

/*-----------------------------------------------------------------------*/


/** @brief Função que verifica se um cliente existe num AVL de filial
 *
 *  @param a AVL filial.
 *  @param elem elemento de procura.
 *  @return 1 caso exista.
 */

int existeClienteNaAVLFilial (AVL a, char* elem);

/*-----------------------------------------------------------------------*/


/** @brief Função que retorna a matriz faturacaoMes de uma lista de produtos comprados
 *
 *  @param fil array de AVL de filiais.
 *  @param clientes AVL de clientes registados.
 *  @param clientesSC counter que será incrementado.
 *  @return void.
 */

FAT_MES getFatMesElem (ELEM elem);

/*-----------------------------------------------------------------------*/


/** @brief Função que retorna a soma acumulada dos elementos de uma matriz (floats)
 *
 *  @param matriz A matriz de floats.
 *  @return float soma acumulada.
 */

float sumatorioMatriz(float **matriz);

/*-----------------------------------------------------------------------*/


/** @brief Função que gera uma tabela 12x3 com a quantidade comprada, por mes e 
 *         por filial, de um cliente.
 *
 *  @param filial AVL filial.
 *  @param nProd matriz de quantidade comprada do seu registo da Filial.
 *  @param flag indica a filial para as funções de soma.
 *  @return table de inteiros.
 */

int** tabelaComprasFilial (AVL filial, char* cliente, int** nProd, int flag);

/*-----------------------------------------------------------------------*/


/** @brief Função que gera a lista de produtos comprados por um cliente
 *         e a qt comprada pelo mesmo.
 *
 *  @param filial AVL filial.
 *  @param produtos lista de produtos para guardar (acumula o produto no fim da lista).
 *  @param cliente cliente de procura.
 *  @return Lista após insercao.
 */

LString top3Compras_do_cliente (AVL filial, char* cliente, LString produtos);

/*-----------------------------------------------------------------------*/


/** @brief Função que insere um elemento numa lista de produtos comprados
 *
 *  @param elem lista de produtos de procura.
 *  @param l Lista de produtos para inserir.
 *  @return Lista após insercao.
 */

LString insereNaListDeProdutosComprados (ELEM elem, LString l);

/*-----------------------------------------------------------------------*/


/** @brief Função que retorna a AVL de um array de avl de filial
 *
 *  @param f array de avl filial.
 *  @param fi filial de procura.
 *  @return AVL filial.
 */

AVL getAVLfilial (FILIAL f, int fi);

/*-----------------------------------------------------------------------*/


/** @brief Função que inicializa a struct filial NAS TRES FILIAIS do array
 *
 *  @param nova Array de filiais (inicialmente NULL).
 *  @param clientes AVL de clientes.
 *  @return vendas AVL de vendas.
 */

FILIAL initFilial (FILIAL nova, AVL clientes, AVL vendas);

/*-----------------------------------------------------------------------*/


/** @brief Função que inicializa os arrays de faturacao e vendas a zero.
 *
 *  @param f array de floats (faturacao do mes).
 *  @param v array de ints (vendas do mes).
 *  @return void.
 */

void initFaturaFilial (FAT_MES f, VENDAS v);

/*-----------------------------------------------------------------------*/


/** @brief Função que atribui os apontadores f e v as respetivas posicoes na lista elem.
 *
 *  @param elem Lista de produtos e faturacao/quantidade vendida.
 *  @param f array de floats (faturacao do mes).
 *  @param v array de ints (vendas do mes).
 *  @return void.
 */

void initMatrizFilial(ELEM elem, FAT_MES f, VENDAS v);

/*-----------------------------------------------------------------------*/


/** @brief Função que adiciona um cliente a uma struct gestao filial.
 *
 *  @param c novo cliente.
 *  @param posicao da avl filial para adicionar.
 *  @return void.
 */

void setClienteFilial (char *c, GESTAO_FILIAL g);

/*-----------------------------------------------------------------------*/


/** @brief Função que atribui o apontador de uma lista de produtos a uma posicao de uma avl filial.
 *
 *  @param filial Avl (mais propriamente representa a posicao do elemento).
 *  @return void.
 */

void setList(AVL filial, ELEM l);

/*-----------------------------------------------------------------------*/


/** @brief Função que atribui a uma posicao de uma matriz de faturacao,
 *         de uma lista elemen um novo valor.
 *
 *  @param elem celula para inserir.
 *  @param l linha.
 *  @param c coluna.
 *  @param val valor a inserir.
 *  @return void.
 */

void setFatFilial (ELEM elem, int l, int c, double val);

/*-----------------------------------------------------------------------*/


/** @brief Função que atribui a uma posicao de uma matriz de vendas,
 *         de uma lista elemen um novo valor.
 *
 *  @param elem celula para inserir.
 *  @param l linha.
 *  @param c coluna.
 *  @param quant quantidade a inserir (inteiro).
 *  @return void.
 */

void setVendasFilial (ELEM elem, int l, int c, int quant);

/*-----------------------------------------------------------------------*/


/** @brief Função que retorna o cliente de uma gestao filial
 *
 *  @param filial struct gestao de filial.
 *  @return o cliente.
 */

char* getClienteFilial(GESTAO_FILIAL filial);

/*-----------------------------------------------------------------------*/


/** @brief Função que retorna a lista de produtos de uma struct gestao filial
 *
 *  @param g struct gestao de filial.
 *  @return a lista dessa struct.
 */

ELEM getList(GESTAO_FILIAL g);

/*-----------------------------------------------------------------------*/


/** @brief Função que faz print a uma AVL filial (para debug)
 *
 *  @param filial AVL filial.
 *  @return void.
 */

void printFilial (AVL filial);

/*-----------------------------------------------------------------------*/


/** @brief Função que imprime uma lista de produtos comprados por um cliente.
 *
 *  @param filial AVL filial.
 *  @return void.
 */

void printElem(ELEM elemenos);

/*-----------------------------------------------------------------------*/


/** @brief Função que imprime a matriz, mediante a flag opcao, de vendas ou faturacao.
 *
 *  @param f matriz faturacao.
 *  @param v matriz vendas
 *  @param opcao 0 -> faturacao, opcao 1 -> vendas
 *  @return void.
 */

void printMATRIXFilial (FAT_MES f, VENDAS v, int opcao);

/*-----------------------------------------------------------------------*/


/** @brief Função que soma duas matrizes guardando o resultado no nProd.
 *
 *  @param nProd matriz onde é guardada o resultado.
 *  @param atual matriz para somar
 *  @param flag que indica a filial
 *  @return void.
 */

void somaMatrizes(int **nProd, int **atual, int flag);

/*-----------------------------------------------------------------------*/


/** @brief Função que acumulas as somas de uma lista de produtos.
 *
 *  @param nProd matriz onde é guardada o resultado.
 *  @param elem lista de produtos
 *  @param flag que indica a filial
 *  @return void.
 */

void somaVendas(int **nProd, ELEM elem, int flag);

/*-----------------------------------------------------------------------*/


/** @brief Função que retorna a matriz de vendas de uma lista de produtos comprados por um cliente.
 *
 *  @param nProd matriz onde é guardada o resultado.
 *  @param atual matriz para somar
 *  @param flag que indica a filial
 *  @return void.
 */

VENDAS getNumVendasElem (ELEM elem);

/*-----------------------------------------------------------------------*/


/** @brief Função que procura um elemento numa filial colocando a
           a posição da filial numa matriz de flags filial[].
 *
 *  @param vendas AVL de vendas para procurar um cliente.
 *  @param filial array de flags na qual as posicoes da filial estao a 1 se o cliente comprou nessa filial
 *  @param cliente para procurar
 *  @return void.
 */

void procuraNaFilial (AVL vendas, int filial[], char* cliente);

/*-----------------------------------------------------------------------*/


/** @brief Função que verifica se um elemento existe numa AVL filial.
 *
 *  @param a AVL de procura.
 *  @param elemento de produra
 *  @return 1 caso exista.
 */

int exist_elementFilial (AVL a, char *element);

/*-----------------------------------------------------------------------*/


/** @brief Função que retorna um produto de uma lista.
 *
 *  @param filial lista de produtos.
 *  @return O produto.
 */

char* getProdutoFilial(ELEM filial);

/*-----------------------------------------------------------------------*/


/** @brief Função que retorna a soma acumulada de uma matriz de ints.
 *
 *  @param matriz matriz de inteiros.
 *  @return A soma.
 */

int sumatorioMatrizInt(int **matriz);

/*-----------------------------------------------------------------------*/


/** @brief Função auxiliar da query11 que adiciona as quantidades compradas 
 *         de um produto numa hashtable.
 *
 *  @param l lista de produtos de procura.
 *  @param h hashtable
 *  @param flag quantidade para adicionar
 *  @return void.
 */

void updateQuantidadesProduto(ELEM l, HEAD_TABLE h, int flag);

/*-----------------------------------------------------------------------*/


/** @brief Função que verifica se um produto existe numa lista
 *
 *  @param l lista de produtos de procura.
 *  @param elem elemento produto de procura
 *  @return 1 caso exista.
 */

int existeNaLista (char* elem, ELEM l);

/*-----------------------------------------------------------------------*/

/** @brief Função que gera a avl de produtos comprados de um cliente
 *
 *  @param filial Avl filial.
 *  @param prodMaisComprad AVL de produtos comprados
 *  @param cliente cliente de procura.
 *  @param mes mes de procura
 *  @return void.
 */

void cria_avl_produtos_Comprados(AVL filial, AVL* prodMaisComprad, char* cliente, int mes);

/*-----------------------------------------------------------------------*/

#endif
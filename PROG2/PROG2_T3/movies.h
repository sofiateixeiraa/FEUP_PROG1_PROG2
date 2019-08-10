/*****************************************************************/
/*         Trabalho pratico 3 | PROG2 | MIEEC | 2018/19        */
/*****************************************************************/


#ifndef MOVIES_H
#define MOVIES_H

#include "vetor.h"



/* tabela de dispersao de strings baseada em encadeamento */


/** Conteudo individual da tabela de dispersao (colecaoClientes):
 * cada cliente tem um username e um vetor dos filmesId vistos
 */
typedef struct
{
	char* username;
	vetor* vistos;
} cliente;

/** Elemento da tabela de dispersao (colecaoClientes):
 * 	clien é um apontador para estrutura cliente com os dados do cliente guardado
 * 	proximo é um apontador para o próximo cliente (implementação baseada em lista ligada)
 */
typedef struct elem
{
	cliente* clien;
	struct elem* proximo;
} elementoCliente;

/**
 * A estrutura colecaoClientes serve para armazenar dados relativos a tabela de dispersao que a implementa
 */
typedef struct
{
	elementoCliente **elementos;	/* vetor de elementos */
	int tamanho;			/* tamanho do vetor de elementos */
} colecaoClientes;

/**
 * A estrutura filme serve para armazenar os dados relativos a um filme:
 * Nota: o filmId é um numero a começar em 1 e sequencial.
*/
typedef struct 
{
	char* titulo;
	char* categoria;
	unsigned int filmId;
	float rating;
} filme;
/** Estrutura colecaoFilmes deverá ser completada de forma a ser possivel guardar os filmes em memoria
 * */
typedef struct elem1
{
	filme *movie;
	struct elem1* proximo;
}elementosFilme;
typedef struct 
{
	elementosFilme **elementos;
	int tamanho;
} colecaoFilmes;


/**
 * Cria uma colecaoClientes (tabela de dispersao)
 * parametros: tamanho da tabela de dispersao
 * retorno: uma tabela de dispersao vazia que representa a colecaoClientes
 */
colecaoClientes* colecaoClientesNova(int tamanho);

/**
 * Apaga uma colecaoClientes (tabela de dispersao)
 * parametros: apontador para colecaoClientes a apagar
 */
void colecaoClientesApaga(colecaoClientes *td);

/**
 * Determina o numero de clientes guardados numa colecaoClientes (tabela de dispersao)
 * parametros: apontador para colecaoClientes
 * retorno: -1 se tabela nao existe, numero de clientes em caso de sucesso
 */
int colecaoNumClientes(colecaoClientes *td);

/**
 * Verifica a existencia de um cliente da colecaoClientes (tabela de dispersao)
 * parametros: apontador para colecaoClientes, username do cliente a verificar
 * retorno: -1 se erro, 0 se o cliente nao consta na tabela, 1 se consta
 */
int clienteExiste(colecaoClientes *td, const char *username);

/**
 * Adiciona um cliente, um filme a lista de visualizacoes de um cliente, ou ambos
 * parametros: apontador para colecaoClientes, username do cliente, identificador unico do filme
 * retorno: -1 em caso de erro, 0 se a entrada ja existe (cliente existe e ja viu o filme
 * 			correspondente a filmId), 1 caso tenha sido feita a adicao
 * NOTA 1: se o cliente ja existir, a filmId devera ser inserida no vetor com as filmId vistas
 * 		pelo utilizador
 * NOTA 2: se o cliente nao existir, deverá ser inserido um cliente novo na colecaoClientes
 * 		(tabela de dispersao) e o seu vetor de vistos devera conter a filmId que esta funcao
 * 		recebe como argumento
 * NOTA 3: para insercao de um cliente sem visualizacoes, filmId=0
 */
int clienteAdiciona(colecaoClientes *td, const char *username, unsigned int filmId);

/**
 * Calcula hash de um username para insercao na colecaoClientes (tabela de dispersao)
 * parametros: username do cliente, tamanho da tabela
 * retorno: valor de hash
 */
unsigned long hash_cliente(const char* username, int tamanho);


/**
 * Imprime o estado actual da tabela para o ecra
 * parametros: colecaoClientes (tabela de dispersao) a ser mostrada
 */
void mostraTabela(colecaoClientes *td);


/**
 * Coloca na estrura colecaoFilmes (a escolher pelo grupo) a informacao contida no ficheiro
 * de texto dos filmes
 * parametros: nomef nome do ficheiro com os dados
 * retorno: apontador para a estrutura colecaoFilmes criada, NULL se a estrutura nao for criada
 * 			ou se o ficheiro nao for aberto correctamente
 * NOTA: esta funcao devera fazer o parse dos dados lidos do ficheiro e chamar para cada linha
 * 		do mesmo a funcao "inserirNovoFilme"
 */
colecaoFilmes* filmesCarrega(const char *nomeFicheiro);

/**
 * Insere um novo filme na estrura colecaoFilmes (a escolher pelo grupo)
 * parametro: apontador para a estrutura colecaoFilmes onde inserir, titulo do filme, categoria do 
 * 			filme, identificador unico do filme, rating do filme
 * retorno: 1 se teve sucesso, 0 se já existe o filme na estrutura e -1 se ocorreu algum erro
 */
int inserirNovoFilme(colecaoFilmes* colecFilmes, char* titulo, char* categoria, int filmId, float rating);


/**
 * Remove um  filme da estrura colecaoFilmes (a escolher pelo grupo) e da estrutura colecaoClientes
 * parametro: apontador para a estrutura colecaoFilmes, apontador para a estrutura colecaoClientes e identificador unico do filme
 * retorno: 1 se teve sucesso, 0 nao existe o filme na estrutura e -1 se ocorreu algum erro
 *  NOTA 1: Não se esqueça que tem que remover o filme dos vistos dos clientes
 */
int removerFilme(colecaoFilmes* colecFilmes, colecaoClientes *td, int filmId);

/**
 * Apaga uma colecaoFilmes (estrutra implementada pelos alunos)
 * parametros: apontador para colecaoFilmes a apagar e para a tabela de Clioentes
 */

void colecaoFilmesApaga(colecaoFilmes* colecFilmes, colecaoClientes *td);

/**
 * Sugere nFilmes para um determinado cliente 
 * parametro: username do cliente que faz o pedido, numero de sugestões, limite minimo do rating para os filmes a sugerir
 * retorno: vetor com os identificadores unicos dos filmes sugeridos para o utilizador, NULL em caso de erro
 * NOTA 1: Se nao foram encontrados nFilmes com rating>=limiar, o vetor devera apenas conter os filmId que estao acima do
 * 		limiar
 * NOTA 2: As sugestoes apresentadas deverao apenas conter filmId nao vistos pelo utilizador
 * NOTA 3: As sugestoes apresentadas deverao ser dadas em dupla ordem decrescente. Comecar pela categoria mais vista do 
 * 		utilizador e so quando as sugestoes dessa categoria atingirem o limiar, passar para a proxima categoria mais
 * 		vista do utilizador. Se não houver mais nenhum filme para sugerir, as restnane posições do vetor têm que estar preenchida com 0
 * NOTA 4: Se houver categorias empatadas vistas pelos clientes, ou seja, têm o mesmo numero de filmes visto pelo cliente 
 * 			o proximo critério de desempate é o que tive a média de rating maior dos filmes vistos. ( É garantido que não existe 
 *         empate neste critério)
 * Nota 5: Quando dois ou mais filmes tiverem o mesmo rating é escolhido o que tive o filmId maior que significa que é o mais recente
 */
vetor* sugestoes(colecaoFilmes* colecFilmes, colecaoClientes *td,char* username, int nFilmes, float limiar);

#endif

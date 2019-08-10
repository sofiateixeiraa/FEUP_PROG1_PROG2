/*****************************************************************/
/*           Movies | PROG2 | MIEEC | 2018/19                */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "movies.h"




//Declaracao funcoes auxiliares//



//////   Implementacao Tabela de Dispersão - Clientes  ///////
colecaoClientes* colecaoClientesNova(int tamanho)
{
    /* aloca memoria para a estrutura tabela_dispersao */

    colecaoClientes *t = (colecaoClientes*) malloc(sizeof (colecaoClientes));
    if (t == NULL)
        return NULL;

    /* aloca memoria para os elementos */
    t->elementos = (elementoCliente **) calloc(tamanho, sizeof (elementoCliente*));
    if (t->elementos == NULL) {
        free(t);
        return NULL;
    }

    t->tamanho = tamanho;

    return t;
}

void colecaoClientesApaga(colecaoClientes *td)
{
    int i;
    elementoCliente *elem, *aux;

    if (td == NULL) return ;

    /* para cada entrada na tabela */
    for (i = 0; i < td->tamanho; i++)
    {
        /* e enquanto existirem elementos nessa entrada */
        elem = td->elementos[i];
        while (elem != NULL)
        {
            /* liberta cada elemento */
            aux = elem->proximo;
            vetor_apaga(elem->clien->vistos);
            free(elem->clien->username);
            elem->clien->username=NULL;
            free(elem->clien);
            free(elem);
            elem = aux;
        }
    }

    /* liberta vector e estrutura */
    free(td->elementos);
    free(td);
}

int clienteAdiciona(colecaoClientes *td, const char *username, unsigned int filmId)
{
    int i;
    int indice;
    elementoCliente *existe1;
    indice=hash_cliente(username, td->tamanho);
    existe1=td->elementos[indice];
    while(existe1!=NULL && strcmp(existe1->clien->username, username)!=0){
        existe1=existe1->proximo;
    }
    if(td==NULL){
        return -1;
    }
    if(existe1==NULL){
        existe1 = (elementoCliente*) malloc(sizeof(elementoCliente));
        existe1->clien=(cliente*)malloc(sizeof(cliente));
        existe1->clien->vistos=vetor_novo();
        existe1->clien->username=(char*)malloc((strlen(username)+1)*sizeof(char));
        strcpy(existe1->clien->username, username);
        vetor_insere(existe1->clien->vistos, filmId, -1);
        if(vetor_insere(existe1->clien->vistos, filmId, -1)==-1){
            return -1;
        }
        existe1->proximo=td->elementos[indice];
        td->elementos[indice]=existe1;
        return 1;
    }
    else{
        for(i=0;i<existe1->clien->vistos->tamanho;i++){
            if(existe1->clien->vistos->elementos[i]==filmId){
                return 0;
            }
            if(existe1->clien->vistos->tamanho==existe1->clien->vistos->capacidade){
                return -1;
            }
            if(vetor_insere(existe1->clien->vistos, filmId, -1)==-1){
                return -1;
            }
            else{
                return 1;
            }
        }
    }
   return -1;
}

int colecaoNumClientes(colecaoClientes *td)
{
	if(td == NULL) return -1; 

      int i, count = 0;
    elementoCliente *elem;
    /* percorre todos os elementos da tabela */
    for (i = 0; i < td->tamanho; i++)
    {
        elem = td->elementos[i];
        while(elem != NULL)
        {
            elem = elem->proximo;
            count++;
            printf("...");
        }
    }
    return count;
}

int clienteExiste(colecaoClientes *td, const char *username)
{
    int i;
    cliente* existe;
    if(td==NULL){
        return -1;
    }
    for(i=0;i<td->tamanho;i++){
        if(td->elementos[i]==NULL) continue;
        if(strcmp(td->elementos[i]->clien->username,username)==0){
            existe=td->elementos[i]->clien;
            break;
        }
    }
    if(td->elementos==NULL){
        return 0;
    }
	return 1;

}

unsigned long hash_cliente(const char* username, int tamanho)
{
    int c, t = strlen(username);
    unsigned long hash = 7;

    for(c = 0; c < t; c++)
    {
        hash += (int) username[c]*powf(2,c);
    }

    return hash % tamanho;
}

/*================================================================================*/
void mostraTabela(colecaoClientes *td)
{
    int i;
    elementoCliente * elem;


    printf("TABELA DE CLIENTES (%d Clientes)\n", colecaoNumClientes(td));
    for (i = 0; i < td->tamanho; i++)
    {
        if (td->elementos[i])
        {
            printf("\t[%2d]", i);
            elem = td->elementos[i];
            while (elem)
            {
                printf(" : [\"%s\" Filmes: ", elem->clien->username);
                if (elem->clien->vistos->tamanho>0)
                {

                    for (int j=0; j<elem->clien->vistos->tamanho; j++)
                    {
                        printf(" (%d)", elem->clien->vistos->elementos[j]);
                    }

                }
                printf("]");
                elem = elem->proximo;
            }
            printf("\n");
        }
    }
    printf("\n");
}



///////////////////////////////////////////////////



/* inserir um Novo Filme*/
int inserirNovoFilme(colecaoFilmes* colecFilmes, char* titulo, char* categoria, int filmId, float rating)
{
    if(colecFilmes == NULL) return -1;

    filme *aux;
    elementosFilme *elem;

    int tamanho = colecFilmes->tamanho;

    aux = (filme *) malloc(sizeof(filme));
    elem = (elementosFilme *) calloc(tamanho, sizeof(elementosFilme));
    
    if(elem == NULL || aux == NULL){
        free(aux);
        free(elem);
        return -1;
    } 
    elem->movie = aux;
    elem->movie->titulo = (char *) malloc(sizeof(char)*strlen(titulo)+1);
    elem->movie->categoria = (char *) malloc(sizeof(char)*strlen(categoria)+1); 
    strcpy(elem->movie->titulo,titulo);
    strcpy(elem->movie->categoria,categoria);
    elem->movie->filmId = filmId;
    elem->movie->rating = rating;
        
    return 1;
}

colecaoFilmes* filmesCarrega(const char *nomeFicheiro)
{
    char palavra[200];
    char *titulo;
    char *categoria;
    unsigned int filmId;
    float rating;

    colecaoFilmes *colecFilmes = (colecaoFilmes*) malloc(sizeof(colecaoFilmes));
        if(colecFilmes == NULL) return NULL;

    FILE *f = fopen(nomeFicheiro,"r");
        if(f == NULL) return NULL;

    while(fgets(palavra, 200, f) != NULL){
        titulo = strtok(palavra, "|");
        categoria = strtok(NULL, "|");
        filmId = atoi(strtok(NULL, "|"));
        rating = atof(strtok(NULL, "|"));
        inserirNovoFilme(colecFilmes, titulo, categoria, filmId, rating);
    }
    fclose(f);
    return colecFilmes;
}

unsigned long hash_filme(int filmId, int tamanho){

    return filmId * 2654435761 % tamanho;

}

// Remover um filme///
int removerFilme(colecaoFilmes* colecFilmes, colecaoClientes *td, int filmId)
{
  if(td == NULL || colecFilmes == NULL ) return -1;  

        for(int i=0; i<td->tamanho; i++)
        {
            elementoCliente *aux = td->elementos[i];
                while(aux!=NULL)
                {
                    for(int j = 0; j < aux->clien->vistos->tamanho; j++)
                    {
                        if(aux->clien->vistos->elementos[j] == filmId)
                        {
                            vetor_remove(aux->clien->vistos, j);
                            break;
                        }
                    }                   
                    aux = aux->proximo;
                }
        }
        elementosFilme *aux1 = colecFilmes->elementos;
        while(aux1 != NULL)
        {
            if(aux1->movie->filmId == filmId)
            {
                
                free(aux1->movie->categoria);
                free(aux1->movie->titulo);
                free(aux1->movie);   
            }
            aux1 = aux1->proximo;
            return 1;
        }
    return 1;
}

// Remover a estrutura colecaoFilmes
void colecaoFilmesApaga(colecaoFilmes* colecFilmes, colecaoClientes *td)
{
    if(colecFilmes == NULL || td == NULL) return;
    elementoCliente* elem1;
    for(int i=0;i<td->tamanho;i++){
        elem1=td->elementos[i];
        while(elem1!=NULL){
            vetor_apaga(elem1->clien->vistos);
            elem1->clien->vistos=vetor_novo();
            elem1=elem1->proximo;
        }
    }
}
//Sugestões //////////////////////////////

vetor* sugestoes(colecaoFilmes* colecFilmes, colecaoClientes *td,char* username, int nFilmes, float limiar)
{
	
   return NULL;
}



///////////////////////////////////////

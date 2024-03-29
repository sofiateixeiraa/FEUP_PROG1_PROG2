/*****************************************************************/
/*   Arvore AVL | PROG2 | MIEEC | 2013/14                        */      
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

/* declaracao das funcoes utilitarias */
no_avl* avl_pesquisa_impl(no_avl *no, const char *str);
no_avl* avl_insere_impl(no_avl *no, const char *str);
no_avl* avl_remove_impl(no_avl *no, const char *str);
no_avl* avl_no_valormin(no_avl* no);
no_avl* avl_no_valormax(no_avl* no);
void avl_preordem_impl(no_avl *no);

arvore_avl* avl_nova()
{
    arvore_avl *avl = (arvore_avl*) malloc(sizeof(arvore_avl));
    if(avl == NULL)
        return NULL;

    avl->raiz = NULL; /* arvore vazia */

    return avl;
}

void avl_apaga(arvore_avl* avl)
{
    while(avl->raiz != NULL)
    {
        avl->raiz = avl_remove_impl(avl->raiz, avl->raiz->str);
    }

    free(avl);
}

no_avl* avl_pesquisa(arvore_avl* avl, const char *str)
{
    if(avl == NULL || str == NULL)
        return NULL;

    return avl_pesquisa_impl(avl->raiz, str);
}

int avl_insere(arvore_avl* avl, const char *str)
{
    if(avl == NULL || str == NULL)
        return -1;

    avl->raiz = avl_insere_impl(avl->raiz, str);

    return 0;
}

int avl_remove(arvore_avl* avl, const char *str)
{
    if(avl == NULL || str == NULL)
        return -1;

    avl->raiz = avl_remove_impl(avl->raiz, str);

    return 0;   
}

const char *avl_min(arvore_avl* avl)
{
    if(avl == NULL)
        return NULL;

    return avl_no_valormin(avl->raiz)->str;
}

const char *avl_max(arvore_avl* avl)
{
    if(avl == NULL)
        return NULL;

    return avl_no_valormax(avl->raiz)->str;
}

void avl_imprime(arvore_avl* avl)
{
    if(avl == NULL)
        return;

    avl_preordem_impl(avl->raiz);

    printf("\n");
}


/*************************************************/
/* funcoes utilitarias                           */
/*************************************************/

/* altura da arvore */
int altura(no_avl *N)
{
    if (N == NULL)
        return 0;
    return N->altura;
}
 
/* maximo entre dois inteiros */
int max(int a, int b)
{
    return (a > b)? a : b;
}
 
/*  cria um novo no dada uma string */
no_avl* avl_novo_no(const char *str)
{
    no_avl *no = (no_avl*) malloc(sizeof(no_avl));
    no->str = (char*) malloc(sizeof(char)*(strlen(str)+1));
    strcpy(no->str, str);
    no->esquerda = NULL;
    no->direita  = NULL;
    no->altura = 1;  /* novo no e' inicialmente uma folha */
    return no;
}
 
/* roda sub-arvore 'a direita tendo raiz em y */
no_avl* roda_direita(no_avl *y)
{
    no_avl *x = y->esquerda;
    no_avl *T2 = x->direita;
 
    /* efetua rotacao */
    x->direita = y;
    y->esquerda = T2;
 
    /* atualiza alturas */
    y->altura = max(altura(y->esquerda), altura(y->direita))+1;
    x->altura = max(altura(x->esquerda), altura(x->direita))+1;
 
    /* retorna novo no' */
    return x;
}
 
/* roda sub-arvore 'a esquerda tendo raiz em x */
no_avl* roda_esquerda(no_avl *x)
{
    no_avl *y = x->direita;
    no_avl *T2 = y->esquerda;
 
    /* efetua rotacao */
    y->esquerda = x;
    x->direita = T2;
 
    /*  atualiza alturas */
    x->altura = max(altura(x->esquerda), altura(x->direita))+1;
    y->altura = max(altura(y->esquerda), altura(y->direita))+1;
 
    /* retorna novo no' */
    return y;
}
 
/* calcula fator de balanceamento */
int calc_balanceamento(no_avl *N)
{
    if (N == NULL)
        return 0;
    return altura(N->esquerda) - altura(N->direita);
}

no_avl* avl_pesquisa_impl(no_avl* no, const char *str)
{
    if(no == NULL)
        return NULL;

    if(strcmp(str, no->str) < 0)
        return avl_pesquisa_impl(no->esquerda, str);
    
    else if(strcmp(str, no->str) > 0)
        return avl_pesquisa_impl(no->direita, str);
    
    else
        return no;
}
 
no_avl* avl_insere_impl(no_avl *no, const char *str)
{
    /* 1.  efetua insercao normal de arvore binaria de pesquisa */
    if (no == NULL)
        return avl_novo_no(str);
 
    if (strcmp(str, no->str) < 0)
        no->esquerda  = avl_insere_impl(no->esquerda, str);
    else if(strcmp(str, no->str) > 0)
        no->direita = avl_insere_impl(no->direita, str);
    else
        return no; /* se forem iguais, nao faz nada */
 
    /* 2. atualiza a altura deste no ancestral */
    no->altura = max(altura(no->esquerda), altura(no->direita)) + 1;
 
    /* 3. calcula o fator de balanceamento deste no ancestral para verificar
       se deixou de estar balanceado */
    int balance = calc_balanceamento(no);
 
    /* se o no deixau de estar balanceado, existem 4 casos */
 
    /* esquerda-esquerda */
    if (balance > 1 && strcmp(str, no->esquerda->str) < 0)
        return roda_direita(no);
 
    /* direita-direita */
    if (balance < -1 && strcmp(str, no->direita->str) > 0)
        return roda_esquerda(no);
 
    /* esquerda-direita */
    if (balance > 1 && strcmp(str, no->esquerda->str) > 0)
    {
        no->esquerda =  roda_esquerda(no->esquerda);
        return roda_direita(no);
    }
 
    /* direita-esquerda */
    if (balance < -1 && strcmp(str, no->direita->str) < 0)
    {
        no->direita = roda_direita(no->direita);
        return roda_esquerda(no);
    }
 
    /* retorna o apontador para o no (inalterado) */
    return no;
}
 
/* dada uma arvore binaria de pesquisa, retorna o no' com o valor minimo
   que se pode encontrar nessa arvore */
no_avl* avl_no_valormin(no_avl* no)
{
    no_avl* curr = no;
 
    /* percorre a arvore para encontrar o filho mais 'a esquerda */
    while (curr->esquerda != NULL)
        curr = curr->esquerda;
 
    return curr;
}

/* dada uma arvore binaria de pesquisa, retorna o no' com o valor maximo
   que se pode encontrar nessa arvore */
no_avl* avl_no_valormax(no_avl* no)
{
    no_avl* curr = no;
 
    /* percorre a arvore para encontrar o filho mais 'a direita */
    while (curr->direita != NULL)
        curr = curr->direita;
 
    return curr;
}
 
no_avl* avl_remove_impl(no_avl* no, const char *str)
{
    /* 1. efetua remocao normal de arvore binaria de pesquisa */
 
    if (no == NULL)
        return no;
 
    /* se a str a ser removida � menor do que a str da raiz,
       entao esta' na sub-arvore esquerda */
    if ( strcmp(str, no->str) < 0 ) 
        no->esquerda = avl_remove_impl(no->esquerda, str);
 
    /* se a str a ser removida � maior do que a str da raiz,
       entao esta' na sub-arvore direita */
    else if( strcmp(str, no->str) > 0 )
        no->direita = avl_remove_impl(no->direita, str);
 
    /* se a str a ser removida � igual a str da raiz,
       entao e' este no a remover */
    else
    {
        /* no' com apenas um filho ou sem filhos */
        if( (no->esquerda == NULL) || (no->direita == NULL) )
        {
            no_avl *temp = no->esquerda ? no->esquerda : no->direita;
 
            /* caso sem filhos */
            if(temp == NULL)
            {
                temp = no;
                no = NULL;
            }
            else /* caso de um filho */
            {
                /* copia os conteudos do filho que n�o est� vazio */
                no->str = realloc(no->str, (strlen(temp->str)+1)*sizeof(char));
                strcpy(no->str, temp->str);
                no->esquerda = temp->esquerda;
                no->direita = temp->direita;
                no->altura = temp->altura;
            }
 
            free(temp->str);
            free(temp);
        }
        else
        {
            /* no' com dois filhos: obtem sucessor em-ordem (menor da arvore direita) */
            no_avl* temp = avl_no_valormin(no->direita);
 
            /* copia o valor em.ordem do sucessor para este no' */
            no->str = realloc(no->str, (strlen(temp->str)+1)*sizeof(char));
            strcpy(no->str, temp->str);
 
            /* apaga o sucessor em-ordem */
            no->direita = avl_remove_impl(no->direita, temp->str);
        }
    }
 
    /* se a arvore tinha apenas um no, ent�o retorna */
    if (no == NULL)
      return no;
 
    /* 2. atualiza a altura do no corrente */
    no->altura = max(altura(no->esquerda), altura(no->direita)) + 1;
 
    /* 3. calcula o fator de balanceamento deste no ancestral para verificar
       se deixou de estar balanceado */
    int balance = calc_balanceamento(no);
 
    /* se o no deixau de estar balanceado, existem 4 casos */

    /* esquerda-esquerda */
    if (balance > 1 && calc_balanceamento(no->esquerda) >= 0)
        return roda_direita(no);
 
    /* esquerda-direita */
    if (balance > 1 && calc_balanceamento(no->esquerda) < 0)
    {
        no->esquerda =  roda_esquerda(no->esquerda);
        return roda_direita(no);
    }
 
    /* direita-direita */
    if (balance < -1 && calc_balanceamento(no->direita) <= 0)
        return roda_esquerda(no);
 
    /* direita-esquerda */
    if (balance < -1 && calc_balanceamento(no->direita) > 0)
    {
        no->direita = roda_direita(no->direita);
        return roda_esquerda(no);
    }
 
    return no;
}

void avl_preordem_impl(no_avl* no)
{
    if (no == NULL) return;
    printf("%s ", no->str);
    avl_preordem_impl(no->esquerda);
    avl_preordem_impl(no->direita);
}
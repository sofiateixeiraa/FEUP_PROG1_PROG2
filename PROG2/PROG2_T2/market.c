/*****************************************************************/
/*           Market | PROG2 | MIEEC | 2018/19                */
/*****************************************************************/

/*
Ana Sofia Teixeira
Ana Rita Oliveira
2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "market.h"

#define RAIZ 		(1)
#define PAI(x) 		(x/2)
#define FILHO_ESQ(x) 	(x*2)
#define FILHO_DIR(x) 	(x*2+1)

//Declaracao funcoes auxiliares//
int maior_que(elemento_t * e1, elemento_t * e2);
int avl_altura(no_avl *no);
int calc_balanceamento(no_avl *N);
no_avl* roda_direita(no_avl *y);
no_avl* roda_esquerda(no_avl *x);
no_avl* avl_no_valormin(no_avl* no);
no_avl* avl_no_valormax(no_avl* no);
int max(int a, int b);
int min(int a, int b);


//////   Implementacao Elemento e Calculo Metrica (5.1)  ///////

elemento_t* elemento_novo(const char* nameItem, const char* expDate, int qty, int sellRate)
{
elemento_t *elemento = malloc(sizeof(elemento_t));
    strcpy(elemento->nameItem,nameItem);
    strcpy(elemento->expirationDate,expDate);
    elemento->qty = qty;
    elemento->sellRate = sellRate;
    
    elemento->priorityVal = calcMetrica(elemento);
    
    return elemento;
}

void elemento_apaga(elemento_t* elem)
{   
    if(elem) free(elem);
    elem = NULL;
}

//   Implementacao metrica prioridade  //

float calcMetrica(elemento_t* elem)
{
 struct tm expDate, curDate;
    char aux[sizeof(elem->expirationDate)], *aux1;
    int time1, time2;
    strcpy(aux, elem->expirationDate);
    aux1 = strtok(aux, "-");
    expDate.tm_year = atoi(aux1) - 1900;
    aux1 = strtok(NULL, "-");
    expDate.tm_mon = atoi(aux1) - 1;
    aux1 = strtok(NULL, "-");
    expDate.tm_mday = atoi(aux1);
    expDate.tm_hour = 0;
    expDate.tm_min = 0;
    expDate.tm_sec = 1;
    curDate.tm_isdst = -1;
    time1 = mktime(&expDate);
    strcpy(aux, CURDATE);
    aux1 = strtok(aux, "-");
    curDate.tm_year = atoi(aux1) - 1900;
    aux1 = strtok(NULL, "-");
    curDate.tm_mon = atoi(aux1) - 1;
    aux1= strtok(NULL, "-");
    curDate.tm_mday = atoi(aux1);
    curDate.tm_hour = 0;
    curDate.tm_min = 0;
    curDate.tm_sec = 1;
    curDate.tm_isdst = -1;
    time2 = mktime(&curDate);
    if(time1 == -1 || time2==-1)
    {
        return 0.0;
    }
    elem->priorityVal = 1/(difftime(time1 , time2) + 1000/elem->sellRate);
    return elem->priorityVal;
}


///////////////////////////////////////////////////

/// Implementacao Heaps (5.2) ///

heap* heap_nova(int capacidade)
{
    heap* h;
	h = malloc(sizeof(heap));
	    if(h == NULL) return NULL;

	h->tamanho = 0;
	h->capacidade = capacidade;
	h->elementos = malloc(sizeof(elemento_t*)*(capacidade+1));

        if(h->elementos == NULL)
        {
            free(h);
            return NULL;
        }
        for(int i = 0; i < capacidade+1; i++){
            h->elementos[i] = NULL;
        }
	return h;
}

void heap_apaga(heap *h)
{
	int i;

	for (i = 1; i <= h->tamanho; i++)
	{
		elemento_apaga(h->elementos[i]);
	}

    free(h->elementos);
	free(h);
    return;
}


int heap_insere(heap *h, elemento_t* elem)
{
	elemento_t * aux;
	int i;
	//gilc
	if(!h) return 0;
	/* se heap esta' cheia, nao insere elemento */
	if (h->tamanho >= h->capacidade)
		return 0;

	if (!elem)
		return 0;

	/* coloca elemento no fim da heap */
	h->tamanho++;
	i = h->tamanho;
	h->elementos[i] = elem;

 	/* enquanto elemento for mais prioritario do que o respetivo pai, troca-os */
	while (i != RAIZ && maior_que(h->elementos[i], h->elementos[PAI(i)]))
	{
		aux = h->elementos[PAI(i)];
		h->elementos[PAI(i)] = h->elementos[i];
		h->elementos[i] = aux;
		i = PAI(i);
	}
	return 1;

    //Default
    return 0;
}


elemento_t* heap_remove(heap * h){
    int i=1, p;
    //float max;
    elemento_t* j = h->elementos[RAIZ];
    elemento_t* aux;
         
        if(j == NULL) return NULL;

    h->elementos[RAIZ]= h->elementos[h->tamanho];
    h->elementos[h->tamanho] = NULL;
    h->tamanho -- ;
    while(FILHO_ESQ(i) <= h->tamanho){
        elemento_t* left = h->elementos[FILHO_ESQ(i)];
        elemento_t* right = h->elementos[FILHO_DIR(i)];
        if(maior_que(left,right) || right == NULL){
           // max=left;
            p=FILHO_ESQ(i);
        }
        else{
            //max=right;
            p=FILHO_DIR(i);
        }
        
            aux = h->elementos[p];
            h->elementos[p] = h->elementos[i];
            h->elementos[i] = aux;
            i = p;
        
    }
    return j;
}


void mostraHeap(heap *h)
{
    if(!h)
        return;

    for(int indice =1; indice<=h->tamanho; indice++)
    {
        printf("%s %s %d %d %f\n",h->elementos[indice]->nameItem, h->elementos[indice]->expirationDate,
                        h->elementos[indice]->qty,h->elementos[indice]->sellRate,
                        h->elementos[indice]->priorityVal);
    }
}


//////////////////////////////////////////////

/// Implementacao criacao categoria nova ///

category_t* novaCategoria(heap* itemTree, char* categName)
{
    category_t* retCat = (category_t*)malloc(sizeof(category_t));

    if(retCat == NULL)
    {
        return NULL;
    }

    retCat->itemTree = itemTree;

    retCat->categName = (char*)malloc((strlen(categName)+1)*sizeof(char));

    if(retCat->categName==NULL)
    {
        return NULL;
    }

    strcpy(retCat->categName,categName);

    return retCat;

    //Default
    return NULL;
}

void categoriaApaga(category_t* categ)
{
    heap_apaga(categ->itemTree);
    free(categ->categName);
    categ->categName = NULL;
    free(categ);
    categ = NULL;
}


////////////////////////////////////////////

//////   Implementacao AVLs (5.3)  ///////

arvore_avl* avl_nova()
{
    // Implementacao exercicio 5.4.1
    arvore_avl *avl = (arvore_avl*) malloc(sizeof(arvore_avl));
    if(avl == NULL)
        return NULL;

    avl->raiz = NULL; /* arvore vazia */

    return avl;

    // Default
    return NULL;
}

no_avl* avl_novo_no(category_t* categ)
{
    // Implementacao exercicio 5.4.2
    no_avl *no = (no_avl*) malloc(sizeof(no_avl));

    if(no==NULL)
        return NULL;

    no->categ = categ;
    no->esquerda = NULL;
    no->direita  = NULL;
    no->altura = 0;  /* novo no e' inicialmente uma folha */
    return no;

    // Default
    return NULL;
}

no_avl* avl_insere(no_avl *no, category_t* categ)
{
    if (no == NULL)
        return avl_novo_no(categ);

    if (strcmp(categ->categName, no->categ->categName) < 0)
        no->esquerda  = avl_insere(no->esquerda, categ);
    else if(strcmp(categ->categName, no->categ->categName) > 0)
        no->direita = avl_insere(no->direita, categ);
    else {
        return no;
    }
    no->altura = max(avl_altura(no->esquerda), avl_altura(no->direita)) + 1;
    int balance = calc_balanceamento(no);

    if (balance > 1) {
    	if (calc_balanceamento(no->direita) < 0) {
			no->direita = roda_direita(no->direita);
			return roda_esquerda(no);
    	} else {
    		return roda_esquerda(no);
    	}
    }
    else if (balance < -1) {
    	if (calc_balanceamento(no->esquerda) > 0) {
			no->esquerda = roda_esquerda(no->esquerda);
			return roda_direita(no);
    	} else {
    		return roda_direita(no);
    	}
    }
    return no;
    
    return NULL;
}

no_avl* avl_remove(no_avl *no, const char* categStr)
{
    // Implementacao exercicio 5.4.4

    /* 1. efetua remocao normal de arvore binaria de pesquisa */

    if (no == NULL)
        return no;

    /* se o nome da categoria a ser removida é menor do que a str da raiz,
       entao esta' na sub-arvore esquerda */
    if ( strcmp(categStr, no->categ->categName) < 0 )
        no->esquerda = avl_remove(no->esquerda, categStr);

    /* se a str a ser removida é maior do que a str da raiz,
       entao esta' na sub-arvore direita */
    else if( strcmp(categStr, no->categ->categName) > 0 )
        no->direita = avl_remove(no->direita, categStr);

    /* se a str a ser removida é igual a str da raiz,
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
                /* copia os conteudos do filho que não está vazio */
                no->categ->categName = realloc(no->categ->categName, (strlen(temp->categ->categName)+1)*sizeof(char));
                strcpy(no->categ->categName, temp->categ->categName);
                heap_apaga(no->categ->itemTree);
                no->categ->itemTree = temp->categ->itemTree;
                no->esquerda = temp->esquerda;
                no->direita = temp->direita;
                no->altura = temp->altura;
            }

            free(temp->categ->categName);
            free(temp->categ);
            free(temp);
        }
        else
        {
            /* no' com dois filhos: obtem sucessor em-ordem (menor da arvore direita) */
            no_avl* temp = avl_no_valormin(no->direita);

            /* copia o valor em.ordem do sucessor para este no' */
            no->categ->categName = realloc(no->categ->categName, (strlen(temp->categ->categName)+1)*sizeof(char));
            strcpy(no->categ->categName, temp->categ->categName);
            heap_apaga(no->categ->itemTree);
            no->categ->itemTree = temp->categ->itemTree;

            /* apaga o sucessor em-ordem */
            no->direita = avl_remove(no->direita, temp->categ->categName);
        }
    }

    /* se a arvore tinha apenas um no, então retorna */
    if (no == NULL)
      return no;

    /* 2. atualiza a altura do no corrente */
    no->altura = max(avl_altura(no->esquerda), avl_altura(no->direita)) + 1;

    /* 3. calcula o fator de balanceamento deste no ancestral para verificar
       se deixou de estar balanceado */
    int balance = calc_balanceamento(no);

    /* se o no deixou de estar balanceado, existem 4 casos */

    if (balance > 1) {
        /* Arvore e' right-heavy */
        if (calc_balanceamento(no->direita) < 0) {
            /* Sub-arvore direita é left-heavy */
            /* Rotacao RL */
            no->direita = roda_direita(no->direita);
            return roda_esquerda(no);
        } else {
            /* Rotacao L */
            return roda_esquerda(no);
        }
    }
    else if (balance < -1) {
        /* Arvore e' left-heavy */
        if (calc_balanceamento(no->esquerda) > 0) {
            /* Sub-arvore esquerda é right-heavy */
            /* Rotacao LR */
            no->esquerda = roda_esquerda(no->esquerda);
            return roda_direita(no);
        } else {
            /* Rotacao R */
            return roda_direita(no);
        }
    }
    /* caso esteja balanceada retorna o apontador para o no (inalterado) */
    return no;

    // Default
    return NULL;
}

no_avl* avl_pesquisa(no_avl *no, const char* categStr)
{
    if(no == NULL)
        return NULL;

    if(strcmp(categStr, no->categ->categName) < 0)
        return avl_pesquisa(no->esquerda, categStr);

    else if(strcmp(categStr, no->categ->categName) > 0)
        return avl_pesquisa(no->direita, categStr);

    else
        return no;
    return NULL;
}

void avl_apaga(arvore_avl* avl)
{
	if (!avl) return;
    while(avl->raiz != NULL)
    {
        avl->raiz = avl_remove(avl->raiz, avl->raiz->categ->categName);
    }

    free(avl);
}

///////////////////////////////////////



///   Implementacao adicao artigo (5.4)
int artigo_adiciona(arvore_avl *avl, elemento_t* elem, char *categName, int capCateg)
{
    heap *h_nova;
        h_nova = heap_nova(capCateg);
    no_avl *avl_nova;
        
   if((avl_nova = avl_pesquisa(avl->raiz, categName))==NULL){
        avl->raiz = avl_insere(avl->raiz,novaCategoria(h_nova,categName));
        heap_insere(h_nova,elem);
        return 1;
    }
    else if(avl_nova->categ->itemTree->tamanho == capCateg) return 0;

    heap_insere(avl_nova->categ->itemTree,elem);
    return 1;
}

//////////////////////////////////////////////


///   Implementacao montagem montra (5.5)   ///
elemento_t** criar_montra(arvore_avl* avl, const char* categName, int numPorItem, int totalItems, int* tamanhoArray)
{ 
    int i=1, delete, removepos;
    delete = totalItems;
    
    no_avl* no1 = avl_pesquisa(avl->raiz, categName);
    heap* h = heap_nova(no1->categ->itemTree->capacidade);
    elemento_t** elemt = malloc((no1->categ->itemTree->tamanho+1)*8);
    

    while(i<=no1->categ->itemTree->tamanho){
        delete -= no1->categ->itemTree->elementos[i]->qty;
        i++;
        if(delete <= 0) break;
    }
    if(delete>0){
        free(elemt);
        return NULL;
    }
    i = 0;
    delete=totalItems;
    while(no1->categ->itemTree->tamanho>0){
        removepos = min(delete, numPorItem);
        if(no1->categ->itemTree->elementos[RAIZ]->qty>removepos){
            elemt[i]=elemento_novo(no1->categ->itemTree->elementos[RAIZ]->nameItem, no1->categ->itemTree->elementos[RAIZ]->expirationDate, removepos, no1->categ->itemTree->elementos[RAIZ]->sellRate);
            no1->categ->itemTree->elementos[RAIZ]->qty = removepos;
            heap_insere(h, heap_remove(no1->categ->itemTree));
            delete = removepos;
        }
        else{
            elemt[i]=elemento_novo(no1->categ->itemTree->elementos[RAIZ]->nameItem, no1->categ->itemTree->elementos[RAIZ]->expirationDate, no1->categ->itemTree->elementos[RAIZ]->qty, no1->categ->itemTree->elementos[RAIZ]->sellRate);
            delete = no1->categ->itemTree->elementos[RAIZ]->qty;
            heap_remove(no1->categ->itemTree);
        }
        i++;
        if(delete == 0){
            break;
        }
    }
    while(h->elementos[RAIZ]!= NULL){
        heap_insere(no1->categ->itemTree, heap_remove(h));
    }
    *tamanhoArray=i;
    heap_apaga(h);
    return elemt; 
}

//////////////////////////////////////////////





// Auxiliary functions

int maior_que(elemento_t* e1, elemento_t* e2)
{
	if (e1 == NULL || e2 == NULL)
	{
		return 0;
	}

	return e1->priorityVal > e2->priorityVal;
}

int avl_altura(no_avl *no)
{
    if (no == NULL)
        return -1;
    return no->altura;
}

int calc_balanceamento(no_avl *N)
{
    if (N == NULL)
        return 0;
    return avl_altura(N->direita) - avl_altura(N->esquerda);
}

no_avl* roda_direita(no_avl *y)
{
    no_avl *x = y->esquerda;
    no_avl *T2 = x->direita;

    /* efetua rotacao */
    x->direita = y;
    y->esquerda = T2;

    /* atualiza alturas */
    y->altura = max(avl_altura(y->esquerda), avl_altura(y->direita))+1;
    x->altura = max(avl_altura(x->esquerda), avl_altura(x->direita))+1;

    /* retorna novo no' */
    return x;
}

no_avl* roda_esquerda(no_avl *x)
{
    no_avl *y = x->direita;
    no_avl *T2 = y->esquerda;

    /* efetua rotacao */
    y->esquerda = x;
    x->direita = T2;

    /*  atualiza alturas */
    x->altura = max(avl_altura(x->esquerda), avl_altura(x->direita))+1;
    y->altura = max(avl_altura(y->esquerda), avl_altura(y->direita))+1;

    /* retorna novo no' */
    return y;
}


no_avl* avl_no_valormin(no_avl* no)
{
    no_avl* curr = no;

    /* percorre a arvore para encontrar o filho mais 'a esquerda */
    while (curr->esquerda != NULL)
        curr = curr->esquerda;

    return curr;
}

no_avl* avl_no_valormax(no_avl* no)
{
    no_avl* curr = no;

    /* percorre a arvore para encontrar o filho mais 'a direita */
    while (curr->direita != NULL)
        curr = curr->direita;

    return curr;
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

int min(int a, int b)
{
    return (a < b)? a : b;

}

int enoughItems(heap* h, int numPorItem, int totalItems)
{
    int qtyCounter = 0;
    for (int i=1; i<=(h->tamanho); i++)
    {
        qtyCounter += min(h->elementos[i]->qty,numPorItem);
        if(qtyCounter>=totalItems)
        {
            return 1;
        }
    }
    return 0;
}

void avlNoApaga(no_avl* node)
{

    if(!node)
        return;

    categoriaApaga(node->categ);
    node->esquerda = NULL;
    node->direita = NULL;
    node->altura = 0;
    free(node);
    node = NULL;
}

void avlNoCopia(no_avl* nodeDest, no_avl* nodeSrc)
{

    if(!nodeSrc || !nodeDest)
        return;

    nodeDest->categ->categName = realloc(nodeDest->categ->categName, (strlen(nodeSrc->categ->categName)+1)*sizeof(char));
    strcpy(nodeDest->categ->categName, nodeSrc->categ->categName);
    heap_apaga(nodeDest->categ->itemTree);
    nodeDest->categ->itemTree = heap_nova(nodeSrc->categ->itemTree->capacidade);

    for(int i=RAIZ; i<=(nodeSrc->categ->itemTree->tamanho); i++)
    {
        nodeDest->categ->itemTree->elementos[i] = elemento_novo(nodeSrc->categ->itemTree->elementos[i]->nameItem,
        nodeSrc->categ->itemTree->elementos[i]->expirationDate,nodeSrc->categ->itemTree->elementos[i]->qty,
        nodeSrc->categ->itemTree->elementos[i]->sellRate);
    }
	nodeDest->categ->itemTree->tamanho = nodeSrc->categ->itemTree->tamanho;
    nodeDest->esquerda = nodeSrc->esquerda;
    nodeDest->direita = nodeSrc->direita;
    nodeDest->altura = nodeSrc->altura;

}

void avlNoValorCopia(no_avl* nodeDest, no_avl* nodeSrc)
{

    if(!nodeSrc || !nodeDest)
        return;

    nodeDest->categ->categName = realloc(nodeDest->categ->categName, (strlen(nodeSrc->categ->categName)+1)*sizeof(char));
    strcpy(nodeDest->categ->categName, nodeSrc->categ->categName);
    heap_apaga(nodeDest->categ->itemTree);
    nodeDest->categ->itemTree = heap_nova(nodeSrc->categ->itemTree->capacidade);

    for(int i=RAIZ; i<=(nodeSrc->categ->itemTree->tamanho); i++)
    {
        nodeDest->categ->itemTree->elementos[i] = elemento_novo(nodeSrc->categ->itemTree->elementos[i]->nameItem,
        nodeSrc->categ->itemTree->elementos[i]->expirationDate,nodeSrc->categ->itemTree->elementos[i]->qty,
        nodeSrc->categ->itemTree->elementos[i]->sellRate);
    }
	nodeDest->categ->itemTree->tamanho = nodeSrc->categ->itemTree->tamanho;
}

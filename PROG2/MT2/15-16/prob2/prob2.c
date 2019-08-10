#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vetor.h"
#include "grafo.h"
#include "tabdispersao.h"


/*** problema 2.1 ***/
vetor* td_pesquisa_inversa(tabela_dispersao *td, const char *valor)
{
	if(td==NULL) return NULL;
	vetor* chave = vetor_novo();
	int n=0;
	objeto* elem1 = tabela_elementos(td, &n);
	for(int i=0; i<td->tamanho;i++){
		if(strcmp(valor, elem1[i].valor)==0){
			vetor_insere(chave, elem1[i].chave, -1);
		}
	}
	if(chave == NULL) return NULL;
	return chave;
}

/*** problema 2.2 ***/
grafo * grafo_uniao(grafo *g1, grafo *g2)
{
	if(g1==NULL || g2==NULL) return NULL;
	grafo* g3 = grafo_novo(g1->tamanho, DIGRAFO);
	for(int i=0; i<g1->tamanho;i++){
		lista_no* l1 = g1->adjacencias[i].inicio;
		lista_no* l2 = g2->adjacencias[i].inicio;
		while(l1!=NULL){
		grafo_adiciona(g3, i, l1->vertice);
		l1= l1->proximo;
		}
		while(l2!=NULL){
		grafo_adiciona(g3, i, l2->vertice);
		l2= l2->proximo;
		}
	}
	return g3;
}

/* Aqui comeca o codigo de teste. Nao modificar! */

#define MAX_LINE	100
#define MAX_WORD	50
#define PESQ "Netherlands"

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);

	/* teste problema 2.1 */
	{
		int i;
		char aeroporto[MAX_WORD], pais[MAX_WORD], line[MAX_LINE];
		puts("* Problema 2.1 *");
		tabela_dispersao * td = tabela_nova(300, hash_krm);
		FILE *fp=fopen("aeroportos.txt", "r");
		while(fscanf(fp, "%s\t%s", aeroporto, pais) == 2)
			tabela_insere(td,aeroporto,pais);
		vetor *v=td_pesquisa_inversa(td, PESQ);
		printf("%s airports:\n",PESQ);
		for (i=0; i<vetor_tamanho(v);i++) {
			printf("%d: %s\n",i+1,vetor_elemento(v,i));
		}
		tabela_apaga(td);
	}

	/* teste problema 2.2 */
	{
		puts("\n\n* Problema 2.2 *");
		grafo * g1 = grafo_novo(8, DIGRAFO);
		grafo * g2 = grafo_novo(8, DIGRAFO);
		grafo_adiciona(g1,0,4);
		grafo_adiciona(g1,1,0);
		grafo_adiciona(g1,1,5);
		grafo_adiciona(g1,2,1);
		grafo_adiciona(g1,3,2);
		grafo_adiciona(g1,4,3);
		grafo_adiciona(g1,5,4);
		grafo_adiciona(g1,6,3);
		grafo_adiciona(g1,7,2);
		grafo_adiciona(g1,7,6);
		grafo_adiciona(g2,0,4);
		grafo_adiciona(g2,1,0);
		grafo_adiciona(g2,1,4);
		grafo_adiciona(g2,1,5);
		grafo_adiciona(g2,2,3);
		grafo_adiciona(g2,5,4);
		grafo_adiciona(g2,6,2);
		grafo_adiciona(g2,7,3);
		grafo * g3=grafo_uniao(g1,g2);
		if (g3) grafo_imprime(g3);
		grafo_apaga(g1);
		grafo_apaga(g2);
		grafo_apaga(g3);
	}

	return 0;
}

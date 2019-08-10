#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "heap.h"
#include "fila.h"
#include "vetor.h"

/*** problema 1.1 ***/
int avl_conta_letras(no_avl *no)
{
	if(no==NULL) return 0;
	int contador =0;
	int dis=strlen(no->str);
	for(int i=0;i<dis;i++){
	if(no->str[i] >= 'a' && no->str[i] <= 'z'){
		contador ++;
	}
	}
	contador+=avl_conta_letras(no->esquerda);
	contador+=avl_conta_letras(no->direita);
	return contador;
}

/*** problema 1.2 ***/
int fila_reordena(fila *original, vetor *prioridades)
{
	/* complexidade do algoritmo:
 			heap_insere e heap_remove->O(logn) fila_front, fila_pop, fila_push e vetor_elemento ->O(1)
			Como tanto a funçao heap_insere como a função heap_remove estão em ciclos while que percorrem n elementos,
			a complexidade de cada um dos ciclos é O(nlogn) logo a complexidade total do algoritmo é O(nlogn)
	*/
	if(original==NULL || prioridades == NULL){
		return 0;
	}
	heap* haux = heap_nova(fila_tamanho(original));
	int tamanho = fila_tamanho(original);
	for(int i=0;i<tamanho;i++){
		heap_insere(haux, fila_front(original), atoi(vetor_elemento(prioridades, i)));
		fila_pop(original);
	}
	int tamanho1=haux->tamanho;
	for(int i=0; i<tamanho1;i++){
		fila_push(original, heap_remove(haux));
	}
	return 1;
}

/* Aqui comeca o codigo de teste. Nao modificar! */

#define MAX_STR 500

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	FILE *fp=fopen("paises.txt", "r");
	FILE *fm=fopen("estrelas.txt", "r");
	char str_aux[MAX_STR];

	/* teste problema 1.1 */
	{
		arvore_avl *arv;
		puts("* Problema 1.1 *");
		arv = avl_nova();
		while(fgets(str_aux,MAX_STR,fp) != NULL)
		{
			str_aux[strlen(str_aux)-1] = '\0';			
			avl_insere(arv, str_aux);
		}
		printf("Numero de letras: %d\n", avl_conta_letras(arv->raiz));
		avl_apaga(arv);
	}

	/* teste problema 1.2 */
	{
		fila *f;
		vetor *p;
		int i, tam, res;
		char val[MAX_STR], *s;
		puts("\n\n* Problema 1.2 *");
		f=fila_nova();
		p=vetor_novo();
		while(fscanf(fm, "%s %s", str_aux, val) == 2)
		{
			fila_push(f, str_aux);
			vetor_insere(p, val, p->tamanho);
		}
		res = fila_reordena(f, p);
		tam = fila_tamanho(f);
		for(i=0; i<3 && tam>0; i++)
		{
			printf("%s\n", fila_front(f));
			fila_pop(f);
		}
		for(i=3; i<tam-2; i++)
			fila_pop(f);
		puts("...");
		for(i=tam-2; i<tam; i++)
		{
			printf("%s\n", fila_front(f));
			fila_pop(f);
		}
		fila_apaga(f);
		vetor_apaga(p);
	}

	fclose(fp);
	fclose(fm);
	return 0;
}


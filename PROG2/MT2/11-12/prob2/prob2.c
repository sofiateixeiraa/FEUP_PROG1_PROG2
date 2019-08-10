#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

int topSubmissoes(FILE *f){
if(f==NULL) return 0;
	char str[20];
	int seg, min;
	heap* haux = heap_cria(300);
	if(haux == NULL)  return 0;
	while(fscanf(f, "%s %d %d", str, &min, &seg) != EOF){
		heap_insere(haux,str, 60*min+seg);
	}
	int tempo;
	for(int i=0;i<5;i++){
		tempo=haux->elementos[0]->prioridade;
		min=tempo/60;
		seg=tempo - min*60;
		printf("%s %d %d \n", haux->elementos[0]->valor, min, seg);
		heap_remove(haux);
	}
	return 1;
}


/* v-- nao alterar funcao main --v */

int main()
{
	FILE *f;

	f = fopen("submissoes.txt", "r");

	if(topSubmissoes(f) == 0)
	{
		puts("Erro ao executar funcao.\n");
		fclose(f);
		return 1;
	}

	fclose(f);
	return 0;
}

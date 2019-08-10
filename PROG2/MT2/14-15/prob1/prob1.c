#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "tabdispersao.h"

void avl_max_subarvore(arvore_avl *arv, const char *inicio)
{
	/* prob 1.1 - a implementar */
	if (arv == NULL || inicio == NULL)
		return;

	arvore_avl *subArv = avl_nova();
	if (subArv == NULL)
		return;

	subArv->raiz = avl_pesquisa(arv, inicio);
	printf("%s", avl_max(subArv));
	free(subArv);
}

tabela_dispersao *tabela_copia(tabela_dispersao *original, int novotamanho)
{
	if(original == NULL || novotamanho <=0) return 0;
	tabela_dispersao* tdaux=tabela_nova(novotamanho, original->hfunc);
	int n = 0;
	objeto* elem1=tabela_elementos(original, &n);
	for(int i=0; i<original->tamanho;i++){
		if(tabela_adiciona(tdaux, elem1[i].chave, elem1[i].valor)==TABDISPERSAO_ERRO){
			return 0;
		}
	}
	return tdaux;
}

/* Aqui come�a o c�digo de teste. N�o modificar! */

#define MAX_STR 500
#define TAM_TAB 601
#define TAM_TAB_2 619

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	FILE *fp = fopen("paises.txt", "r");
	FILE *fm = fopen("mails.txt", "r");
	char str_aux[MAX_STR];

	/* teste problema 1.1 */
	{
		arvore_avl *res;
		puts("* Problema 1.1 *");
		res = avl_nova();
		while (fscanf(fp, "%s", str_aux) == 1)
			avl_insere(res, str_aux);
		printf("Arvore original: ");
		avl_imprime(res);
		printf("Maximo da sub-arvore: ");
		avl_max_subarvore(res, "ID");
		avl_apaga(res);
	}

	/* teste problema 1.2 */
	{
		tabela_dispersao *tab = NULL, *tab_exp = NULL;
		puts("\n\n* Problema 1.2 *");
		tab = tabela_nova(TAM_TAB, hash_djbm);
		while (fscanf(fm, "%s", str_aux) == 1)
			tabela_adiciona(tab, str_aux, "");
		mostraTabela(tab);
		tab_exp = tabela_copia(tab, TAM_TAB_2);
		if (tab_exp != NULL)
			mostraTabela(tab_exp);
		tabela_apaga(tab);
		tabela_apaga(tab_exp);
	}

	fclose(fp);
	fclose(fm);
	return 0;
}

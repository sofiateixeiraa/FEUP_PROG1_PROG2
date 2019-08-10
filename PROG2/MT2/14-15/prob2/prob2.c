#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "grafo.h"
#include "heap.h"

int proximas_n_chegadas(lista *tempos, lista *origens, lista *aeroportos, int n) {
    /* prob 2.1 - a implementar */
    if(origens==NULL || tempos ==NULL || aeroportos==NULL || n >25) return 0;
    heap* heapaux = heap_nova(25);
    elemento* origens1= origens->inicio;
    elemento* aeroportos1=aeroportos->inicio;
    elemento* tempos1=tempos->inicio;
    for(int i=0;i<25; i++){
        int indice =atoi(origens1->str);
        heap_insere(heapaux, aeroportos1->str, atoi(tempos1->str));
        for(int a=0;a<indice;a++)
            aeroportos1=aeroportos1->proximo;
        origens1 = origens1->proximo;
        tempos1 = tempos1->proximo;
        aeroportos1= aeroportos->inicio;
    }
    for(int j=0;j<n;j++){
        printf("%d: %s\n", j+1, heap_remove(heapaux));
    }
    return 1;
}

lista *pesquisa_destinos(grafo *rotas, lista *aeroportos, const char *origem) {
    /* prob 2.2 - a implementar */
    if(rotas  ==  NULL || aeroportos  ==  NULL  ||  origem  ==  NULL) return  NULL;

    lista *destinosDiretos  = lista_nova();
    elemento  *iAeroporto = aeroportos->inicio;
    int contador  = 0;

    while(strcmp(iAeroporto->str,origem)  !=  0){
      iAeroporto  = iAeroporto->proximo;
      contador++;
    }

    if(iAeroporto ==  NULL || rotas->adjacencias[contador].tamanho ==  0) return  NULL;
    iAeroporto = aeroportos->inicio;
    lista_no *elAdj  = rotas->adjacencias[contador].inicio;
    while(elAdj !=  NULL){
      for(int a=0;a<elAdj->vertice;a++)
        iAeroporto = iAeroporto->proximo;
      lista_insere(destinosDiretos, iAeroporto->str, 0);
      elAdj = elAdj->proximo;
      iAeroporto = aeroportos->inicio;
    }

    return  destinosDiretos;
}

/* Aqui começa o código de teste. Não modificar! */

grafo *carrega_rotas(lista *aeroportos, const char *filename) {
    if (!filename) return NULL;
    grafo *g = NULL;
    FILE *f;
    int origem, destino;
    f = fopen(filename, "r");
    if (!f) {
        printf("Erro na leitura do ficheiro: %s\n", filename);
        return NULL;
    }
    g = grafo_novo(lista_tamanho(aeroportos), NAODIRECIONADO);
    if (!g) {
        printf("Erro na criacao do grafo\n");
        return NULL;
    }
    while (fscanf(f, "%d\t%d", &origem, &destino) == 2) {
        grafo_adiciona(g, origem, destino);
    }
    fclose(f);
    return g;
}

int main() {
    FILE *f;
    grafo *g = NULL;
    lista *aeroportos;
    char *buff;
    size_t n;

    setvbuf(stdout, NULL, _IONBF, 0);
    f = fopen("aeroportos.txt", "r");
    aeroportos = lista_nova();
    buff = NULL;
    n = 0;
    while (getline(&buff, &n, f) != -1) {
        buff[strlen(buff) - 1] = '\0';
        lista_insere(aeroportos, buff, NULL);
    }
    free(buff);
    fclose(f);

    g = carrega_rotas(aeroportos, "rotas.txt");

    /* teste problema 2.1 */
    {
        FILE *f;
        char tempo[5], origem[10];
        lista *tempos, *origens;

        printf("* Problema 2.1 *\n");

        f = fopen("chegadas.txt", "r");
        tempos = lista_nova();
        origens = lista_nova();

        while (fscanf(f, "%s\t%s", tempo, origem) == 2) {
            lista_insere(tempos, tempo, NULL);
            lista_insere(origens, origem, NULL);
        }

        if (proximas_n_chegadas(tempos, origens, aeroportos, 5) != 1)
            printf("Erro ao executar a funcao\n");

        lista_apaga(tempos);
        lista_apaga(origens);
        fclose(f);
    }

    /* teste problema 2.2 */
    {
        printf("\n* Problema 2.2 *\n");
        const char *origem = "Lille (FR)";
        elemento *elem;
        lista *l = pesquisa_destinos(g, aeroportos, origem);
        if (l == NULL)
            printf("Destinos diretos a partir de %s = 0\n", origem);
        else {
            printf("Destinos diretos a partir de %s = %d\n",
                   origem, lista_tamanho(l));
            for (elem = l->inicio; elem != NULL; elem = elem->proximo)
                printf("%s\n", elem->str);
            lista_apaga(l);
        }
    }

    grafo_apaga(g);
    lista_apaga(aeroportos);
    return 0;
}

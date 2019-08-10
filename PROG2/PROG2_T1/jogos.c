/*****************************************************************/
/*         Trabalho pratico 1 | PROG2 | MIEEC | 2018/19          */
/*****************************************************************/
/*                    FUNCOES A IMPLEMENTAR                      */
/*****************************************************************/

#include "jogos.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


vetor* jogos_load(const char *nomef){
FILE *arq;
vetor *vec = vetor_novo();
jogo jogo1;
arq=fopen(nomef, "r");
    while (fscanf(arq,"%s %s %s %d %d %d %d",jogo1.epoca,jogo1.nome_casa,jogo1.nome_fora,&jogo1.golos_casa,&jogo1.golos_fora,&jogo1.vermelhos_casa,&jogo1.vermelhos_fora)!= EOF){
        vetor_insere(vec, jogo1, -1);
    }
if(vec != NULL) return vec;
else return NULL;
}

int jogos_save(vetor *vec, const char *nomef){
 FILE *arq;
 int i=0;
 arq = fopen(nomef, "w");
    if(arq == NULL)
        return -1;
   for(i=0; i < vetor_tamanho(vec); i++){
       jogo *ptr = vetor_elemento(vec,i);
       fprintf(arq,"%s %s %s %d %d %d %d",ptr->epoca,ptr->nome_casa,ptr->nome_fora,ptr->golos_casa,ptr->golos_fora,ptr->vermelhos_casa,ptr->vermelhos_fora);
   }
   fclose(arq);
    return i;

}
vetor_equipas *stats_equipa(vetor *vec){
  equipa team;
  vetor_equipas *ptr;
  int i = 0, r=0, m=0;
  int ver1=0, ver2=0;


    ptr = vetor_equipas_novo();
    if(ptr == NULL)
        return NULL; // Se houver problemas na criação do vetor, 
                     //retorna código de erro, no caso, NULL
    
    while (i<vetor_tamanho(vec)){
        if(vetor_equipas_tamanho(ptr)==0){ //verifica se ja existe alguma equipa no vetor criado
//casa         
            strcpy(team.nome_equipa,vec->elementos[i].nome_casa);
            team.diff_golos = vec->elementos[i].golos_casa - vec->elementos[i].golos_fora;
                if(strcmp(vec->elementos[i].epoca, "15/16") == 0){
                    team.vermelhos[0] = vec->elementos[i].vermelhos_casa;
                }
                else if(strcmp(vec->elementos[i].epoca, "16/17") == 0){
                    team.vermelhos[1]=vec->elementos[i].vermelhos_casa;
                }
                else if(strcmp(vec->elementos[i].epoca, "17/18") == 0){ 
                    team.vermelhos[2]=vec->elementos[i].vermelhos_casa;
                }
                vetor_equipas_insere(ptr,team,r);
                r++;
//fora
            strcpy(team.nome_equipa,vec->elementos[i].nome_fora);
            team.diff_golos = vec->elementos[i].golos_fora - vec->elementos[i].golos_casa;
                if(strcmp(vec->elementos[i].epoca, "15/16") == 0){
                    team.vermelhos[0] = vec->elementos[i].vermelhos_fora;
                }
                else if(strcmp(vec->elementos[i].epoca, "16/17") == 0){
                    team.vermelhos[1]=vec->elementos[i].vermelhos_fora;
                }
                else if(strcmp(vec->elementos[i].epoca, "17/18") == 0){ 
                    team.vermelhos[2]=vec->elementos[i].vermelhos_fora;
                }
                vetor_equipas_insere(ptr,team,r);
        }//if

        else{
//casa          
            strcpy(team.nome_equipa, vec->elementos[i].nome_casa);
            team.diff_golos = vec->elementos[i].golos_casa - vec->elementos[i].golos_fora;
                if(strcmp(vec->elementos[i].epoca, "15/16") == 0){
                    team.vermelhos[0] = vec->elementos[i].vermelhos_casa;
                }
                else if(strcmp(vec->elementos[i].epoca, "16/17") == 0){
                    team.vermelhos[1]=vec->elementos[i].vermelhos_casa;
                }
                else if(strcmp(vec->elementos[i].epoca, "17/18") == 0){
                    team.vermelhos[2]=vec->elementos[i].vermelhos_casa;
                }

            for(int j= 0; j<=r; j++){ 
                if(strcmp(team.nome_equipa, ptr->elementos[j].nome_equipa) == 0)
                {
                    ptr->elementos[j].diff_golos = ptr->elementos[j].diff_golos + team.diff_golos;
                    for( m=0; m < 3; m++)
                    {
                        ptr->elementos[j].vermelhos[m] = ptr->elementos[j].vermelhos[m] + team.vermelhos[m];
                    } 
                    ver1 = 1;
                }
            }

                if(ver1 == 0){
                    r++;
                    vetor_equipas_insere(ptr,team,r);
                }

//fora 
            strcpy(team.nome_equipa, vec->elementos[i].nome_fora);
            team.diff_golos = vec->elementos[i].golos_fora - vec->elementos[i].golos_casa;
                if(strcmp(vec->elementos[i].epoca, "15/16") == 0){
                    team.vermelhos[0] = vec->elementos[i].vermelhos_casa;
                }
                else if(strcmp(vec->elementos[i].epoca, "16/17") == 0){
                    team.vermelhos[1]=vec->elementos[i].vermelhos_casa;
                }
                else if(strcmp(vec->elementos[i].epoca, "17/18") == 0){
                    team.vermelhos[2]=vec->elementos[i].vermelhos_casa;
                }

            for(int j= 0; j<=r; j++){ 
                if(strcmp(team.nome_equipa, ptr->elementos[j].nome_equipa) == 0)
                {
                    ptr->elementos[j].diff_golos = ptr->elementos[j].diff_golos + team.diff_golos;
                    for( m=0; m < 3; m++)
                    {
                        ptr->elementos[j].vermelhos[m] = ptr->elementos[j].vermelhos[m] + team.vermelhos[m];
                    } 
                    ver2 = 1;
                }
            }
                if(ver2 == 0){
                    r++;
                    vetor_equipas_insere(ptr,team,r);
                }
            i++;
            ver1=0;
            ver2=0;
        }//else

            for(int a=0; a<vetor_tamanho(vec); a++){
                for(int b=0; b<3; b++){
                    ptr->elementos[a].vermelhos[b] = ptr->elementos[a].vermelhos[b] / 38;
                }
            }
    }//while 

    return ptr;
    return NULL;
}

void ordena_diff_golos(vetor_equipas v, int left, int right){
    int i = left;
    int j = right;
    equipa aux;
    //int tamanho = right - left + 1;

        int pivot = v.elementos[(i+j)/2].diff_golos;
    
    while(i<=j){
        while(v.elementos[i].diff_golos < pivot && i < right){
            i++;
        }
        while(v.elementos[j].diff_golos > pivot && j > left){
            j--;
        }

        if(i <= j){
            aux = v.elementos[i];
            v.elementos[i] = v.elementos[j];
            v.elementos[j] = aux;
            i++;
            j--;
        }//if
    }//while

        if(j > left) ordena_diff_golos(v,left,j);
        if(i < right) ordena_diff_golos(v,i,right);
    
      
}  

void ordena_alfa(vetor_equipas v, int left, int right){
    int i = left;
    int j = right;
    equipa aux;
    char pivot[50];
    strcpy(pivot,v.elementos[(j+i)/2].nome_equipa);

    while(i <= j){
        while(strcmp(v.elementos[i].nome_equipa,pivot) < 0 && i < right){
            i++;
        }
        while(strcmp(v.elementos[j].nome_equipa,pivot) > 0 && j > left){
            j--;
        }
        
        if ( i <= j){
            aux = v.elementos[i];
            v.elementos[i] = v.elementos[j];
            v.elementos[j] = aux;
            i++;
            j--;
        }
    }
    if(j > left) ordena_alfa(v,left,j);
    if(i < right) ordena_alfa(v,i,right);
 
}

int equipas_ordena(vetor_equipas *v, int criterio){
    
    if(criterio == 1) ordena_diff_golos(*v, 0, (v->tamanho)-1);
    else ordena_alfa(*v, 0, (v->tamanho)-1);

    return 0;
    return -1;
}

int corrige_jogo(vetor *vec, const char *nomef){

    int i=0;
    vetor *vec1 = jogos_load(nomef);
    vetor_equipas *team = stats_equipa(vec);

    for(i=0; i < vetor_tamanho(vec); i++){

        if(strcmp(vec->elementos[i].epoca,vec1->elementos[i].epoca) == 0 && strcmp(vec->elementos[i].nome_casa,vec1->elementos[i].nome_casa) == 0 && strcmp(vec->elementos[i].nome_fora,vec1->elementos[i].nome_fora) == 0){
            vec->elementos[i].vermelhos_casa = vec1->elementos[i].vermelhos_casa;
            vec->elementos[i].vermelhos_fora = vec1->elementos[i].vermelhos_fora;
            vec->elementos[i].golos_casa=vec1->elementos[i].golos_casa;
            vec->elementos[i].golos_fora=vec1->elementos[i].golos_fora;
            
            team = stats_equipa(vec);
        }
    }
    return 0;
    return -1;
}


int pontos_de_equipa(vetor *vec, char *nome_equipa, char *epoca){
int i=0;
int pontos_equipa=0;
    for( i=0; i<vetor_tamanho(vec); i++){ 
        
        if(strcmp(epoca,vec->elementos[i].epoca)==0 && strcmp(nome_equipa,vec->elementos[i].nome_casa)==0){
           if(vec->elementos[i].golos_casa > vec->elementos[i].golos_fora){
               pontos_equipa = pontos_equipa + 3;
           }
           else if(vec->elementos[i].golos_casa == vec->elementos[i].golos_fora){
               pontos_equipa = pontos_equipa + 1;
           }
           else if (vec->elementos[i].golos_casa < vec->elementos[i].golos_fora){
               pontos_equipa = pontos_equipa + 0;
           }
           
        }

       if(strcmp(epoca,vec->elementos[i].epoca)==0 && strcmp(nome_equipa,vec->elementos[i].nome_fora)==0){
           if(vec->elementos[i].golos_fora > vec->elementos[i].golos_casa){
                pontos_equipa = pontos_equipa + 3;
           }
            else if(vec->elementos[i].golos_fora == vec->elementos[i].golos_casa){
                pontos_equipa = pontos_equipa + 1;
           }
           else if (vec->elementos[i].golos_fora < vec->elementos[i].golos_casa){
                pontos_equipa = pontos_equipa + 0;
           }
            
        }
    }

return pontos_equipa;
    return -1;
}








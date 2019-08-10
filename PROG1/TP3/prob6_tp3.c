/*Ana Sofia Teixeira, 2018 */
#include <stdio.h>

int main(){
    int x, y;
    printf("Indique o ponto(x,y):");
    scanf("%d %d",&x, &y);
    if(x>0 && y>0){
        printf("O ponto encontra-se no 1ºquadrante\n");
    }
    if(x<0 && y>0){
        printf("O ponto encontra-se no 2ºquadrante\n");
    }
    if(x<0 && y<0){
        printf("O ponto encontra-se no 3ºquadrante\n");
    }
    if(x>0 && y<0){
        printf("O ponto encontra-se no 4ºquadrante\n");
    }
}

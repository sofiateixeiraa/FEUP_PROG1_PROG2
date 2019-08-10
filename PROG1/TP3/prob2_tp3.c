/*Ana Sofia Teixeira, 2018 */
#include <stdio.h>
int main (){
    int i;
    printf("Indique um número:");
    scanf("%d", &i);
    if(i<-10){
        printf("O número %d pertence aos intervalos\n", i);
    }
    if (i>=5 && i<45){
        printf("O número %d pertence aos intervalos\n", i);
    }
    if(i>120 && i<=245){
        printf("O número pertence aos intervalos\n");
    }
    else{
     printf("O número não pertence aos intervalos\n");
    }
}

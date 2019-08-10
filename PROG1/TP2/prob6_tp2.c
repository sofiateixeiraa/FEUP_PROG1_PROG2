/*Ana Sofia Teixeira, 2018 */
#include <stdio.h>
int main (){
    int i, x, j=0;
    float y, aux, k;
    printf("Quantos segundos?");
    scanf("%d", &i);
    x=i/60;
    while(x>24==1){
        x=x-24;
        j++;
    }
    y=(float)i/60;
    aux=y-x;
    k=aux*60;
    printf("%d segundos = %d dias e %d horas e %f minutos", i, j, x, k);
}

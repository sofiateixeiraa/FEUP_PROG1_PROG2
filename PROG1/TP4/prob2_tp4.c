/*Ana Sofia Teixeira, 2018 */
#include <stdio.h>
int main(){
    float num, soma=0, media, i=0;
    printf("Insira números:");
while(1){
    scanf("%f", &num);
    if(scanf("%f", &num) != 1){ 
    break;
    }
    soma+=num;
    i++;
}
media=soma/i;
printf("Média:%.2f", media);
}
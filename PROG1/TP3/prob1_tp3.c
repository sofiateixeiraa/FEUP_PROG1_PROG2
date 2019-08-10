/*Ana Sofia Teixeira, 2018 */
#include <stdio.h>
int main (){
    int i;
    printf("Indique um número:");
    scanf("%d", &i);
    if(i%2==0){
        printf("O número %d é par\n", i);
    }
    else{
        printf("O número %d é ímpar\n", i);
    }
}

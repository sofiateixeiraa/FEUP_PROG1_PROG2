/*Ana Sofia Teixeira, 2018 */
#include <stdio.h>

int main(){
    int i, j, r;
    printf("Número inteiro 1:");
    scanf("%d", &i);
    printf("Número inteiro 2:");
    scanf("%d", &j);
    r = i%j;
    if(r==0){
        printf("%d é múltiplo de %d", i, j);
    }
    else 
        printf("%d não é múltiplo de %d", i, j);
}

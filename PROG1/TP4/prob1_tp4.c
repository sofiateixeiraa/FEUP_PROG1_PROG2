/*Ana Sofia Teixeira, 2018 */
#include <stdio.h>
int main(){
    int num, total=0, resto;
    printf("Insira um número:");
    scanf("%d", &num);
    while(num>0){
        resto=num%10;
        total+=resto;
        num=num/10;
    }
    printf("Total=%d\n", total);
}
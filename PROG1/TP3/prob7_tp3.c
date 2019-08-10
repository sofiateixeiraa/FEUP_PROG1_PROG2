/*Ana Sofia Teixeira, 2018 */
#include <stdio.h>
int main(){
    int num1, num2, num3;
    printf("Insira 3 números:");
    scanf("%d %d %d", &num1, &num2, &num3);
    if (num1<num2 && num2<num3){
        printf("%d %d %d", num1, num2, num3);
    }
    if (num1<num2 && num2>num3){
        printf("%d %d %d", num1, num3, num2);
    }
    if (num1>num2 && num2>num3){
        printf("%d %d %d", num3, num2, num1);
    }
    if (num1>num2 && num1<num3){
        printf("%d %d %d", num2, num1, num3);
    }
    if (num1<num2 && num1>num3){
        printf("%d %d %d", num3, num1, num2);
    }
    if (num1>num3 && num2<num3){
        printf("%d %d %d", num2, num3, num1);
    }
}

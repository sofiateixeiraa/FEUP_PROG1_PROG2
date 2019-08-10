/*Ana Sofia Teixeira, 2018 */
#include <stdio.h>

int main() {
    int fator, guarda_fator, num;

    printf("Introduza número inteiro: "); scanf("%d", &num);

    fator=2;
    while(num>1) {
        if (num%fator==0) {
            while(num%fator==0) {
                printf("%d ", fator);
                num=num/fator;
            }
        }
        else {
            fator++;
        }
    }

    printf("\n");
}
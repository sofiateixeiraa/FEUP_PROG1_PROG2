/*Ana Sofia Teixeira, 2018 */
#include <stdio.h>

int main (){
    float n, aux;
    int x;
    printf("Introduza um número:");
    scanf("%f", &n);
    printf("Número com 3 casas decimais = %.3f\n", n);
    x=(int)n;
    aux=n-x;
    printf("Parte inteira do número: %d\n", x);
    printf("Parte decimal do número: %f\n", aux);
}

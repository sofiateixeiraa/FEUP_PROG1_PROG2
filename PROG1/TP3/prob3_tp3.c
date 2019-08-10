/*Ana Sofia Teixeira, 2018 */
#include <stdio.h>
int main(){
    float a, b;
    printf("Qual a altura da pessoa?");
    scanf("%f", &a);
    b=a;
    if (b<1.3){
        printf("Essa pessoa é baixissima\n");
    }
    if (b>=1.3 && b<1.6){
        printf("Essa pessoa é baixa\n");
    }
    if (b>=1.6 && b<1.75){
        printf("Essa pessoa é mediana\n");
    }
    if (b>=1.75 && b<1.9){
        printf("Essa pessoa é alta\n");
    }
    if (b>=1.9){
        printf("Essa pessoa é baixissima\n");
    }
}

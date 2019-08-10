/*Ana Sofia Teixeira, 2018 */
#include <stdio.h>

int main (){
    int r;
    float p, a;
    printf("Qual é o raio da circunferência?\n");
    scanf ("%d", &r);
    p=2*r*3.14;
    a=3.14*r*r;
    printf("Perímetro=%f\n", p);
    printf("Área=%f\n", a);
}

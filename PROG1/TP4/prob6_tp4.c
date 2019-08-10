/*Ana Sofia Teixeira, 2018 */
#include <stdio.h>

int main() {
    int anos;
    float PA, PB, TA, TB;
    printf("Introduza população de país A: ");
    scanf("%f", &PA);
    printf("Introduza taxa de crescimento anual de país A: ");
    scanf("%f", &TA);
    printf("Introduza população de país B: ");
    scanf("%f", &PB);
    printf("Introduza taxa de crescimento anual de país B: ");
    scanf("%f", &TB);

    anos=0;
   
    TA = TA/100;
    TB = TB/100;
      
    while (PA>PB) {
        PB = PB + (PB * TB);
        PA = PA + (PA * TA);
        anos+=1;
    }
    printf("População de B ultrapassa a de A em %d anos\n", anos);
    
}
/*Ana Sofia Teixeira, 2018 */
#include<stdio.h>
int main() {
    int altura, count1, count2, count3, count4, count5;

    printf("Introduza altura da árvore: ");
    scanf("%d", &altura);

    count2=1;
    count3=altura-1;
    count4=1;

    for (count1=altura; count1>0; count1--) {
        
        while (count2<=count3) {
            printf(" ");
            count3--;
        }

        for(count3=1; count3<=2*count4-1; count3++) {
            printf("*");
        }

        count4++;
        count2++;
        count3=altura-1;
        printf("\n");
    }
    for (count5=1; count5<altura; count5++) {
        printf(" ");
    }
    printf("*\n");
}
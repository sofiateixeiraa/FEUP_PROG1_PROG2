/*Ana Sofia Teixeira, 2018 */
#include <stdio.h>

int main() {
    int num, centena, dezena, unidade;
    char roman1,roman2,roman3; 
    printf("Introduza um número inteiro: ");
    scanf("%d", &num);

    centena=num/100;
    
    if (centena==9) {
        printf("CM");
    }
    else if (centena>=5 && centena<9) {
        printf("D");
        while (centena-5>0) {
            printf("C");
            centena-=1;
        }
    }
    else if (centena==4) {
        printf("CD");
    }
    else if (centena>0 && centena<4) {
        while (centena>0) {
            printf("C");
            centena-=1;
        }
    }
    
    dezena=num/10-10*(num/100);

    if (dezena==9) {
        printf("XC");
    }
    else if (dezena>=5 && dezena<9) {
        printf("L");
        while (dezena-5>0) {
            printf("X");
            dezena-=1;
        }
    }
    else if (dezena==4) {
        printf("XL");
    }
    else if (dezena>0 && dezena<4) {
        while (dezena>0) {
            printf("X");
            dezena-=1;
        }
    }
    
    unidade=num%10;
    
    if (unidade==9) {
        printf("IX");
    }
    else if (unidade>=5 && unidade<9) {
        printf("V");
        while (unidade-5>0) {
            printf("I");
            unidade-=1;
        }
    }
    else if (unidade==4) {
        printf("IV");
    }
    else if (unidade>=1 && unidade<4) {
        printf("I");
        while(unidade-1>0) {
            printf("I");
            unidade-=1;
        }
    }
    
    printf("\n");
    
    return 0;
}

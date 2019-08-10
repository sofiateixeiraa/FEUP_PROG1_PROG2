/*Ana Sofia Teixeira, 2018 */
#include <stdio.h>

int main()
{
    float num1,num2;
    char conta;
    printf("Introduza operação a efetuar: ");
    scanf("%f %c %f",&num1,&conta,&num2);

    if (conta=='+') {
        printf("%.4f",num1+num2);
    }
    else if (conta=='-') {
        printf("%.4f",num1-num2);
    }
    else if (conta=='*') {
        printf("%.4f",num1*num2);
    }
    else if (conta=='/') {
        printf("%.4f",num1/num2);
    }
    else if (conta=='%') {
        printf("%d",(int)num1%(int)num2);
    }

    return 0;
}

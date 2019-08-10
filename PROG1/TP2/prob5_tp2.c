/*Ana Sofia Teixeira, 2018 */
#include <stdio.h>
int main(){
    float n, aux;
    int x;
    printf("Introduza um número:");
    scanf("%f", &n);
    x=(int)n;
    aux=n-x;
    if(aux>=0.5){
        if(x%2==0){
            printf("%d %d\n", x, x+2);
        }
        else{
            printf("%d %d\n", x-1, x+1);
        }
    }
    else{
       if(x%2==0){
            printf("%d %d\n", x-2, x+2);
        }
        else{
            printf("%d %d\n", x-1, x+1);
        }
    } 
    }

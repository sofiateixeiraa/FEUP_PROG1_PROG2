
/*Ana Sofia Teixeira, 2018 */
#include <stdio.h>

int main() {
    char letra;
    int contaa=0, contae=0, contai=0, contao=0, contau=0;

    while(letra != '.') {
        scanf("%c", &letra);
        switch (letra) {
            case 'a': {contaa++; continue; }
            case 'e': {contae++; continue; }
            case 'i': {contai++; continue; }
            case 'o': {contao++; continue; }
            case 'u': {contau++; continue; }
            case 'A': {contaa++; continue; }
            case 'E': {contae++; continue; }
            case 'I': {contai++; continue; }
            case 'O': {contao++; continue; }
            case 'U': {contau++; continue; }
        }
    }
    printf("A: %d\n", contaa);
    printf("E: %d\n", contae);
    printf("I: %d\n", contai);
    printf("O: %d\n", contao);
    printf("U: %d\n", contau);
    return 0;
}
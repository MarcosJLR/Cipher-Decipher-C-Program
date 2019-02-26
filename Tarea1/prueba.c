#include "date.h"
#include "cipher.h"

#define MAX_SZ 1000

int main(){
    Cipher *A, *B;
    
    char s[14];
    char *nat, *enc;
    size_t sz = MAX_SZ;
    nat = malloc(sz*sizeof(char));
    enc = malloc(sz*sizeof(char));
    int d, m, y;

        printf("Fecha: ");
        scanf("%s", s);
        printf("Cifrado: ");
        while(getline(&enc, &sz, stdin) <= 1);
        printf("Descifrado: ");
        while(getline(&nat, &sz, stdin) <= 1);
        sscanf(s, "%d/%d/%d", &d, &m, &y);
        A = mkCipher(dateToInt(d, m, y), nat, enc);
        
        printf("Fecha: ");
        scanf("%s", s);
        printf("Cifrado: ");
        while(getline(&enc, &sz, stdin) <= 1);
        printf("Descifrado: ");
        while(getline(&nat, &sz, stdin) <= 1);
        sscanf(s, "%d/%d/%d", &d, &m, &y);
        B = mkCipher(dateToInt(d, m, y), nat, enc);
        
    printf("A:\n");
    printCipher(A);

    printf("B:\n");
    printCipher(B);

    printf("A U B:\n");
    mergeCipher(A, B);
    printCipher(A);
}
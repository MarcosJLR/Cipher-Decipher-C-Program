#include "main.h"

void printMenu(){
    printf("\n1. Registrar nuevos mensajes cifrados y sus descifrados\n");
    printf("2. Descifrar mensajes\n");
    printf("3. Cifrar mensajes\n");
    printf("4. Mostrar un esquema de cifrado\n");
    printf("5. Borrar un esquema de cifrado\n");
    printf("6. Salir\n");
}

void opt1(List *L){
    printf("\nModo insercion.\nFormato de fecha dd/mm/yyyy\n");
    printf("(inserte '#' para volver al menu)\n");
    char s[14];
    char *nat, *enc;
    size_t sz = MAX_SZ;
    nat = malloc(sz*sizeof(char));
    enc = malloc(sz*sizeof(char));
    int d, m, y;
    while(1){
        printf("Fecha: ");
        scanf("%s", s);
        if(s[0] == '#') return;
        printf("Cifrado: ");
        while(getline(&enc, &sz, stdin) <= 1);
        printf("Descifrado: ");
        while(getline(&nat, &sz, stdin) <= 1);
        sscanf(s, "%d/%d/%d", &d, &m, &y);
        Cipher *C = mkCipher(dateToInt(d, m, y), nat, enc);
        if(!listInsert(L, C))
            fprintf(stderr, "El mensaje no es consistente con uno de la misma fecha.\n");
    }
    free(nat);
    free(enc);
}

void opt2(List *L){
    printf("\nModo descifrado.\nFormato de fecha dd/mm/yyyy\n");
    printf("(inserte '#' para salir)\n");
    char s[14];
    char *mes;
    size_t sz = MAX_SZ;
    mes = malloc(sz*sizeof(char));
    int d, m, y;
    while(1){
        printf("Fecha: ");
        scanf("%s", s);
        if(s[0] == '#') return;
        printf("Mensaje: ");
        while(getline(&mes, &sz, stdin) <= 1);
        sscanf(s, "%d/%d/%d", &d, &m, &y);
        listDecrypt(L, dateToInt(d, m, y), mes);
        printf("%s\n", mes);    
    }
    free(mes);
}

void opt3(List *L){
    printf("\nModo cifrado.\nFormato de fecha dd/mm/yyyy\n");
    printf("(inserte '#' para salir)\n");
    char s[14];
    char *mes;
    size_t sz = MAX_SZ;
    mes = malloc(sz*sizeof(char));
    int d, m, y;
    while(1){
        printf("Fecha: ");
        scanf("%s", s);
        if(s[0] == '#') return;
        printf("Mensaje: ");
        while(getline(&mes, &sz, stdin) <= 1);
        sscanf(s, "%d/%d/%d", &d, &m, &y);
        listEncrypt(L, dateToInt(d, m, y), mes);
        printf("%s\n", mes);    
    }
    free(mes);
}

void opt4(List *L){
    printf("\nMostrar esquema.\nFormato de fecha dd/mm/yyyy\n");
    printf("Fecha: ");
    char s[14];
    int d, m, y;
    scanf("%s", s);
    sscanf(s, "%d/%d/%d", &d, &m, &y);
    listPrintCipher(L, dateToInt(d, m, y));
}

void opt5(List *L){
    printf("\nBorrar esquema.\nFormato de fecha dd/mm/yyyy\n");
    printf("Fecha: ");
    int d, m, y;
    scanf("%d/%d/%d", &d, &m, &y);
    listDelete(L, dateToInt(d, m, y));

}

int main(){

    List *L = mkList();
    while(1){
        printMenu();
        int op;
        scanf("%d", &op);
        if(op == 1) opt1(L);
        if(op == 2) opt2(L);
        if(op == 3) opt3(L);
        if(op == 4) opt4(L);
        if(op == 5) opt5(L);
        if(op == 6) break;
        printListDates(L);
    }

    return 0;
}
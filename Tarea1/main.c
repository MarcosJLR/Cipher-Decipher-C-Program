#include "main.h"

void printMenu(){
    printf("1. Registrar nuevos mensajes cifrados y sus descifrados\n");
    printf("2. Descifrar mensajes\n");
    printf("3. Cifrar mensajes\n");
    printf("4. Mostrar un esquema de cifrado\n");
    printf("5. Borrar un esquema de cifrado\n");
    printf("6. Salir\n");
}

void opt1(List *L){
    printf("Modo insercion.\nFormato de fecha dd/mm/yyyy\n");
    printf("(inserte '#' para volver al menu)\n");
    char s[14];
    char nat[MAX_SZ], enc[MAX_SZ];
    int d, m, y;
    while(1){
        printf("Fecha: ");
        scanf("%s", s);
        if(s[0] == '#') return;
        printf("Cifrado: ");
        scanf("%s", enc);
        printf("Descifrado: ");
        scanf("%s", nat);
        sscanf(s, "%d/%d/%d", &d, &m, &y);
        Cipher *C = mkCipher(dateToInt(d, m, y), nat, enc);
        if(!listInsert(L, C))
            fprintf(stderr, "El mensaje no es consistente con uno de la misma fecha.\n");
    }
}

void opt2(List *L){
    printf("Modo descifrado.\nFormato de fecha dd/mm/yyyy\n");
    printf("(inserte '#' para salir)");
    char s[14];
    char mes[MAX_SZ];
    int d, m, y;
    while(1){
        printf("Fecha: ");
        scanf("%s", s);
        if(s[0] == '#') return;
        printf("Mensaje: ");
        scanf("%s", mes);
        sscanf(s, "%d/%d/%d", &d, &m, &y);
        listDecrypt(L, dateToInt(d, m, y), mes);
        printf("%s\n", mes);    
    }
}

void opt3(List *L){
    printf("Modo cifrado.\nFormato de fecha dd/mm/yyyy\n");
    printf("(inserte '#' para salir)");
    char s[14];
    char mes[MAX_SZ];
    int d, m, y;
    while(1){
        printf("Fecha: ");
        scanf("%s", s);
        if(s[0] == '#') return;
        printf("Mensaje: ");
        scanf("%s", mes);
        sscanf(s, "%d/%d/%d", &d, &m, &y);
        listEncrypt(L, dateToInt(d, m, y), mes);
        printf("%s\n", mes);    
    }
}

void opt4(List *L){
    printf("Mostrar esquema.\nFormato de fecha dd/mm/yyyy\n");

}

void opt5(List *L){
    printf("Mostrar esquema.\nFormato de fecha dd/mm/yyyy\n");

}

int main(){

    List *L;
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
    }

    return 0;
}
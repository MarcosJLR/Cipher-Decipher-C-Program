#ifndef CIPHER_H
#define CIPHER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int bool;
#define true 1
#define false 0

// Estructura con fecha y esquema de cifrado.
typedef struct{
    time_t date;
    char deciph[96];
    char ciph[96];
} Cipher;

// Crea un nuevo esquema de cifrado y retorna un apuntador a el.
Cipher *mkCipher(time_t dt, char *natural, char *encrypted);

// Nos dice si el cifrado A es anterior al cifrado B
bool isBefore(Cipher *A, Cipher *B);

// Nos dice si el cifrado A y el cifrado B son de la misma fecha
bool isSameDate(Cipher *A, Cipher *B);

// Nos dice si el cifrado A y el cifrado B son compatibles
bool isCompatible(Cipher *A, Cipher *B);

// Mezcla dos cifrados A y B si son compatibles o devuelve false en caso
// de que no lo sean. El resultado de la mezcla se guarda en A.
// La fecha del resultado es la menor fecha entre A y B.
bool mergeCipher(Cipher *A, Cipher *B);

// Cifra el mensaje en s (debe ser un string terminado en '\0') 
// segun el cifrado A. Retorna false si algun caracter de s no se 
// pudo cifrar (y se coloca '#' en su lugar)
// Retorna true de lo contrario.
bool encrypt(Cipher *A, char *s);

// Descifra el mensaje en s (debe ser un string terminado en '\0') 
// segun el cifrado A. Retorna false si algun caracter de s no se 
// pudo descifrar (y se coloca '#' en su lugar)
// Retorna true de lo contrario.
bool decrypt(Cipher *A, char *s);

// Imprime un esquema de cifrado.
void printCipher(Cipher *A);

#endif
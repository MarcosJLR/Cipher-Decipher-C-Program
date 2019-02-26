#ifndef CIPHER_H
#define CIPHER_H

#include "date.h"

typedef int bool;
#define true 1
#define false 0

// Estructura con fecha y esquema de cifrado.
typedef struct{
    long date;
    int x;
} Cipher;

// Crea un nuevo esquema de cifrado y retorna un apuntador a el.
Cipher *mkCipher(long dt, int x);

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



#endif
#include <stdio.h>
#include <stdlib.h>
#include "cipher2.h"

typedef int bool;
#define true 1
#define false 0

Cipher *mkCipher(long dt, int x){
    Cipher *newCipher = malloc(sizeof (Cipher));
    newCipher->date = dt;
    newCipher->x = x;
    return newCipher;
}

bool isBefore(Cipher *A, Cipher *B){
	return A->date < B->date;
}
bool isSameDate(Cipher *A, Cipher *B){
	return A->date == B->date;
}
bool isCompatible(Cipher *A, Cipher *B){
	return (A->x - B->x > 0)?A->x - B->x:B->x - A->x <= 3;
}
bool mergeCipher(Cipher *A, Cipher *B){
	return (A->x - B->x > 0)?A->x - B->x:B->x - A->x <= 3;
}
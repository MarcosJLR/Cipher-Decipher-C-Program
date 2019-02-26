#include "cipher.h"

typedef int bool;
#define true 1
#define false 0

Cipher *mkCipher(long dt, char *nat, char *enc){
    Cipher *newCipher = malloc(sizeof (Cipher));
    int i;
	newCipher->ciph[0] = newCipher->deciph[0] = ' ';
    for(i=1;i<96;i++)
    	newCipher->ciph[i] = newCipher->deciph[i] = '#';

    i = 0;
    while(nat[i]){
		if(nat[i] <= ' ') { i++; continue; }
    	newCipher->ciph[ nat[i] - 32 ] = enc[i];
    	newCipher->deciph[ enc[i] - 32 ] = nat[i];
		i++;
	}
    newCipher->date = dt;
    return newCipher;
}

bool isBefore(Cipher *A, Cipher *B){
	return A->date < B->date;
}

bool isSameDate(Cipher *A, Cipher *B){
	return A->date == B->date;
}

bool isCompatible(Cipher *A, Cipher *B){
	char *a,*b;
	int i;
	a = A->ciph;
	b = B->ciph;
	for(i = 0; i<96; i++)
		if(a[i] != '#' && b[i] != '#' && a[i] != b[i]) return false;;
	return true;
	
}

bool mergeCipher(Cipher *A, Cipher *B){
	if(!isCompatible(A,B)) return false;
	char *a,*b;
	a = A->ciph;
	b = B->ciph;
	for(int i=0;i<96;i++)
		if(a[i] == '#')
			a[i] = b[i];
	a = A->deciph;
	b = B->deciph;
	for(int i=0;i<96;i++)
		if(a[i] == '#')
			a[i] = b[i];
	return true;
}

bool encrypt(Cipher *A, char *s){
	char c;
	bool uncyph = true;
	char *a;
	a = A->ciph;
	for(int i=0; s[i] != '\0'; i++){
		if(s[i] < ' ') continue;
		c = a[ s[i] - 32 ];
		if(c=='#'){
			uncyph = false;
			s[i] = '#';
		}
		else s[i] = c;
	}
	return uncyph;
}

bool decrypt(Cipher *A, char *s){
	char c;
	bool uncyph = true;
	char *a;
	a = A->deciph;
	for(int i=0; s[i] != '\0'; i++){
		if(s[i] < ' ') continue;
		c = a[ s[i] - 32 ];
		if(c=='#'){
			uncyph = false;
			s[i] = '#';
		}
		else s[i] = c;
	}
	return uncyph;
}

void printCipher(Cipher *A){
	int i;
	for(i=0;i<95;i++) printf("%c", (char)(32 + i));
	printf("\n");
	for(i=0;i<95;i++) printf("%c", A->ciph[i]);
	printf("\n");
}
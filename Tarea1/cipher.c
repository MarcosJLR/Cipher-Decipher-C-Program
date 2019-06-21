#include "cipher.h"

typedef int bool;
#define true 1
#define false 0

/* Crea un nuevo esquema de cifrado a partir de un string en lenguaje natural, su equivalente 
   encriptado y una fecha. Se generará un ciher donde el valor ciph tenga en la posicion
   del caracter natural al caracter encriptado y deciph tenga en la posicion del caracter 
   encriptado al caracter natural correspondiente. La fecha dada será asignada a date en el cipher.
*/
Cipher *mkCipher(long dt, char *nat, char *enc){
    Cipher *newCipher = malloc(sizeof (Cipher));
    int i;
	newCipher->ciph[0] = newCipher->deciph[0] = ' ';
    for(i=1;i<96;i++)
    	newCipher->ciph[i] = newCipher->deciph[i] = '#';

    i = 0;
    while(nat[i]){
		if(nat[i] <= ' ') { i++; continue; }
		if(newCipher->ciph[ nat[i] - 32 ] != '#' || newCipher->deciph[ enc[i] - 32 ] != '#')
			fprintf(stderr, "El esquema de cifrado no es consistente!\n");
    	newCipher->ciph[ nat[i] - 32 ] = enc[i];
    	newCipher->deciph[ enc[i] - 32 ] = nat[i];
		i++;
	}
    newCipher->date = dt;
    return newCipher;
}

// Devuelve si la fecha de cipher A es previa a la de cipher B
bool isBefore(Cipher *A, Cipher *B){
	return A->date < B->date;
}

// Devuelve si las fechas de dos ciphers son iguales
bool isSameDate(Cipher *A, Cipher *B){
	return A->date == B->date;
}

/* Devuelve un booleano indicando si dos cipher son compatibles, es decir, al usar uno
   de los dos cipher sobre un caracter asignaria el mismo caracter cifrado que asignaria
   el otro, a no ser que alguno no tenga un valor asociado a ese caracter
*/
bool isCompatible(Cipher *A, Cipher *B){
	char *a,*b;
	int i;
	a = A->ciph;
	b = B->ciph;
	for(i = 0; i<96; i++)
		if(a[i] != '#' && b[i] != '#' && a[i] != b[i]) return false;;
	return true;
	
}

/* Mezcla dos cifrados A y B si son compatibles o devuelve false en caso
   de que no lo sean. El resultado de la mezcla se guarda en A.
   La fecha del resultado es la menor fecha entre A y B.
*/
bool mergeCipher(Cipher *A, Cipher *B){
	if(!isCompatible(A,B)) return false;
	char *a,*b;
	A->date = (A->date<B->date) ? A->date : B->date;
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

/* Toma un string y un cipher y cifra el string usando el cipher. Retorna true en caso de haber 
   podido encriptarse completamente, mientras que retorna false en caso de que uno de los caracteres
   a enriptar no tuviera un valor asignado, completando estos caracteres con '#'.
*/
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

/* Recibe un string y un Cipher y descifra el string a su mensaje original. Retorna true en caso de haber 
   podido descifrarse completamente, mientras que retorna false en caso de que uno de los caracteres
   a descifrar no tuviera un valor asignado, completando estos caracteres con '#'.
*/
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

// Imprime los caracteres ASCII y luego imprime el equivalente a ese caracter superior cifrado
void printCipher(Cipher *A){
	int i;
	for(i=0;i<95;i++) printf("%c", (char)(32 + i));
	printf("\n");
	for(i=0;i<95;i++) printf("%c", A->ciph[i]);
	printf("\n");
}
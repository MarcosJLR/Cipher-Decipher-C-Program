#include "cipher.h"

typedef int bool;
#define true 1
#define false 0

Cipher *mkCipher(long dt, char *natural, char *encrypted){
    Cipher *newCipher = malloc(sizeof (Cipher));
    int i;
    for(i=0;i<96;i++){
    	newCipher->ciph[i] = newCipher->deciph[i] = '#';
    }
    int n=sizeof(natural)/sizeof(natural[0]);
    for(i=0;i<n;i++){
    	newCipher->ciph[natural[i]-32]=encrypted[i];
    	newCipher->deciph[encrypted[i]-32]=natural[i];
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
	a=&(A->ciph[0]);
	b=&(B->ciph[0]);
	for(i=0;i<96 && (*(a+i)=='#' || *(b+i)=='#' || *(a+i)==*(b+i));i++);
	if(i==96) return true;
	else return false;
}
bool mergeCipher(Cipher *A, Cipher *B){
	bool c=isCompatible(A,B);
	char *a,*b;
	a=&(A->ciph[0]);
	b=&(B->ciph[0]);
	if(!c) return false;
	for(int i=0;i<96;i++){
		if(*(a+i)=='#' && *(b+i)!='#'){
			*(a+i)=*(b+i);
		}
		else if(*(a+i)!='#' && *(b+i)=='#'){
			*(b+i)=*(a+i);
		}
	}
	return true;
}
bool encrypt(Cipher *A, char *s){
	char c;
	bool uncyph=true;
	char *a;
	a=&(A->ciph[0]);
	for(int i=0; *(s+i)!='\0'; i++){
		c=*(a+*(s+i)-32);
		if(c=='#'){
			uncyph=false;
			*(s+i)='#';
		}
		else *(s+i)=c;
	}
	return uncyph;
}
bool decrypt(Cipher *A, char *s){
	char c;
	bool uncyph=true;
	char *a;
	a=&(A->deciph[0]);
	for(int i=0; *(s+i)!='\0'; i++){
		c=*(a+*(s+i)-32);
		if(c=='#'){
			uncyph=false;
			*(s+i)='#';
		}
		else *(s+i)=c;
	}
	return uncyph;
}

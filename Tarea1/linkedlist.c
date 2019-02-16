#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

Pnode mkNode(Cipher *data){
    Pnode newNode = malloc(sizeof (Node));
    newNode->prv = newNode->nxt = NULL;
    newNode->data = data;
    return newNode;
}

List *mkList(){
    List *newList = malloc(sizeof (List));
    newList->fst = newList->lst = NULL;
    newList->sz = 0;
    return newList;
}

int askUser(Cipher *A, Cipher *B){
    int ret = 0;
    while(ret<1 || ret>3){
        printf("El esquema que desea insertar coincide con los esquemas de fecha:\n");
        printf("Que desea hacer?\n");
        printf("1. Agregarlo al esquema anterior");
        printf("2. Crear un nuevo esquema");
        printf("3. Agregarlo al esquema siguiete");
        scanf("%d", &ret);
        if(ret<1 || ret>3) printf("Entrada invalida!\nIntente de nuevo\n");
    }
    return ret;
}

int insertBetween(Pnode A, Pnode B, Pnode C){

    if(isSameDate(A->data, B->data))
        return (mergeCipher(A->data, B->data)) ? 0 : -1;

    if(isSameDate(C->data, B->data))
        return (mergeCipher(C->data, B->data)) ? 0 : -1;

    if(isCompatible(A->data, B->data) && isCompatible(B->data, C->data)){
        int op = askUser(A->data, C->data);
        if(op == 1) {
            mergeCipher(A->data, B->data);
            free B;
            return 0;
        }
        if(op == 3){
            mergeCipher(C->data, B->data);
            free B;
            return 0;
        }
        A->nxt = B, C->prv = B, B->prv = A, B->nxt = C;
        return 1;
    }
    if(!isCompatible(A->data, B->data) && !isCompatible(B->data, C->data)){
        A->nxt = B, C->prv = B, B->prv = A, B->nxt = C;
        return 1;
    }
    if(isCompatible(A->data, B->data)){
        mergeCipher(A->data, B->data);
        free B;
        return 0;
    }
    if(isCompatible(B->data, C->data)){
        mergeCipher(C->data, B->data);
        free B;
        return 0;
    }
}

bool listInsert(List *L, Cipher *data){
    Pnode N = mkNode(data);
    if(L->sz == 0){
        L->fst = L->lst = N;
        L->sz++;
        return true;
    }

    Pnode it = L->fst;
    if(isBefore(data, it->data)){
        if(mergeCipher(it->data, data)) free N;
        else{
            it->prv = N, N->nxt = it, L->fst = N;
            L->sz++;
        }
        return true;
    }

    while(it->nxt != NULL && isBefore(it->nxt->data, data)) it = it->nxt;
    
    if(it->nxt == NULL){
        if(isSameDate(it->data, data))
            return mergeCipher(it->data, data);
        if(mergeCipher(it->data, data)) free N;
        else{
            it->nxt = N, N->prv = it, L->lst = N;
            L->sz++;
        }
        return true;
    }

    int aux = insertBetween(it, N, it->nxt);
    if(aux != -1) L->sz += aux;
    return aux != -1;
}

int main(){

    
    return 0;
}
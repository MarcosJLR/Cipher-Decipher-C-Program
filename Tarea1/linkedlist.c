#include "linkedlist.h"

typedef int bool;
#define true 1
#define false 0

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
        printf("\nEl esquema que desea insertar coincide con los esquemas de fecha:\n");
        int d, m, y;
        intToDate(A->date, &d, &m, &y);
        printf("-- %02d/%02d/%04d\n", d, m, y);
        intToDate(B->date, &d, &m, &y);
        printf("-- %02d/%02d/%04d\n", d, m, y);

        printf("\nQue desea hacer?\n");
        printf("1. Agregarlo al esquema anterior\n");
        printf("2. Crear un nuevo esquema\n");
        printf("3. Agregarlo al esquema siguiente\n");
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
            free(B);
            return 0;
        }
        if(op == 3){
            mergeCipher(C->data, B->data);
            free(B);
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
        free(B);
        return 0;
    }
    if(isCompatible(B->data, C->data)){
        mergeCipher(C->data, B->data);
        free(B);
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
        if(mergeCipher(it->data, data)) free(N);
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
        if(mergeCipher(it->data, data)) free(N);
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

bool listDelete(List *L, long dt){
    Pnode it = L->fst;
    while(it && it->data->date != dt)
        it = it->nxt;

    if(!it) return false;
    
    if(it->nxt)
        it->nxt->prv = it->prv;
    if(it->prv)
        it->prv->nxt = it->nxt;
    if(!it->prv)
        L->fst = it->nxt;
    if(!it->nxt)
        L->lst = it->prv;
    
    L->sz--;
    free(it);
    return true;
}

bool listDecrypt(List *L, long dt, char *s){
    if(L->sz == 0 || dt < L->fst->data->date){
        fprintf(stderr, "No hay esquemas de cifrado para esa fecha.\n");
        return false;
    }
    Pnode it = L->fst;
    while(it->nxt != NULL && it->nxt->data->date < dt) it = it->nxt;
    if(!decrypt(it->data, s))
        printf("No se pudo descifrar todo el mensaje.\n");
    return true;
}

bool listEncrypt(List *L, long dt, char *s){
    if(L->sz == 0 || dt < L->fst->data->date){
        fprintf(stderr, "No hay esquemas de cifrado para esa fecha.\n");
        return false;
    }
    Pnode it = L->fst;
    while(it->nxt != NULL && it->nxt->data->date < dt) it = it->nxt;
    if(!encrypt(it->data, s))
        printf("No se pudo cifrar todo el mensaje.\n");
    return true;
}

/*void printList(List *L){
    Pnode it = L->fst;
    printf("L: ");
    while(it){
        printf("(%ld, %d) ", it->data->date,it->data->x);
        it = it->nxt;
    }
    printf("\n");
}*/

/*int main(){

    long dt;
    int x,op;
    List *L = mkList(); 
    while(1){
        scanf("%d", &op);
        if(op){
            scanf("%ld %d", &dt, &x);
            Cipher *C = mkCipher(dt, x);
            if(!listInsert(L, C)) fprintf(stderr, "La cagaste joyita!\n");
        }
        else{
            scanf("%ld",&dt);
            if(!listDelete(L, dt)) fprintf(stderr, "No habia nada en esa fecha\n");
        }
        printList(L);
    }
    
    return 0;
}
*/
#include "linkedlist.h"

typedef int bool;
#define true 1
#define false 0

// Crea un nodo y retorna un apuntador a el
Pnode mkNode(Cipher *data){
    Pnode newNode = malloc(sizeof (Node));
    newNode->prv = newNode->nxt = NULL;
    newNode->data = data;
    return newNode;
}

// Elimina un nodo y libera la memoria
void nodeDelete(Pnode N){
    if(!N) return;
    if(N->data) free(N->data);
    free(N);
}

// Crea una nueva lista
List *mkList(){
    List *newList = malloc(sizeof (List));
    newList->fst = newList->lst = NULL;
    newList->sz = 0;
    return newList;
}

// Pregunta al usuario en cual esquema se debe insertar
// En caso de insertar un esquema que sea consistente con
// el esquema anterior y con el siguiente (segun fecha)
// Se escoge entre agragar al anterior, al siguiente
// o crear un nuevo esquema en medio.
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


// Inserta el nodo B entre el nodo A y el nodo C
// Si es compatible con solo uno de los adyacentes
// se unen los esquemas y se toma la menor fecha
// Si no es compatible con ninguno se crea un nuevo esquema
// Si es compatible con los dos adyacentes se pregunta al 
// usuatio que hacer
// Retorna 1 si se creo un nuevo esquema, 0 si se unio con otro
// y -1 si hay dos elementos en la misma fecha incompatibles
int insertBetween(Pnode A, Pnode B, Pnode C){
    // Misma fecha que A
    if(isSameDate(A->data, B->data))
        return (mergeCipher(A->data, B->data)) ? 0 : -1;

    // Misma fecha que B
    if(isSameDate(C->data, B->data))
        return (mergeCipher(C->data, B->data)) ? 0 : -1;

    // Compatible con ambos
    if(isCompatible(A->data, B->data) && isCompatible(B->data, C->data)){
        int op = askUser(A->data, C->data);
        // Unir al anterior
        if(op == 1) {
            mergeCipher(A->data, B->data);
            nodeDelete(B);
            return 0;
        }
        // Unir al siguiente
        if(op == 3){
            mergeCipher(C->data, B->data);
            nodeDelete(B);
            return 0;
        }
        // Crear nuevo esquema
        A->nxt = B, C->prv = B, B->prv = A, B->nxt = C;
        return 1;
    }
    // No es compatible con ninguno
    if(!isCompatible(A->data, B->data) && !isCompatible(B->data, C->data)){
        A->nxt = B, C->prv = B, B->prv = A, B->nxt = C;
        return 1;
    }
    // Compatible con el anterior
    if(isCompatible(A->data, B->data)){
        mergeCipher(A->data, B->data);
        nodeDelete(B);
        return 0;
    }
    // Compatiblo con el siguiente
    if(isCompatible(B->data, C->data)){
        mergeCipher(C->data, B->data);
        nodeDelete(B);
        return 0;
    }
}

// Inserta en L el esquema data
// Mantiene la lista ordenada por fecha
// Retorna true si todo salio bien, false si no
bool listInsert(List *L, Cipher *data){
    Pnode N = mkNode(data);
    if(L->sz == 0){
        L->fst = L->lst = N;
        L->sz++;
        return true;
    }

    // iterador para la lista
    Pnode it = L->fst;
    
    // Va de primero
    if(isBefore(data, it->data)){
        if(mergeCipher(it->data, data)) nodeDelete(N);
        else{
            it->prv = N, N->nxt = it, L->fst = N;
            L->sz++;
        }
        return true;
    }

    // Buscar hasta encontrar una fecha mayor
    while(it->nxt != NULL && isBefore(it->nxt->data, data)) it = it->nxt;
    
    // Va de ultimo
    if(it->nxt == NULL){
        if(isSameDate(it->data, data))
            return mergeCipher(it->data, data);
        if(mergeCipher(it->data, data)) nodeDelete(N);
        else{
            it->nxt = N, N->prv = it, L->lst = N;
            L->sz++;
        }
        return true;
    }

    // Va en el medio
    int aux = insertBetween(it, N, it->nxt);
    if(aux != -1) L->sz += aux;
    return aux != -1;
}

// Borra el elemtno con fecha dr de la lista L
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
    nodeDelete(it);
    return true;
}

// Descifra el mensaje en s segun el el esquema de cifrado mas
// reciente antes de la fecha dt.
// Retorna false si no existe un esquema de cifrado para esa fecha
bool listDecrypt(List *L, long dt, char *s){
    if(L->sz == 0 || dt < L->fst->data->date){
        fprintf(stderr, "No hay esquemas de cifrado para esa fecha.\n");
        return false;
    }
    Pnode it = L->fst;
    while(it->nxt != NULL && it->nxt->data->date <= dt) it = it->nxt;
    if(!decrypt(it->data, s))
        printf("No se pudo descifrar todo el mensaje.\n");
    return true;
}

// Cifra el mensaje en s segun el el esquema de cifrado mas
// reciente antes de la fecha dt.
// Retorna false si no existe un esquema de cifrado para esa fecha
bool listEncrypt(List *L, long dt, char *s){
    if(L->sz == 0 || dt < L->fst->data->date){
        fprintf(stderr, "No hay esquemas de cifrado para esa fecha.\n");
        return false;
    }
    Pnode it = L->fst;
    while(it->nxt != NULL && it->nxt->data->date <= dt) it = it->nxt;
    if(!encrypt(it->data, s))
        printf("No se pudo cifrar todo el mensaje.\n");
    return true;
}

// Imprime el mensaje de cifrado activo para una fecha dada
// Retorna false si no hay esquemas de cifrado en la lista para
// dicha fecha.
bool listPrintCipher(List *L, long dt){
    if(L->sz == 0 || dt < L->fst->data->date){
        fprintf(stderr, "No hay esquemas de cifrado para esa fecha.\n");
        return false;
    }
    Pnode it = L->fst;
    while(it->nxt != NULL && it->nxt->data->date <= dt) it = it->nxt;
    printCipher(it->data);
    return true;
}

// Imprime las fechas de inicio de los esquemas de cifrado en la lista.
void printListDates(List *L){
    Pnode it = L->fst;
    printf("\nFechas de esquemas:\n");
    int d, m, y;
    while(it){
        intToDate(it->data->date, &d, &m, &y);
        printf("-- %02d/%02d/%04d\n", d, m, y);
        it = it->nxt;
    }
    printf("\n");
}

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
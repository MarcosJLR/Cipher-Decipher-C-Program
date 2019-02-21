/* 
    Implementacion de una lista enlazada de esquemas de cifrado.
    Escrito por: Marcos Lerones y Nicolas Jaua
*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stddef.h>
#include "cipher.h"

typedef int bool;
#define true 1
#define false 0

// Estructura para un nodo de la lista
// Contiene un apuntador al siguiente nodo y un apuntador al nodo 
// anterior y un apuntador al esquema de cifrado que representa
typedef struct listnode *Pnode;
typedef struct listnode{
    Cipher *data;
    Pnode prv;
    Pnode nxt;
} Node;

// Estructura para la lista
// Contiene el tamaño de la lista, y apuntadores al primer y ultimo nodo
typedef struct linkedlist{
    size_t sz;
    Pnode fst;
    Pnode lst;
} List;

// Crea un nodo de la lista
Pnode mkNode(Cipher *data);

// Crea una nueva lista
List *mkList();

// Inserta un esquema de cifrado en la lista, manteniendola ordenada.
// Retorna false si el esquema a insertar no es consistente con uno 
// de la misma fecha.
bool listInsert(List *L, Cipher *data);

#endif
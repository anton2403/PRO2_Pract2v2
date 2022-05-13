/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practica 2
 * AUTHOR 1: Ruben Seoane Iglesias LOGIN 1: r.seoane.iglesias
 * AUTHOR 2: Anton Lopez Nunez LOGIN 2: anton.lopez.nunez
 * GROUP: *2.4*
 * DATE:  29/04/2022
 */

#ifndef BID_STACK_H
#define BID_STACK_H

#include "types.h"

#include <stdbool.h>
#define SNULL -1
#define SMAX 25

typedef struct {
    tUserId bidder;
    tProductPrice productPrice;
} tItemS; //Declaramos el tipo tItemS,

typedef int tPosS;

typedef struct stack {
    tItemS data [SMAX];
    tPosS top;
} tStack;

void createEmptyStack (tStack *stack);
/*
 Objetivo: Crear una pila vacia e inicializarla
 Entradas:
    Stack: Una pila tipo tStack
 Salidas:
    Stack: Pila inicializada
 Postcondiciones: La pila no tiene elementos
 */
bool push (tItemS d, tStack *stack);
/*
 Objetivo: Inserta un elemento encima de la pila.
           Devuelve un valor True si el elemento fue apilado, y un valor False en caso contrario
 Entradas:
    Item: Contenido del elemento a insertar (variable d tipo tItemS)
    Stack: Pila donde vamos a insertar
 Salidas:
    Stack: Pila con el elemento Item insertado
    Bool: Devuelve verdadero si se ha podido insertar, falso en caso contrario.
 Precondiciones: La pila está inicializada
 */
void pop (tStack *stack);
/*
 Objetivo: Elimina de la pila el elemento situado en la cima.
 Entradas:
    Stack: Pila donde se va a eliminar el elemento (Por referencia, para que se mantengan los cambios)
 Salidas:
    Stack: Pila sin el elemento que acabamos de eliminar
 Precondiciones: La pila esta inicializada y no esta vacia
 */
tItemS peek (tStack stack);
/*
 Objetivo: Recupera el elemento de la cima de la pila sin eliminarlo
 Entradas:
    Stack: Pila de la cual vamos a recuperar el elemento
 Salidas:
    Item: Elemento que hemos recuperado de la cima de la pila
 Precondiciones: La pila esta inicializada y no esta vacia
 */
bool isEmptyStack (tStack stack);
/*
 Objetivo: Determina si una pila esta vacia o no
 Entradas:
    Stack: Pila que queremos analizar
 Salidas:
    Bool: Devuelve verdadero si la pila esta vacia, falso si no lo esta.
 Precondiciones: La pila esta inicializada
 */

#endif

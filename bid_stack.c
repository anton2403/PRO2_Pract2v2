/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practica 2
 * AUTHOR 1: Ruben Seoane Iglesias LOGIN 1: r.seoane.iglesias
 * AUTHOR 2: Anton Lopez Nunez LOGIN 2: anton.lopez.nunez
 * GROUP: *2.4*
 * DATE:  29/04/2022
 */

#include "bid_stack.h" //Incluimos el .h

void createEmptyStack (tStack *stack) {
    stack->top = SNULL; //Inicializa el elemento en la cima a nulo
}

bool isEmptyStack (tStack stack) {
    return (stack.top == SNULL); //Devuelve verdadero si stack.top == SNULL y falso si no
}

tItemS peek (tStack stack) { //Consultar la cima de la pila
    return stack.data[stack.top]; //Devuelve el campo data correspondiente a stack.top, que es el índice del primer elemento de la lista
}

void pop (tStack *stack) { //Elimina el primer elemento
    stack->top--;//Cambiamos top de sitio (no hace falta borrar, en los arrays se sobreescribe)
}

bool push (tItemS d, tStack *stack) {
    if (stack->top == SMAX-1) //Top ya está ariba (no podemos insertar mas)
        return false; //Devolvemos falso
    else { //Si no
        stack->top ++; //Movemos el top una posicion
        stack->data[stack->top] = d; //Insertamos d en el nuevo top, que corresponde al indice anterior al que acabamos de mover
        return true; //Devolvemos verdadero
    }
}
/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practica 2
 * AUTHOR 1: Ruben Seoane Iglesias LOGIN 1: r.seoane.iglesias
 * AUTHOR 2: Anton Lopez Nunez LOGIN 2: anton.lopez.nunez
 * GROUP: *2.4*
 * DATE:  29/04/2022
 */

#include <string.h>
#include "product_list.h"

void createEmptyList (tList *L){ //Cabecera de la función. Recibe la lista como variable dinámica, para que se guarden los cambios que realicemos
    *L = LNULL; //Inicializamos la lista a LNULL porque esta vacia
}

bool isEmptyList (tList L){ //Cabecera de la función. Recibe la lista y, como no la va a modificar, no la recibe como variable dinamica
    return (L == LNULL); //Si el primer elemento es nulo (La lista está vacía), devuelve verdadero. Si no, devuelve falso
}

tPosL first (tList L){ //Cabecera de la función. Recibe la lista y, como no la va a modificar, no la recibe como variable dinamica
    return L; //Devuelve la posicion del primer elemento
}

tPosL next (tPosL p, tList L){ //Cabecera de la función. Recibe la posicion de la que se quiere el siguiente y la lista
    return p->next; //Devuelve el siguiente a p
}

tPosL last (tList L){ //Cabecera de la función. Recibe la lista
    tPosL p; //Creamos una variable local tipo tPosL para recorrer la lista
    for (p = L; p->next != NULL; p=p->next); //Recorremos la lista hasta el ultimo elemento; p=L equivale a first(L). Y p=p->next equivale a next (p,L)
    return p; //Devolvemos la posicion del ultimo elemento
}

tPosL previous (tPosL p, tList L){ //Cabecera de la función. Recibe la posicion de la que se quiere la anterior y la lista
    tPosL q; //Creamos una variable local de tipo tPosL para recorrer la lista
    if (L==p) { //Si la posicion dada corresponde al primer elemento
        return LNULL; //Devolvemos LNULL
    } else { //Si no corresponde al primer elemento:
        q=L; //q=primer elemento de la lista
        while (q->next != p) //Mientras el siguiente de q sea distinto de p
            q = q->next; //q = siguiente de q
        return q; //Devolvemos q
        /*for(q=L; q->next != p; q=q->next);
        return q;*/
    }
}

bool createNode (tPosL *p){ //Cabecera de la función. Recibe la posición donde crear el nodo
    *p= malloc(sizeof(**p)); //Reservamos memoria para el nodo
    return *p != LNULL; //Devolvemos true si se creo el nodo correctamente y false si no se pudo crear
}

tPosL findPosition (tList L, tItemL d) {
    tPosL p; //Creamos una variable local para recorrer la lista
    p=L; //equivale a p=first(L);
    while (p->next!=LNULL && (strcmp(d.productId,p->next->data.productId) > 0)) //Mientras que el siguiente de p sea distinto de nulo (no sea el final de la lista) y d.productId sea > que el productId del siguiente a p
        p=p->next; //p igual a su siguiente. Equivale a p=next(p,L). Si no tiene siguiente (es el ultimo elemento), se le asigna el valor nulo
    return p; //Devolvemos la posicion de p
}

bool insertItem (tItemL d, tList *L) {
    tPosL p, q;//Una va a servir para crear el nodo, otra para
    if (!createNode(&q)) //Si no se puede crear el nodo
        return false; //Devolvemos falso porque no se puede insertar el Item d
    else { //Si no:
        q->data = d; //Asignamos a la variable "data" del nodo al que apunta q el valor de d
        q->next = LNULL; //Asignamos a la variable "next" del nodo al que apunta q el valor de LNULL
        if (*L==LNULL) { //Tambien vale *L = last(L). Si la lista esta vacía
            *L = q; //Insertamos al principio
        } else if (strcmp(d.productId,(*L)->data.productId)<0) { //Si el campo productId de d es menor que el campo productId de *L. Insertamos
            q->next = *L; //El siguiente de q es *L
            *L = q;
        } else {
            p = findPosition(*L, d); //Asignamos a p la posicion de d
            q->next = p->next; //Asignamos a la posicion siguiente de q la siguiente de p
            p->next = q; //Asignamos a la posicion siguiente de p q
        }
        return true; //Devolvemos cierto porque se pudo insertar el item
    }
}

void deleteAtPosition (tPosL p, tList *L){ //Cabecera de la función. Recibe la posicion del elemento a eliminar y la lista donde se encuentra como variable dinamica (Porque se va a modificar y queremos que se mantengan los cambios tras acabar la funcion)
    tPosL q; //Creamos una variable local tipo tPosL para recorrer la lista
    if(*L==p){ //Si p = primer valor de la lista
        *L = p->next; //Asigna a L el valor del que le sucede en la lista
    } else if (p->next == LNULL){ //Si el siguiente es nulo, p nulo (Estamos insertando el elemento al final)
        for(q=*L; q->next != p; q=q->next); //desde el primer elemento hasta que el siguiente de q sea igual a p, sigue
        q->next = LNULL; //Asignamos al siguiente de q el valor LNULL
    } else { //Si el siguiente no es nulo (Estamos insertando por el medio de la lista)
        q = p->next; //q = siguiente de p
        p->data = q->data; //Asignamos al campo "data" l nodo al que apunta  p el valor del campo "data" del nodo al que apunta q
        p->next = q->next; //Asignamos al siguiente de p el siguiente de q
        p = q; //p igual a q
    }
    free(p); //Liberamos la memoria ocupada por p
}

tItemL getItem (tPosL p, tList L){ //Cabecera de la función. Recibe la posicion del elemento que se quiere y la lista donde se encuentra
    return p->data; //Devolvemos el contenido del campo "data" del elemento que se encuentra el la posicion p
}

void updateItem (tItemL d, tPosL p, tList *L){ //Cabecera de la función. Recibe el valor del item a actualizar, la posicion del item que se quiere actualizar y la lista donde se encuentra dicho item (como variable dinamica, Porque se va a modificar la lista y queremos que se mantengan los cambios al acabar la funcion)
    p->data = d; //Actualizamos el campo "data" del item que se encuentra en la posicion p, con los valores de d
}

tPosL findItem (tProductId d, tList L) {
    tPosL p; //Creamos una variable tipo tPosL para recorrer la lista
    for (p=L; (p!=LNULL) && (strcmp(p->data.productId,d)<0); p=p->next); //Desde el prinicpio de la lista (p=L) hasta que p sea distinto de nulo y d sea mayor que p->data.productId, p = siguiente de p
    if (p!=LNULL && strcmp(p->data.productId,d) == 0) //Paramos en mitad de la lista porque encontramos el dato
        return p; //Devolvemos p
    else //LLegamos al final de la lista y no lo encontramos
        return LNULL; //Devolvemos nulo
}
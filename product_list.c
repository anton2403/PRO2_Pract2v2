/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Ruben Seoane Iglesias LOGIN 1: r.seoane.iglesias
 * AUTHOR 2: Anton Lopez Nunez LOGIN 2: anton.lopez.nunez
 * GROUP: *2.4*
 * DATE:  /  /
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
    for (p = L; p->next != NULL; p=p->next); //Recorremos la lista hasta el ultimo elemento;p=L equivale a first(L). Y p=p->next equivale a next (p,L)
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
    tPosL p;
    p=L; //Tambien vale p=first(L)
    while (p!=LNULL && p->data<d)
        p=p->next; //Equivale a p=next(p,L)
    return p;
}

bool insertItem (tItemL d, tList *L) {
    tPosL p, q, r;//Una va a servir para crear el nodo, otra
    if (!createNode(&q))
        return false;
    else {
        q->data = d;
        q->next = LNULL;
        if (*L==LNULL) { //Tambien vale *L = last(L)
            *L = q;
        } else if (d<(*L)->data) {
            q->next = *L;
            *L = q;
        } else {
            p = findPosition(*L, d);
            if (p == LNULL)
                for(r = *L; r->next != LNULL; r=r->next)
                    r->next = q;
        }
        q->data = p->data;
        p->data = d;
        q->next = p->next;
        p->next = q;
    }
    return true;
/*bool insertItem (tItemL d, tPosL p, tList *L) { //Cabecera de la función. Recibe el item a insertar, la posicion donde insertarlo y la lista donde insertarlo (como variable dinamica (Porque se va a modificar y queremos que se mantengan los cambios tras acabar la funcion))
    tPosL q, r; //Creamos variables locales. Punteros a un nodo
    if (!createNode(&q)) //Si no se pudo crear el nodo
        return false; //Devolver falso
    else { //Si se pudo crear el nodo
        q->data = d; //Introducimos el valor dado (d) en el campo "data" del nodo (struct) al que apunta q
        q->next = LNULL; //Asignamos al campo "next" de q el valor LNULL
        if (*L == LNULL) //Si el primer valor de la lista es LNULL
            *L = q; //Asignamos el valor de q a *L
        else if (p == LNULL) { //Si p es igual a LNULL
            r = *L; //
            while (r->next != LNULL) { //Mientras el siguiente de r sea distinto de LNULL:
                r = r->next; //Avanzamos en la lista
            }
            r->next = q; //Asignamos al siguiente de r, el valor de q
        } else if (p == *L) { //Si p es igual al primer valor de la lista
            q->next = *L;
            *L = q;
        } else {
            q->data = p->data;
            p->data = d;
            q->next = p->next;
            p->next = q;
        }
    }
    return true; //Devolvemos cierto (se inserto correctamente)
}*/
}

void deleteAtPosition (tPosL p, tList *L){ //Cabecera de la función. Recibe la posicion del elemento a eliminar y la lista donde se encuentra como variable dinamica (Porque se va a modificar y queremos que se mantengan los cambios tras acabar la funcion)
    tPosL q; //Creamos una variable local tipo tPosL para recorrer la lista
    if(*L==p){ //Si p = primer valor de la lista
        *L = p->next; //Asigna a L el valor del que le sucede en la lista
    } else if (p->next == LNULL){ //Si el siguiente es nulo, p nulo (Estamos insertando el elemento al final) !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        for(q=*L; q->next != p; q=q->next); //desde el primer elemento hasta que el siguiente de q sea igual a p, sigue
        q->next = LNULL;
    } else { //Si el siguiente no es nulo
        q = p->next; //q = siguiente de p
        p->data = q->data; //Asignamos a p el valor del campo "data" del nodo al que apunta q
        p->next = q->next; //Asignamos a p el siguiente de q
        p = q; //p igual a q
    }
    free(p); //Liberamos la memoria ocupada por p
}

tItemL getItem (tPosL p, tList L){ //Cabecera de la función. Recibe la posicion del elemento que se quiere y la lista donde se encuentra
    return p->data; //Devolvemos el contenido del campo "data"
}

void updateItem (tItemL d, tPosL p, tList *L){ //Cabecera de la función. Recibe el valor del item a actualizar, la posicion del iten que se quiere actualizar y la lista donde se encuentra dicho item (como variable dinamica (Porque se va a modificar la lista y queremos que se mantengan los cambios tras acabar la funcion))
    p->data = d; //Actualizamos el campo "data" del item que se encuentra en la posicion p, con los valores de d
}

tPosL findItem (tItemL d, tList L) {
    tPosL p;
    for (p=L; (p!=LNULL) && (p->data<d); p=p->next);
    if (p!=LNULL && p->data==d) //Paramos en mitad de la lista porque encontramos el dato
        return p;
    else
        return LNULL;
/*tPosL findItem (tProductId d, tList L){ //Cabecera de la función. Recibe y la lista donde buscar el item
    tPosL p; //Creamos una variable local de tipo tPosL para recorrer la lista
    for (p=L; (p!=LNULL) && (strcmp(p->data.productId,d)!=0);p=p->next); //Recorremos la lista desde el principio, mientras p sea distinto de LNULL y el campo data de p no coincida con d
    return p; //Devuelve la posicion donde se encuentra el item (p).
}*/
}

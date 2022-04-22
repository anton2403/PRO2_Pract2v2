/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practica 2
 * AUTHOR 1: Ruben Seoane Iglesias LOGIN 1: r.seoane.iglesias
 * AUTHOR 2: Anton Lopez Nunez LOGIN 2: anton.lopez.nunez
 * GROUP: *2.4*
 * DATE:  29/04/2022
 */

#ifndef PRODUCT_LIST_H
#define PRODUCT_LIST_H

#include "types.h"
#include <stdlib.h>
#include <stdbool.h>

#define LNULL NULL

#include "types.h"
#include "bid_stack.h"

typedef struct tItemL {
    tUserId seller;
    tProductId productId;
    tProductCategory productCategory;
    tProductPrice productPrice;
    tBidCounter bidCounter;
    tStack bidStack;
} tItemL;

typedef struct tNode* tPosL;

struct tNode{
    tItemL data;
    tPosL next;
};

typedef tPosL tList; //Se añade para mantener la transparencia de la implementación (Para que funcione con cualquier implementación)

//Cabeceras de Funciones
void createEmptyList (tList *L);
/*
 Objetivo: Crea una lista vacia y la inicializa
 Salidas: Una lista vacia
 Postcondiciones: Lista queda inicializada y no contiene elementos
 */
bool isEmptyList (tList L);
/*
 Objetivo: Determina si la lista está vacia
 Entradas:
    List: Lista a comprobar
 Salidas:
    Verdadero si la lista esta vacia y falso en caso contrario
 Precondiciones: La lista debe estar inicializada
 */
tPosL first(tList L);
/*
 Objetivo: Devuelve la posición del primer elemento de la lista
 Entradas:
    List: Lista a manipular
 Salidas:
    Position: Posición del primer elemento
 Precondiciones: La lista está inicializada y no esta vacia
 */
tPosL last(tList L);
/*
 Objetivo: Devuelve la posición del ultimo elemento de la lista
 Entradas:
    List: Lista a manipular
 Salidas:
    Position: Posición del ultimo elemento
 Precondiciones: La lista está inicializada y no esta vacia
 */
tPosL next(tPosL p, tList L);
/*
 Objetivo: Devuelve la posición en la lista del elemento siguiente al de la posicion indicada (O LNULL si la posicion no
 tiene siguiente)
 Entradas:
    Position: Posicion del elemento actual
    List: Lista a manipular
 Salidas:
    Position: Posición del elemento siguiente o nulo si es el ultimo
 Precondiciones: La lista está inicializada y postion es una posicion valida de la lista
 */
tPosL previous(tPosL p, tList L);
/*
 Objetivo: Devuelve la posicion en la lista del elemento anterior al de la posicion indicada (o LNULL si no tiene anterior)
 Entradas:
    Position: Posicion del elemento actual
    List: Lista a manipular
 Salidas:
    Position: Posición del elemento anterior o nulo si es el primero
 Precondiciones: La lista está inicializada y position es una posicion valida de la lista
 */
bool insertItem (tItemL d, tList *L);
/*
 Objetivo: Inserta un elemento en la Lista de forma ordenada por el campo productId. Devuelve
           un valor True si el elemento fue insertado, False en caso contrario.
 Entradas:
    Item: Elemento a insetar
    List: Lista donde vamos a insertar
 Salidas:
    List: Lista con el elemento Item insertado
    Bool: Devuelve True si el elemento fue insertado, y devuelve False si no fue insertado
 Postcondiciones: Las posiciones de los elementos de la lista posteriores a la del elemento insertado pueden haber variado
 */
void deleteAtPosition (tPosL p, tList *L);
/*
 Objetivo: Elimina de la lista el elemento que ocupa la posición indicada
 Entradas:
    Position: Posicion del elemento a eliminar
    List: Lista a modificar
 Salidas:
    List: Lista sin el elemento correspondiente a Position
 Precondiciones: La posición indicada es una posición válida en la lista y el producto en dicha posición tiene una pila de pujas vacía
 Postcondiciones: Las posiciones de los elementos de la lista posteriores a la de la posición eliminada pueden haber variado
 */
tItemL getItem (tPosL p, tList L);
/*
 Objetivo: Recupera el contenido de un elemento de la lista
 Entradas:
    Position: Posicion del elemento buscado
    List: Lista donde realizar la busqueda
 Salidas:
    Item: Contenido del elemento que esta en Position
 Precondiciones: La lista está inicializada y position es una posicion valida de la lista
 */
void updateItem (tItemL d, tPosL p, tList *L);
/*
 Objetivo: Modifica el contenido de un elemento de la lista.
 Entradas:
    Item: Nuevo contenido a asignar al elemento en position
    Position: Posicion del elemento que queremos modificar
    List: Lista a modificar
 Salidas:
    List: Lista con el contenido del elemento modificado
 Precondiciones: La lista está inicializada y position es una posicion valida de la lista
 */
tPosL findItem (tProductId d, tList L);
/*
 Objetivo: Busca el primer elemento con cierto contenido en la lista
 Entradas:
    tProductId d: Contenido del elemento buscado
    List: Lista donde realizar la búsqueda
 Salidas:
    Position: Posición del elemento encontrado o nulo si no se encuentra
 Precondiciones: La lista está inicializada
 */
#endif
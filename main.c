/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practica 2
 * AUTHOR 1: Ruben Seoane Iglesias LOGIN 1: r.seoane.iglesias
 * AUTHOR 2: Anton Lopez Nunez LOGIN 2: anton.lopez.nunez
 * GROUP: *2.4*
 * DATE:  29/04/2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "bid_stack.h"
#include "product_list.h"

#define MAX_BUFFER 255
//Cabeceras
void deleteProduct (tPosL d, tList *L);

void new (char *param1, char *param2, char *param3, char *param4, tList *L);
void stats (tList L);
void bid (char *position, char *param2, char *preciopuja, tList *L);
void delete (char *param1, tList *L);
void award (char *param1, tList *L);
void withdraw (char *param1, char *param2, tList *L);

void deleteProduct (tPosL d, tList *L) { //Esta funcion elimina un producto tras vaciar su pila
    tItemL Item = getItem (d, *L);

    while(isEmptyStack(Item.bidStack)==false) //Mientras la pila de pujas no este vacia
        pop (&Item.bidStack); //Borrar el elemento de la cima

    updateItem(Item, d, L); //Actualizamos el Item con la pila de pujas vacia
    deleteAtPosition(d, L); //Despues de vaciar la pila (con el while), eliminamos el elemento
}

void new (char *param1, char *param2, char *param3, char *param4, tList *L) { //Cabecera de la función. Recibe el identificador del nuevo producto (param1), el vendedor del producto (param2), la categoría (param3) y el precio (param4)
    tItemL newItem;

    if (findItem(param1,*L)!=LNULL) { //Si existe un producto en la lista con ese identificador (param1), no podemos insertar otro
        printf("+ Error: New not possible\n"); //Imprimimos un error para indicar que no se completo la operacion
    } else {
        createEmptyStack (&newItem.bidStack); //Creamos una pila vacía en la variable newItem
        newItem.bidCounter = 0; //Inicializamos el contador de pujas a 0
        strcpy(newItem.seller, param2); //Copiamos el valor de param2 en el campo "seller" de la variable newItem
        strcpy(newItem.productId, param1); //Copiamos el valor de param1 en el campo "productId" de la variable newItem
        newItem.productPrice = atof(param4); //Pasamos el param4 (char) a float y lo cambiamos en el tItemL newItem, en el campo del precio
        if (strcmp(param3, "book")==0) //Si param3 es book, el campo "productCategory" pasa a ser book. Si no, pasa a ser "painting" que es el otro tipo posible
            newItem.productCategory = book;
        else
            newItem.productCategory = painting;

        if (insertItem(newItem, L) == false) //Insertamos el tItemL newItem con los valores correspondientes (con insertItem) y comprobamos su resultado para saber si se pudo insertar o no
            printf("+ Error: New not possible\n"); //Si insertItem devolvio falso, no se pudo insertar, entonces imprimimos un error para indicar que no se completo la operacion
        else //Si devuelve true
            printf("* New: product %s seller %s category %s price %s\n", param1, param2, param3, param4); //Imprimimos el mensaje correspondiente
    }
}

void stats (tList L) { //Cabecera de la función. Solo recibe la lista y no la va a modificar, solo a leerla
    tPosL i=0; //Creamos una variable tipo tPosL para recorrer la lista
    int countBook = 0, countPainting = 0; //countBook = contador numero de productos tipo book, countPainting = contador numero de productos tipo painting
    float avgBook, avgPainting, sumBook = 0, sumPainting = 0; //Creamos las variables necesarias para almacenar las operaciones que luego mostraremos
    //avgBook = precio medio de los productos tipo "book"; avgPainting = precio medio de los productos tipo "painting"; sumBook = suma de todos los precios de los productos tipo "book"; sumPainting = suma de todos los precios de los productos tipo "painting"
    float topIncrease = 0, increase = 0; //Creamos las variables para guardar el precio mas alto y una variable para almacenar el incremento del precio del producto
    tItemL topProduct; //Creamos una variable para almacenar el producto con el mayor incremento (precio original versus puja)
    tItemS topBidder; //Creamos una variable local para almacenar la puja mas alta

    if (isEmptyList(L)) { //Si la lista está vacia:
        printf("+ Error: Stats not possible\n"); //Imprimimos el mensaje de que la funcion no es realizable
    } else { //Si no esta vacia:
        for (i = first(L); i!=LNULL; i=next(i,L)) { //Recorremos la lista, desde el principio hasta el final
            tItemL item = getItem(i,L); //Cogemos
            // el elemento correspondiente a la posicion tPosL i y lo asignamos a la variable "item"
            if (item.bidCounter == 0) //Si la pila esta vacia (no hay ninguna puja hecha)
                if (item.productCategory == book) //Y la categoria es book
                    printf("Product %s seller %s category book price %.2f. No bids\n", item.productId, item.seller, item.productPrice);
                else //Si no es book, imprimimos el mismo mensaje cambiando la categoria por painting
                    printf("Product %s seller %s category painting price %.2f. No bids\n", item.productId, item.seller, item.productPrice);
            else { //Si la pila no esta vacia (hay pujas)

                topBidder = peek(item.bidStack); //Guardamos la puja mas alta en la variable topBidder
                if (item.productCategory == book) { //Si la categoria es book
                    printf("Product %s seller %s category book price %.2f bids %d top bidder %s\n", item.productId,
                           item.seller, item.productPrice, item.bidCounter, topBidder.bidder);
                } else //Si no es book, imprimimos el mismo mensaje cambiando la categoria por painting
                    printf("Product %s seller %s category painting price %.2f bids %d top bidder %s\n", item.productId,
                           item.seller, item.productPrice, item.bidCounter, topBidder.bidder);
                increase = (topBidder.productPrice - item.productPrice) * 100 / item.productPrice; //Almacenamos el incremento de los dos precios (puja mas alta con respecto al precio original)

                if (increase > topIncrease) { //Si el incremento del elemento que acabamos de leer (depende del for) es mayor que el que teníamos como el mas alto
                    topIncrease = increase; //El incremento que acabamos de leer pasa a ser el mas alto
                    topProduct = item; //Y el elemento que acabamos de leer pasa a ser el que tiene el mayor incremento
                }
            }

            if (item.productCategory == book) { //Si la categoria del item es "book":
                countBook = countBook + 1; //Aumentamos el numero de productos tipo "book" en una unidad
                sumBook = sumBook + item.productPrice; //Sumamos su precio al valor de la variable donde almacenaremos el precio total de todos los productos tipo "book"
            } else { //Si no es tipo "book" (como solo hay dos categorias, al no ser de tipo "book" nos esta diciendo implicitamente que es de tipo "painting"):
                countPainting = countPainting + 1; //Aumentamos el numero de productos tipo "painting" en una unidad
                sumPainting = sumPainting + item.productPrice; //Sumamos su precio al valor de la variable donde almacenaremos el precio total de todos los productos tipo "book"
            }
        }

        if (countBook == 0)//Si el numero de productos tipo "book" es 0:
            avgBook = 0; //El precio medio es automaticamente = 0; para evitar errores al dividir entre 0
        else avgBook = sumBook / countBook; //Si no es 0, el precio medio es igual a la suma de precios entre el numero de productos

        if (countPainting == 0)//Si el numero de productos tipo "painting" es 0:
            avgPainting = 0; //El precio medio es automaticamente = 0; para evitar errores al dividir entre 0
        else avgPainting = sumPainting / countPainting; //Si no es 0, el precio medio es igual a la suma de precios entre el numero de productos

        printf("\n"); //Hacemos un salto de linea para facilitar la legibilidad de la salida por pantalla
        printf ("Category  Products    Price  Average\n"); //Imprimimos las columnas de la tabla
        printf("Book      %8d %8.2f %8.2f\n", countBook, sumBook, avgBook); //Imprimimos, en orden: nº de productos que se ofertan de la categoria, la suma de precios de todos los productos de dicha categoría y precio medio
        printf("Painting  %8d %8.2f %8.2f\n", countPainting, sumPainting, avgPainting); //Lo mismo que en la de arriba pero para la categoria painting

        if (topIncrease == 0) //Si la pila de pujas está vacía
            printf("Top bid not possible\n");//Imprimimos el error
        else { //Si no esta vacia
            if (topProduct.productCategory == book) { //Y la categoria es book
                printf("Top bid: Product %s seller %s category book price %.2f bidder %s top price %.2f increase %.2f%%\n",
                       topProduct.productId, topProduct.seller, topProduct.productPrice, topBidder.bidder, peek(topProduct.bidStack).productPrice, topIncrease);
            } else //Si no es book, imprimimos el mismo mensaje cambiando la categoria por painting
                printf("Top bid: Product %s seller %s category painting price %.2f bidder %s top price %.2f increase %.2f%%\n",
                       topProduct.productId, topProduct.seller, topProduct.productPrice, topBidder.bidder, peek(topProduct.bidStack).productPrice, topIncrease);
        }
    }
}

void bid (char *position, char *param2, char *preciopuja, tList *L) { //Cabecera de la funcion bid que recibe: posicion del elemento, pujador, precio de la puja, la lista a la que accede
    tPosL r = findItem(position, *L); //Creamos una variable local que almacena la posicion del elemento con productId igual a "position"
    float price = atof (preciopuja); //Ccreamos una variable tipo float para el precio convertimos param4 (char) en un float y lo asignamos a la variable precio
    tItemS nuevaPuja; //Creamos una variable local para almacenar la nueva puja

    printf("B: product %s bidder %s price %.2f\n", position, param2, price); //Imprimimos la cabecera de la funcion

    if (r==LNULL) {
        printf("+ Error: Bid not possible\n"); //Imprime el mensaje de error
    } else {
        tItemL bidItem = getItem(r,*L); // Buscamos el item a modificar en la posicion dada (devuelve una copia del item)
        tItemS elementoCima = peek(bidItem.bidStack);

        if ( (strcmp(bidItem.seller, param2) == 0) || (price <= elementoCima.productPrice) || (bidItem.bidCounter == 25) )  { //Si no existe un producto con ese identificador,
            //el vendedor del producto es el mismo que el pujador, el precio de la puja no es superior a la puja mas alta o la pila estuviese llena, entonces:
            printf("+ Error: Bid not possible\n"); //Imprime el mensaje de error
        } else { //Si no se cumple ninguna de las condiciones anteriores:

            if ( (isEmptyStack(bidItem.bidStack) && (price > bidItem.productPrice)) || (!isEmptyStack(bidItem.bidStack) && (price > elementoCima.productPrice)) ) {
                //Si no hay pujas y la nueva puja supera al precio original o si hay pujas y la nueva puja supera a la puja mas alta, entonces
                strcpy(nuevaPuja.bidder, param2); //Añadimos el usuario que hizo la nueva puja
                nuevaPuja.productPrice = price; //Añadimos el precio de la nueva puja
                push(nuevaPuja, &bidItem.bidStack); //Guardamos la nueva puja
                bidItem.bidCounter ++; //actualizamos el contador de pujas
                updateItem(bidItem,r,L); //Actualizamos el item en el que añadimos la nueva puja y modificamos el contador de pujas

                if (bidItem.productCategory == book) //Si la categoria es book
                    printf("* Bid: product %s bidder %s category book price %.2f bids %d\n", bidItem.productId, nuevaPuja.bidder, nuevaPuja.productPrice, bidItem.bidCounter); // imprime el mensaje con categoria "book"
                else //Si no es book, imprimimos el mismo mensaje cambiando la categoria por painting
                    printf("* Bid: product %s bidder %s category painting price %.2f bids %d\n", bidItem.productId, nuevaPuja.bidder, nuevaPuja.productPrice, bidItem.bidCounter); // imprime el mensaje con categoria "painting"
            } else printf("+ Error: Bid not possible\n");
        }
    }

}

void delete (char *param1, tList *L) {
    tPosL r=0; //Creamos una variable local para localizar el elemento
    r = findItem(param1, *L); //Localizamos el item con tProductId = param1
    if (r!=LNULL) {
        tItemL Item = getItem (r, *L); //Almacenamos el item buscado en la variable Item de tipo tItemL
        deleteProduct(r, L); //Eliminamos el elemento tras vaciar su pila
        if (Item.productCategory == book) //Si la categoria es book
            printf("* Delete: product %s seller %s category book price %.2f bids %d\n", Item.productId, Item.seller, Item.productPrice, Item.bidCounter);
        else //Si no es book, imprimimos el mismo mensaje cambiando la categoria por painting
            printf("* Delete: product %s seller %s category painting price %.2f bids %d\n", Item.productId, Item.seller, Item.productPrice, Item.bidCounter);

    } else printf("+ Error: Delete not possible\n");
}

void award (char *param1, tList *L) {
    tPosL r; //Creamos una variable local para localizar el elemento
    tItemS TopPuja;
    float precioFinal=0;

    r = findItem(param1, *L); //Localizamos el item con tProductId = param1

    if (r==LNULL) {
        printf("+ Error: Award not possible\n");
    } else {
        tItemL Item = getItem(r, *L);
        if (!isEmptyStack(Item.bidStack)) {
            TopPuja = peek(Item.bidStack); //Almacenamos la puja mas alta
            precioFinal = TopPuja.productPrice; //Almacenamos el precio de la puja mas alta
            if (Item.productCategory == book) //Y la categoria es book
                printf("* Award: product %s bidder %s category book price %.2f\n", Item.productId, TopPuja.bidder, precioFinal); //Imprimimos el mensaje
            else //Si no es book, imprimimos el mismo mensaje cambiando la categoria por painting
                printf("* Award: product %s bidder %s category painting price %.2f\n", Item.productId, TopPuja.bidder, precioFinal); //Imprimimos el mensaje
            deleteProduct(r, L); //Eliminamos el elemento tras vaciar su pila
        } else printf("+ Error: Award not possible\n");
    }
}

void withdraw (char *param1, char *param2, tList *L) {
    tPosL pos = findItem(param1, *L);
    if (pos==LNULL) {
        printf("+ Error: withdraw not possible\n");
    } else {
        tItemL Item = getItem(pos, *L);
        tItemS topPuja = peek(Item.bidStack);
        if ( (isEmptyStack(Item.bidStack)) || (strcmp (param2, topPuja.bidder)!=0) )
            printf("+ Error: withdraw not possible\n");
        else {
            if (Item.productCategory == book) //Si la categoria es book
                printf("* Withdraw: product %s bidder %s category book price %.2f bids %d\n", Item.productId, topPuja.bidder, topPuja.productPrice, Item.bidCounter);
            else //Si no es book, imprimimos el mismo mensaje cambiando la categoria por painting
                printf("* Withdraw: product %s bidder %s category painting price %.2f bids %d\n", Item.productId, topPuja.bidder, topPuja.productPrice, Item.bidCounter);
            pop(&Item.bidStack);
            Item.bidCounter --;
            updateItem(Item, pos, L);
        }
    }

}

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4, tList *L) {
    printf("********************\n");
    printf("%s ", commandNumber);
    switch (command) {
        case 'N':
            printf("N: product %s seller %s category %s price %s\n", param1, param2, param3, param4); //Imprimimos la cabecera de la funcion new
            new (param1, param2, param3, param4, L);
            break;
        case 'S':
            printf("S\n"); //Imprimimos la cabecera de la funcion
            stats (*L);
            break;
        case 'B':
            bid (param1, param2, param3, L);
            break;
        case 'D':
            printf("D: product %s\n", param1);
            delete (param1, L);
            break;
        case 'A':
            printf("A: product %s\n", param1);
            award (param1, L);
            break;
        case 'W':
            printf("W: product %s bidder %s\n", param1, param2);
            withdraw (param1, param2, L);
            break;
        case 'R':

            break;
        default:

            break;
    }
}

void readTasks(char *filename, tList *lista01) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3, *param4;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);
            param4 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, param3, param4, lista01);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {

    tList lista01; //Creamos la variable lista01 de tipo tList
    createEmptyList(&lista01); //Creamos e inicializamos una lista vacia y la almacenamos en la variable lista01

    char *file_name = "withdraw.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name, &lista01);

    return 0;
}







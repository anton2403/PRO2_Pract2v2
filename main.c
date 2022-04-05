/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "bid_stack.h"
#include "product_list.h"

#define MAX_BUFFER 255
//Cabeceras
void new (char *param1, char *param2, char *param3, char *param4, tItemL *L);

void new (char *param1, char *param2, char *param3, char *param4, tItemL *L) { //Cabecera de la función. Recibe el identificador del nuevo producto (param1), el vendedor del producto (param2), la categoría (param3) y el precio (param4)
    tItemL newItem;

    if (findItem(param1,L)!=LNULL) { //Si existe un producto en la lista con ese identificador (param1), no podemos insertar otro
        printf("+ Error: New not possible\n"); //Imprimimos un error para indicar que no se completo la operacion
    } else {
        newItem.bidCounter = 0;
        strcpy(newItem.seller, param2); //Copiamos el valor de param2 en el campo "seller" del struct tItemL d
        strcpy(newItem.productId, param1); //Copiamos el valor de param1 en el campo "productId" del struct tItemL d
        if (strcmp(param3, "book")==0){ //el campo "productCategory" pasa a ser book. Si no, pasa a ser "painting" que es el otro tipo posible
            newItem.productCategory = book;
            printf("* New: product %s seller %s category book price %s\n", param1, param2, param4);
        } else {
            newItem.productCategory = painting; //Si param3 es de tipo book,
            printf("* New: product %s seller %s category painting price %s\n", param1, param2, param4);
        }
        newItem.productPrice = atof(param4); //Pasamos el param4 (char) a float y lo cambiamos en el tItemL d, en el campo del precio

        insertItem (newItem, L);//Insertamos el tItemL d con los valores correspondientes en la lista
    }
}


void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4, tItemL *L) {

    switch (command) {
        case 'N':
            new ( *param1,  *param2,  *param3,  *param4,  L);
            break;
        case 'S':
            break;
        case 'B':
            break;
        case 'D':
            break;
        case 'A':
            break;
        case 'W':
            break;
        case 'R':
            break;
        default:
            break;
    }
}

void readTasks(char *filename, lista01) {
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

    char *file_name = "new.txt";

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







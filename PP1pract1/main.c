#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "types.h"
#include "lib.h"
#include "../../ownLibC/screenSystemShow.h"
#include "../../ownLibC/userInputOutput.h"

#define QUANTITY 1000

#define HARDCODE 1 //([1] HABILITA LA CARGA DE DATOS DEFAULT, [0] DESHABILITA)

int main()
{
    int exit;
    int menu;
    Product article[QUANTITY];
    Suplier provider[QUANTITY];

    do  // SE REPITE LA ACCION DE INICIALIZAR EN CASO QUE ARTICLE SEA UN PUNTERO A NULL
    {
        exit = initializeEmptyFlagArray(article,provider,QUANTITY);
    }while(exit);


if(HARDCODE){/******************************************************************
*******************************************************************************/
//VALORES PARA HARDCODEAR LOS ELEMENTOS DE LOS ARRAYS
    int i;
    int auxSerialNumber[] = {1,2,3,4,5};
    int auxSerialSuplier[] = {21,22,23,24,25};
    char auxDescriptionArticle[][51] = {"JABON", "SOPA","LENTES","PANUELO","MOCO"};
    int auxAmount[] = {123,321,546,321,654};
    int auxStock[] = {1,5,6,7,8};
    //int auxSerialSuplier2[] = {31,32,31,34,31};
    char auxDescriptionProvider[][51] = {"FERRETERIA","AERONAUTICA","FARMACIA","ELECTRONICA","ROBOTICA"};
    int auxIsEmpty[] = {0,0,0,0,0};

    for (i=0 ; i<5 ; i++)
    {
//INICIALIZAR ARRAY ARTICLE
        article[i].serialNumber = auxSerialNumber[i];
        article[i].serialSuplier= auxSerialSuplier[i];
        strcpy(article[i].description,auxDescriptionArticle[i]);
        article[i].amount = auxAmount[i];
        article[i].stock = auxStock[i];
        article[i].isEmpty = auxIsEmpty[i];
//INICIALIZAR ARRAY PROVIDER
        provider[i].serialSuplier = auxSerialSuplier[i];
        strcpy(provider[i].description,auxDescriptionProvider[i]);
        provider[i].isEmpty = auxIsEmpty[i];
    }
/*******************************************************************************
*******************************************************************************/}

    do
    {
        printAwesomeMenu("1. ALTA DE PRODUCTO\n"
                         "2. MODIFICAR PRODUCTO\n"
                         "3. BAJA DE PRODUCTO\n"
                         "4. LISTADO DE PRODUCTOS\n"
                         "5. LISTADO COMPLETO\n"
                         "6. SALIR\n\n");
        getUserInputInt(&menu,1,6,"Ingrese la opcion deseada\n","Por favor, ingrese una opcion valida\n",0);
        exit = runFunctionMenu(menu,article,provider,QUANTITY);

    }while(exit);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "lib.h"
#include "../../ownLibC/screenSystemShow.h"
#include "../../ownLibC/userInputOutput.h"
#define QUANTITY 5

int main()
{
    int exit;
    int menu;
    Product article[QUANTITY];
    Suplier provider[QUANTITY];

    do
    {
        exit = initializeEmptyFlagArray(article,provider,QUANTITY);
    }while(exit);

//*******************************************************************************
//*******************************************************************************
        //HARDCODE
    int i;
    int auxSerialNumber[] = {1,2,3,4,5};
    int auxSerialSuplier[] = {21,22,23,24,25};
    char auxDescriptionArticle[][51] = {"JABON", "SOPA","LENTES","PANUELO","MOCO"};
    int auxAmount[] = {123,321,546,321,654};
    int auxStock[] = {1,5,6,7,8};
    int auxSerialSuplier2[] = {31,32,33,34,35};
    char auxDescriptionProvider[][51] = {"FERRETERIA","AERONAUTICA","FARMACIA","SUPERMERCADO","ALMACEN"};
    int auxIsEmpty[] = {0,0,0,0,0};

    for (i=0 ; i<QUANTITY ; i++)
    {
        //INICIALIZAR 1ER ESTRUCTURA
        article[i].serialNumber = auxSerialNumber[i];
        article[i].serialSuplier= auxSerialSuplier[i];
        strcpy(article[i].description,auxDescriptionArticle[i]);
        article[i].amount = auxAmount[i];
        article[i].stock = auxStock[i];
        article[i].isEmpty = auxIsEmpty[i];

        //INICIALIZAR 2DA ESTRUCTURA
        provider[i].serialSuplier = auxSerialSuplier2[i];
        strcpy(provider[i].description,auxDescriptionProvider[i]);
        provider[i].isEmpty = auxIsEmpty[i];
    }
//**************************************************************************
//**************************************************************************

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

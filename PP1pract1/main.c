#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "lib.h"
#include "../../ownLibC/screenSystemShow.h"
#include "../../ownLibC/userInputOutput.h"
#define QUANTITY 1000

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

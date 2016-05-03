#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "lib.h"
#include "../../ownLibC/screenSystemShow.h"
#include "../../ownLibC/userInputOutput.h"
#define QUANTITY 1000

#define ADD 1
#define MODIFY 2
#define DEL 3
#define LS_PRODUCT 4
#define LS_ALL 5
#define EXIT 6


/** \brief Ejecuta la opcion seleccionada por el usuario
 *
 * \param (menu) recibe el numero ingresado por el usuario
 * \param (article) array de productos
 * \param (lenght) longitud del array
 * \return 0 para salir del programa 1 para continuar
 *
 */

int runFunctionMenu(int menu, Product *article, Suplier *provider, int lenght)
{
    int ret = 1;

    switch(menu)
    {
        case ADD :
            cleanScreen();
            addArticle(article, provider, lenght);
            pauseScreen();
        break;

        case MODIFY :
            cleanScreen();
 //           modifyArticle(article, provider, lenght);
            pauseScreen();
        break;

        case DEL :
            cleanScreen();
 //           delArticle(article, provider, lenght);
            pauseScreen();
        break;

        case LS_PRODUCT :
            cleanScreen();
 //           listArticle(article, provider, lenght);
            pauseScreen();
        break;

        case LS_ALL :
            cleanScreen();
  //          listAll(article, provider, lenght);
            pauseScreen();
        break;

        case EXIT :
            ret = 0;
        break;
    }
    return ret;
}

/** \brief inicializa todos los campos de los elementos del array
 *
 * \param (article) array de productos
 * \param (provider) array de proveedores
 * \return 0 si funciono correctamente, -1 en caso que alguna direccion sea NULL o el largo menor que 1
 *
 */

int initializeEmptyFlagArray(Product *article,Suplier *provider,int length)
{
    int ret = -1;

    if(article != NULL && provider != NULL && length > 0)
    {
        int i;
        for(i=0 ; i<length ; i++)
        {
                article[i].serialNumber = -1;
                article[i].serialSuplier = -1;
                article[i].description[0] = '\0';
                article[i].amount = -1;
                article[i].stock = -1;
                article[i].isEmpty = 1;

                provider[i].description[0] = '\0';
                provider[i].serialNumber = -1;
                provider[i].isEmpty = 1;
        }
        ret = 0;
    }
    return ret;
}

int addArticle(Product *article, Suplier *provider,int lenght)
{
    int auxSerialNumber;
    int auxSerialSuplier;
    char auxDescription[51];
    int auxAmount;
    int flagValidSuplier = -1;
    int i;
    int index = 1;

    // HACER FORMULA PARA BUSCAR EL PRIMERO LIBRE

    getUserInputInt(&auxSerialNumber,0,QUANTITY,"Ingrese el codigo del producto\n","Por favor ingrese un codigo valido\n",0);
    do
    {
        getUserInputInt(&auxSerialSuplier,0,QUANTITY,"Ingrese el codigo del proveedor asociado\n","Por favor ingrese un codigo valido\n",0);
        for(i=0; i<QUANTITY; i++)
        {
            if(provider[i].serialNumber == auxSerialSuplier)
            {
                flagValidSuplier = 0;
            }
        }
        if(flagValidSuplier != 0)
        {
            printf("El proveedor no existe, por favor intentelo de nuevo");
            pauseScreen();
            return -1;
        }
    }while(flagValidSuplier);
    getUserInputString(&auxDescription,3,50,"Ingrese la descripcion del articulo\n","Por favor ingrese datos validos\n",4000,0);
    getUserInputInt(&auxAmount,0,10000,"Ingrese el importe del articulo\n","Por favor ingrese un importe valido\n",0);
    article[index].isEmpty = 0;
}

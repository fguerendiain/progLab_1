#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "lib.h"
#include "string.h"
#include "../../ownLibC/screenSystemShow.h"
#include "../../ownLibC/userInputOutput.h"
#define QUANTITY 5

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
            listArticle(article, lenght);
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
                article[i].amount = 0;
                article[i].stock = 0;
                article[i].isEmpty = 1;

                provider[i].description[0] = '\0';
                provider[i].serialSuplier = -1;
                provider[i].isEmpty = 1;
        }
        ret = 0;
    }
    return ret;
}

/** \brief Permite agregar un articulo
 *
 * \param (article) array de articulos
 * \param (provider) array de proveedores
 * \param (lenght) longitud de los arrays
 * \return 0 si los valores se cargaron correctamente
 *
 */

int addArticle(Product *article, Suplier *provider,int lenght)
{
    int auxSerialNumber;
    int auxSerialSuplier;
    char auxDescription[51];
    int auxAmount;
    int flagValidSuplier = -1;
    int i;
    int index = 1;

    index = searchFirstEmpty(provider,article,lenght,1);

    getUserInputInt(&auxSerialNumber,0,QUANTITY,"Ingrese el codigo del producto\n","Por favor ingrese un codigo valido\n",0);
    do
    {
        getUserInputInt(&auxSerialSuplier,0,QUANTITY,"Ingrese el codigo del proveedor asociado\n","Por favor ingrese un codigo valido\n",0);
        for(i=0; i<QUANTITY; i++)
        {
            if(provider[i].serialSuplier == auxSerialSuplier)
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
    getUserInputString(auxDescription,3,50,"Ingrese la descripcion del articulo\n","Por favor ingrese datos validos\n",4000,0);
    getUserInputInt(&auxAmount,0,10000,"Ingrese el importe del articulo\n","Por favor ingrese un importe valido\n",0);

    article[index].serialNumber = auxSerialNumber;
    article[index].serialSuplier = auxSerialSuplier;
    strcpy(article[index].description,auxDescription);
    article[index].amount = auxAmount;
    article[index].stock++;
    article[index].isEmpty = 0;

    return 0;
}

/** \brief busca el primer elemnto libre en los array article y provider
 *
 * \param (provider) array de proveedores
 * \param (article) array de articulos
 * \return devuelve el subindice buscado
 *
 */

int searchFirstEmpty(Suplier *provider, Product *article, int length, int arrayOption)
{
    int i;

    switch(arrayOption)
    {
        case 1 :
            for(i=0 ; i<length ; i++)
            {
                if(article[i].isEmpty == 0)
                    return i;
            }
        break;

        case 2 :
            for(i=0 ; i<length ; i++)
            {
                if(provider[i].isEmpty == 0)
                    return i;
            }
        break;
    }
}

int listArticle(Product *article, int length)
{
    int minStock;
    int maxStock;
    int minIndex;
    int maxIndex;
    int i;
    int j;

    minStock = article[0].stock;
    maxStock = article[0].stock;

    for(i=0 ; i<QUANTITY ; i++)
    {
        if(article[i].stock > maxStock)
        {
            maxIndex = i;
        }
    }
    for(j=0 ; j<QUANTITY ; j++)
    {
        if(article[j].stock < minStock)
        {
            minIndex = j;
        }
    }

    printf("\t\tS/N\tPROV\tDESC\tIMPORTE\tSTOCK\n");
    printf("Mayor Stock\t%d\t%d\t%s\t%d\t%d\n",article[i].serialNumber,article[i].serialSuplier,article[i].description,article[i].amount,article[i].stock);
    printf("Menor Stock\t%d\t%d\t%s\t%d\t%d\n",article[j].serialNumber,article[j].serialSuplier,article[j].description,article[j].amount,article[j].stock);

}

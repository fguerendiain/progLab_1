#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "lib.h"
#include "string.h"
#include "../../ownLibC/screenSystemShow.h"
#include "../../ownLibC/userInputOutput.h"

#define SRTINGBUFFER 4000
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

    if(article!=NULL && provider!=NULL && lenght>0)
    {
        switch(menu)
        {
            case ADD :
                cleanScreen();
                addArticle(article, provider, lenght);
                pauseScreen();
            break;

            case MODIFY :
                cleanScreen();
                modifyArticle(article, provider, lenght);
                pauseScreen();
            break;

            case DEL :
                cleanScreen();
                delArticle(article, lenght);
                pauseScreen();
            break;

            case LS_PRODUCT :
                cleanScreen();
                listArticle(article, lenght);
                pauseScreen();
            break;

            case LS_ALL :
                cleanScreen();
                listAll(article, provider, lenght);
                pauseScreen();
            break;

            case EXIT :
                ret = 0;
            break;
        }
    }
    else
    {
        ret = -1;
    }
    return ret;
}

/** \brief inicializa todos los campos siEmpty de los array
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
                article[i].isEmpty = 1;
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
    int auxStock;
    int flagValidSuplier = -1;
    int i;
    int index = 1;
    int ret = -1;

    if(article!=NULL && provider!=NULL && lenght>0)
    {
        index = searchFirstEmpty(provider,article,lenght,1);

        if(index!=-1)
        {
            getUserInputInt(&auxSerialNumber,0,lenght,"Ingrese el codigo del producto\n","Por favor ingrese un codigo valido\n",0);
            do
            {
                getUserInputInt(&auxSerialSuplier,0,lenght,"Ingrese el codigo del proveedor asociado\n","Por favor ingrese un codigo valido\n",0);
                for(i=0; i<lenght; i++)
                {
                    if(provider[i].serialSuplier == auxSerialSuplier)
                    {
                        flagValidSuplier = 0;
                    }
                }
                if(flagValidSuplier != 0)
                {
                    printf("El proveedor no existe, por favor intentelo de nuevo");
                    return -1;
                }
            }while(flagValidSuplier);
            getUserInputString(auxDescription,3,50,"Ingrese la descripcion del articulo\n","Por favor ingrese datos validos\n",SRTINGBUFFER,0);
            getUserInputInt(&auxAmount,0,10000,"Ingrese el importe del articulo\n","Por favor ingrese un importe valido\n",0);
            getUserInputInt(&auxStock,0,10000,"Ingrese la cantidad disponible\n","Por favor ingrese una cantidad valida\n",0);

            article[index].serialNumber = auxSerialNumber;
            article[index].serialSuplier = auxSerialSuplier;
            strcpy(article[index].description,auxDescription);
            article[index].amount = auxAmount;
            article[index].stock = auxStock;
            article[index].isEmpty = 0;

            ret = 0;
        }
        else
        {
            printf("No hay lugar para agregar nuevos articulos\n");
            ret = 0;
        }
    }
    return ret;
}

/** \brief busca el primer elemnto libre en los array article y provider
 *
 * \param (provider) array de proveedores
 * \param (article) array de articulos
 * \return devuelve el subindice buscado, en caso que no exista devuelve -1
 *
 */

int searchFirstEmpty(Suplier *provider, Product *article, int length, int arrayOption)
{
    int i;
    int ret = -1;

    switch(arrayOption)
    {
        case 1 :
            for(i=0 ; i<length ; i++)
            {
                if(article[i].isEmpty == 0)
                    ret = i;
            }
        break;

        case 2 :
            for(i=0 ; i<length ; i++)
            {
                if(provider[i].isEmpty == 0)
                    ret = i;
            }
        break;
    }
    return ret;
}

/** \brief imprime los datos del articulo con mayor stock y el de menor stock
 *
 * \param (article) array de productos
 * \param (length) longitud del array
 * \return devuelve 0 si funciono correctamente
 *
 */

int listArticle(Product *article, int length)
{
    Product minStock;
    Product maxStock;
    int flagMaxValue = 1;
    int flagMinValue = 1;
    int i;
    int ret = -1;

    if(article != NULL && length > 0)
    {

        for(i=0 ; i<length ; i++)
        {
            if(article[i].isEmpty == 0)
            {
                if(flagMaxValue)    //evalua si es la primera comparacion e inicializa el maximo
                {
                    maxStock = article[i];
                    flagMaxValue = 0;
                }
                if(article[i].stock > maxStock.stock)
                {
                    maxStock = article[i];
                }
            }
            if(article[i].isEmpty == 0)
            {
                if(flagMinValue)    //evalua si es la primera comparacion e inicializa el minimo
                {
                    minStock = article[i];
                    flagMinValue = 0;
                }
                if(article[i].stock < minStock.stock)
                {
                    minStock = article[i];
                }
            }
        }
        stringSetCase(maxStock.description,3);
        stringSetCase(minStock.description,3);
        printf("\t\tS/N\tPROV\tDESC\tIMPORTE\tSTOCK\n");
        printf("Mayor Stock\t%d\t%d\t%s\t$ %d\t%d\n",maxStock.serialNumber,maxStock.serialSuplier,maxStock.description,maxStock.amount,maxStock.stock);
        printf("Menor Stock\t%d\t%d\t%s\t$ %d\t%d\n",minStock.serialNumber,minStock.serialSuplier,minStock.description,minStock.amount,minStock.stock);
        ret = 0;
    }
    return ret;
}

/** \brief ordena e imprime los productos primero por codigo de proveedor descendente y luego por descripcion de producto ascendente
 *
 * \param (article) Array de productos
 * \param (provider) Array de proveedores
 * \param (length) longitud del array
 * \return 0 si funciona corretcamente, -1 en caso de puntero a null o longitud negativa
 *
 */

int listAll(Product *article, Suplier *provider, int length)
{
    Product auxArticle;
    Suplier auxProvider;
    int i;
    int j;
    int ret = -1;

    if(article!=NULL && length>0)
    {
        for(i=0;i<length-1;i++)
        {
            for(j=i+1;j<length;j++)
            {
                if(article[i].serialSuplier>article[j].serialSuplier)
                {
                    auxArticle = article[i];
                    article[i] = article[j];
                    article[j] = auxArticle;
                }
                if(article[i].serialSuplier==article[j].serialSuplier)
                {
                    if(strcmp(article[i].description,article[j].description)>0)
                    {
                        auxArticle = article[i];
                        article[i] = article[j];
                        article[j] = auxArticle;
                    }
                }
            }
        }

        printf("PROV\t\tDESCRIPCION\t\tART\t\tDESCRIPCION\t\tIMPORTE\t\tSTOCK\n");
        for(i=0;i<length;i++)
        {
            if(article[i].isEmpty == 0)
            {
                for(j=0;j<length;j++)
                {
                    if(article[i].serialSuplier == provider[j].serialSuplier)
                    {
                        auxProvider = provider[j];
                    }

                }
                stringSetCase(auxProvider.description,3);
                stringSetCase(article[i].description,3);
                printf("%d\t\t%s\t\t%d\t\t%s\t\t$ %d\t\t%d\n",article[i].serialSuplier,auxProvider.description,article[i].serialNumber,article[i].description,article[i].amount,article[i].stock);
            }
        }

        ret = 0;
    }
    return ret;
}

/** \brief realiza el borrado logico de por codigo de producto
 *
 * \param (article) array de productos
 * \param (lenght) longitud del array
 * \return 0 si funciona correctamente, -1 si hay un puntero a null o una longitud menor a 1
 *
 */

int delArticle(Product *article, int lenght)
{
    int delIndex;
    int flagErreaseOk = 1;
    int i;
    int ret = -1;

    if (article!=NULL && lenght>0)
    {
        getUserInputInt(&delIndex,0,lenght-1,"Ingrese el codigo de producto a eliminar\n\n","Por favor ingrese un codigo valido\n\n",0);

        for(i=0;i<lenght;i++)
        {
            if(article[i].isEmpty==0 && article[i].serialNumber==delIndex)
            {
                article[i].isEmpty = 1;
                flagErreaseOk = 0;
                break;
            }
        }
        if(flagErreaseOk)
        {
            printf("El articulo indicado no existe, por favor intente nuevamente\n");
        }
        else
        {
            printf("El articulo fue eliminado con exito\n");
        }
        ret = 0;
    }
    return ret;
}

/** \brief permite modificar articulos por el codigo del articulo
 *
 * \param (article) array de articulos
 * \param (provider) array de proveedores
 * \param (lenght) longitud de los arrays
 * \return 0 si funciona correctamente -1 si es un puntero a null o una longitud negativa
 *
 */

int modifyArticle(Product *article, Suplier *provider, int lenght)
{
    int modIndex;
    int flagModifyOk = 1;
    int i;
    int ret = -1;

    if (article!=NULL && lenght>0)
    {
        getUserInputInt(&modIndex,0,lenght-1,"Ingrese el codigo de producto a modificar\n\n","Por favor ingrese un codigo valido\n\n",0);

        for(i=0;i<lenght;i++)
        {
            if(article[i].isEmpty==0 && article[i].serialNumber==modIndex)
            {
                addArticle(article,provider,lenght);
                flagModifyOk = 0;
                break;
            }
        }
        if(flagModifyOk)
        {
            printf("El articulo indicado no existe, por favor intente nuevamente\n");
        }
        else
        {
            printf("El articulo fue modificado con exito\n");
        }
        ret = 0;
    }
    return ret;
}

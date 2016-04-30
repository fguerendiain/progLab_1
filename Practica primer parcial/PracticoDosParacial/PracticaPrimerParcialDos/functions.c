#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "../../../ownLibraries/screenSystemShow.h"
#include "../../../ownLibraries/userInputOutput.h"

#define ALTAS 1
#define MODIFICAR 2
#define BAJA 3
#define INFORMAR 4
#define LISTAR 5
#define SALIR 6


/** \brief Ejecuta la opcion del menu seleccionada por el usuario
 *
 * \param (suplier) Array de struct de proveedores
 * \param (product) Array de struct de articulos
 * \param (arrayLenght) cantidad de elementos de los arrays
 * \param (userInput) opcion elegida por el usuario para ejecutar
 *
 */

void runFunctionMenu(Proveedor *suplier, Articulo *product, int arrayLenght int userInput)
{
    if(suplier == NULL || producto == NULL || arrayLenght<1)
    {
        printf("Error de memoria\n\nPor favor, intente nuevamente\n");
        pauseScreen();
        return -1;
    }
    else
    {
        switch(userInput)
        {
            case ALTAS :
                cleanScreen();
           //     addArticle(product, suplier, arrayLenght);
                pauseScreen();
            break;

            case MODIFICAR :
                cleanScreen();
            //    modifyArticle(product, suplier, arrayLenght);
                pauseScreen();
            break;

            case BAJA :
                cleanScreen();
           //     delArticle(product, suplier, arrayLenght);
                pauseScreen();
            break;

            case INFORMAR :
                cleanScreen();
            //    listArticle(product, suplier, arrayLenght);
                pauseScreen();
            break;

            case LISTAR :
                cleanScreen();
            //    listSuplierAndArticle(product, suplier, arrayLenght);
                pauseScreen();
            break;

            case SALIR :
            break;
        }

    }
}

/** \brief inicializa el elemento isEmpty en los arrays de struct suplier y product en 1
 *
 * \param (suplier) Array de struct de proveedores
 * \param (product) Array de struct de articulos
 * \param (arrayLenght) cantidad de elementos de los arrays
 * \return
 *
 */

int setEmptyValuesOff(Proveedor *suplier, Articulos *product, int arrayLenght)
{
    int i;
    int ret = -1;

    if(suplier == NULL || product == NULL || arrayLenght<1)
    {
        return ret;
    }
    else
    {
        for(i=0; i<arrayLenght; i++)
        {
            suplier[i].isEmpty = 1;
            product[i].isEmpty = 1;
            ret = 0;
        }
    }
    return ret;
}

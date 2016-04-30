#ifndef __FUNCTIONS
#define __FUNCTIONS

/*-----------------------------------   STRUCTS ----------------------------------*/

typedef struct{
    int codigo;
    char nombre[31]
    char descripcion[51];
    int isEmpty;
}Proveedor

typedef struct{
    int codigo;
    int codigoProveedor;
    char nombre[31];
    char descripcion[51];
    int importe;
    int stock;
    int isEmpty;
}Articulo


/*----------------------------------    FUNCIONES DEL PROGRAMA  -----------------------*/

void runFunctionMenu(Proveedor *suplier, Articulo *product, int arrayLenght int userInput);     /**< Ejecuta la opcion del menu seleccionada por el usuario */

int setEmptyValuesOff(Proveedor *suplier, Articulos *product, int arrayLenght);     /**< inicializa el elemento isEmpty en los arrays de struct suplier y product en 1 */






#endif // __FUNCTIONS

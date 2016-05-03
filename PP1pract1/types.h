#ifndef __STRUCT.H
#define __STRUCT.H

typedef struct
{
    int serialNumber;
    int serialSuplier;
    char description[51];
    int amount;
    int stock;
    int isEmpty;
}Product;

typedef struct
{
    int serialNumber;
    char description[51];
    int isEmpty;
}Suplier;




#endif // __STRUCT.H

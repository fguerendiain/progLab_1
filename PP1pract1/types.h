#ifndef __TYPES
#define __TYPES

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
    int serialSuplier;
    char description[51];
    int isEmpty;
}Suplier;




#endif // __TYPES

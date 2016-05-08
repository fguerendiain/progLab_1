#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "lib.h"
#include "screenSystemShow.h"
#include "userInputOutput.h"

#define QUANTITY 1000

#define HARDCODE 1 //([1] HABILITA LA CARGA DE DATOS DEFAULT, [0] DESHABILITA)

int main()
{
    int exit;
    int menu;
    Client user[QUANTITY];
    Post comment[QUANTITY];

    do  // SE REPITE LA ACCION DE INICIALIZAR EN CASO QUE user SEA UN PUNTERO A NULL
    {
        exit = initializeEmptyFlagArray(user,comment,QUANTITY);
    }while(exit);

if(HARDCODE){/******************************************************************
*******************************************************************************/
//VALORES PARA HARDCODEAR LOS ELEMENTOS DE LOS ARRAYS
    int i;

    int auxNick[] = {1,2,3,4,5};
    int auxPasswd[] = {1234,8523,7896,6541,1236};
    char auxName[][51] = {"BARRY", "BRUCE","CLARK","DIANA","HALL"};
    char auxEmail[][51] = {"FLASH@GMAIL.COM", "BATMAN@HOTMAIL.COM","SUPERMAN@YAHOO.COM","WWOMAN@UOL.COM","GREEN@FACEBOOK.COM"};

    char auxText[][51] = {"HOY TE CONVERTIS EN HEROE","VAMOS QUE SALE","O CUATRO O NADA","SI SE PUEDE","MAY THE FORCE BE WITH YOU"};
    int auxLike[] = {1,5,6,7,2};
    int auxUserNickRef[] = {1,1,1,4,5};

    int auxState[] = {0,0,0,0,0};

    for (i=0 ; i<5 ; i++)
    {
//INICIALIZAR ARRAY USER
        user[i].nick = auxNick[i];
        user[i].passwd= auxPasswd[i];
        strcpy(user[i].name,auxName[i]);
        strcpy(user[i].email,auxEmail[i]);
        user[i].state = auxState[i];
//INICIALIZAR ARRAY POST
        strcpy(comment[i].text,auxText[i]);
        comment[i].like = auxLike[i];
        comment[i].userNickRef = auxUserNickRef[i];
        comment[i].state = auxState[i];
    }
/*******************************************************************************
*******************************************************************************/}

    do
    {
        printAwesomeMenu("1. ALTA DE USUARIO\n"
                         "2. MODIFICAR USUARIO\n"
                         "3. BAJA DE USUARIO\n"
                         "4. NUEVO COMENTARIO\n"
                         "5. ME GUSTA!\n"
                         "6. INFORMAR\n"
                         "7. LISTAR\n"
                         "8. SALIR\n\n");
        getUserInputInt(&menu,1,8,"Ingrese la opcion deseada\n","Por favor, ingrese una opcion valida\n",0);
        exit = runFunctionMenu(menu,user,comment,QUANTITY);

    }while(exit);

    return 0;
}

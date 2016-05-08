#include <stdio.h>
#include <stdlib.h>
#include "lib.h"
#include "string.h"
#include "screenSystemShow.h"
#include "userInputOutput.h"

#define SRTINGBUFFER 4000

#define ADD 1
#define MODIFY 2
#define DEL 3
#define COMMENT 4
#define LIKE 5
#define LS_INFORM 6
#define LS_ALL 7
#define EXIT 8


/** \brief Ejecuta la opcion seleccionada por el usuario
 *
 * \param (menu) recibe el numero ingresado por el usuario
 * \param (user) array de usuarios
 * \param (lenght) longitud del array
 * \return 0 para salir del programa 1 para continuar
 *
 */

int runFunctionMenu(int menu, Client *user, Post *comment, int lenght)
{
    int ret = 1;

    if(user!=NULL && comment!=NULL && lenght>0)
    {
        switch(menu)
        {
            case ADD :
                cleanScreen();
                addUser(user, comment, lenght,1);
                pauseScreen();
            break;

            case MODIFY :
                cleanScreen();
                modifyUser(user, comment, lenght);
                pauseScreen();
            break;

            case DEL :
                cleanScreen();
                delUser(user, lenght);
                pauseScreen();
            break;

            case COMMENT :
                cleanScreen();
                newComment(user,comment,lenght);
                pauseScreen();
            break;

            case LIKE :
                cleanScreen();
                newLike(user,comment,lenght);
                pauseScreen();
            break;

            case LS_INFORM :
                cleanScreen();
                listInfo(user,comment,lenght);
                pauseScreen();
            break;

            case LS_ALL :
                cleanScreen();
                listPostAndLike(user,comment,lenght);
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

/** \brief inicializa todos los campos state de los array de usuario y comment
 *
 * \param (user) array de Clientos
 * \param (comment) array de proveedores
 * \return 0 si funciono correctamente, -1 en caso que alguna direccion sea NULL o el largo menor que 1
 *
 */

int initializeEmptyFlagArray(Client *user,Post *comment,int length)
{
    int ret = -1;

    if(user != NULL && comment != NULL && length > 0)
    {
        int i;
        for(i=0 ; i<length ; i++)
        {
                user[i].state = 1;
                comment[i].state = 1;
                user[i].maxComment = 0;
        }
        ret = 0;
    }
    return ret;
}

/** \brief Permite agregar un usuario
 *
 * \param (user) array de usuarios
 * \param (comment) array de post
 * \param (lenght) longitud de los arrays
 * \param (modifyFlag) determina si la funcion fue llamada desde la opcion modificar
 * \return 0 si los valores se cargaron correctamente
 *
 */

int addUser(Client *user, Post *comment,int lenght, int modifyFlag)
{
    int auxNick;
    int auxPasswd;
    char auxName[31];
    char auxEmail[31];
    int index = 1;
    int ret = -1;

    if(user!=NULL && comment!=NULL && lenght>0)
    {
        index = searchFirstEmpty(comment,user,lenght,1);

        if(index!=-1)
        {
            if(modifyFlag)
            {
                getUserInputInt(&auxNick,0,lenght,"Ingrese el Nick del usuario (numeros hasta 4 digitos)\n","Por favor ingrese un numero valido\n",0);
            }
            getUserInputString(&auxName,3,31,"Ingrese el nombre del usuario\n","Por favor ingrese un nombre valido\n",SRTINGBUFFER,0);
            getUserInputString(&auxEmail,5,31,"Ingrese el e-mail del usuario\n","Por favor ingrese un e-mail valido\n",SRTINGBUFFER,0);
            getUserInputInt(&auxPasswd,0,9999,"Ingrese su clave numerica de 4 digitos\n","Por favor ingrese una clave valida",0);

            user[index].nick = auxNick;
            user[index].passwd = auxPasswd;
            strcpy(user[index].name,auxName);
            strcpy(user[index].email,auxEmail);
            user[index].state = 0;

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

/** \brief busca el primer elemnto libre en los array user y comment
 *
 * \param (comment) array de proveedores
 * \param (user) array de articulos
 * \return devuelve el subindice buscado, en caso que no exista devuelve -1
 *
 */

int searchFirstEmpty(Post *comment, Client *user, int length, int arrayOption)
{
    int i;
    int ret = -1;

    switch(arrayOption)
    {
        case 1 :
            for(i=0 ; i<length ; i++)
            {
                if(user[i].state == 0)
                    ret = i;
            }
        break;

        case 2 :
            for(i=0 ; i<length ; i++)
            {
                if(comment[i].state == 0)
                    ret = i;
            }
        break;
    }
    return ret;
}

/** \brief busca e imprime el usuario con mayor cantidad de comentarios, el comentario con mayor cantidad de likes y el valor promedio de likes
 *
 * \param (user) array de Clientos
 * \param (length) longitud del array
 * \return devuelve 0 si funciono correctamente
 *
 */

int listInfo(Client *user,Post *comment, int length)
{
    Client maxComment;
    Post maxLike;

    int promLikes=0;
    int totalLikes=0;
    int countLikes=0;

    int flagMaxLikeValue = 1;
    int flagMaxCommentValue = 1;
    int i;
    int j;
    int ret = -1;

    if(user != NULL && length > 0)
    {
        for(i=0;i<length;i++)  //ANALIZA LA CANTIDAD DE COMENTARIOS POR USUARIO
        {
            for(j=0;j<length;j++)
            {
                if(user[i].nick==comment[j].userNickRef)
                {
                    user[i].maxComment++;
                }
            }
        }
        for(i=0;i<length;i++)   //USUARIO CON MAYOR CANTIDAD DE COMENTARIOS
        {
            if(user[i].state == 0)
            {
                if(flagMaxCommentValue)
                {
                    maxComment = user[i];
                    flagMaxCommentValue = 0;
                }
                if(maxComment.maxComment<user[i].maxComment)
                {
                    maxComment = user[i];
                }
            }
        }
        for(i=0 ; i<length ; i++)   //COMENTARIO CON MAYOR CANTIDAD DE 'ME GUSTA'
        {
            if(comment[i].state == 0)
            {
                if(flagMaxLikeValue)    //evalua si es la primera comparacion e inicializa el maximo
                {
                    maxLike = comment[i];
                    flagMaxLikeValue = 0;
                }
                if(maxLike.like<comment[i].like)
                {
                    maxLike = comment[i];
                }
            }
        }
        for(i=0; i<length; i++)     //ANALIZA Y CALCULA EL TOTAL DE LIKES
        {
            if(comment[i].state == 0)
            {
                totalLikes=totalLikes+comment[i].like;
                countLikes++;
            }
        }

        promLikes = totalLikes/countLikes;  //CALCULA EL PROMEDIO DE LIKES

        stringSetCase(maxComment.name,3);
        stringSetCase(maxLike.text,3);

        printf("USUARIO CON MAYOR CANTIDAD DE COMENTARIOS\n");
        printf("Nombre: %s\nNick: %d\nCant. Comentarios: %d\n\n\n\n",maxComment.name,maxComment.nick,maxComment.maxComment);

        printf("COMENTARIO CON MAYOR CANTIDAD DE 'ME GUSTA'\n");
        printf("Me gusta: %d\nComentario: %s\n\n\n\n",maxLike.like,maxLike.text);

        printf("PROMEDIO DE 'ME GUSTA': %d por comentario\n",promLikes);

        ret = 0;
    }
    return ret;
}

/** \brief imprime los post y like ordenados primero por nombre de usuario y luego por nick
 *
 * \param (user) Array de usuarios
 * \param (comment) Array de post
 * \param (length) longitud del array
 * \return 0 si funciona corretcamente, -1 en caso de puntero a null o longitud negativa
 *
 */

int listPostAndLike(Client *user, Post *comment, int length)
{
    Client auxUser;
    Post auxComment;
    int i;
    int j;
    int ret = -1;

    if(user!=NULL && length>0)
    {
        for(i=0;i<length-1;i++)
        {
            for(j=i+1;j<length;j++)
            {
                if(strcmp(user[i].name,user[j].name)>0)
                {
                    auxUser = user[i];
                    user[i] = user[j];
                    user[j] = auxUser;
                }
                if(strcmp(user[i].name,user[j].name)==0)
                {
                    if(user[i].nick < user[j].nick)
                    {
                        auxUser = user[i];
                        user[i] = user[j];
                        user[j] = auxUser;
                    }
                }
            }
        }

        printf("MEGUSTA\t\tCOMENTARIO\n\n");
        for(i=0;i<length;i++)
        {
            if(user[i].state == 0)
            {
                for(j=0;j<length;j++)
                {
                    if(user[i].nick == comment[j].userNickRef)
                    {
                        auxComment = comment[j];
                    }

                }
                stringSetCase(auxComment.text,3);
                printf("%d\t\t%s\n",auxComment.like,auxComment.text);
            }
        }

        ret = 0;
    }
    return ret;
}

/** \brief realiza el borrado logico de usuarios seleccionandolos por nick
 *
 * \param (user) array de usuarios
 * \param (lenght) longitud del array
 * \return 0 si funciona correctamente, -1 si hay un puntero a null o una longitud menor a 1
 *
 */

int delUser(Client *user, int lenght)
{
    int delIndex;
    int flagErreaseOk = 1;
    int i;
    int ret = -1;

    if (user!=NULL && lenght>0)
    {
        getUserInputInt(&delIndex,0,lenght,"Ingrese el Nick del Usuario a eliminar\n\n","Por favor ingrese un Nick valido\n\n",0);

        for(i=0;i<lenght;i++)
        {
            if(user[i].state==0 && user[i].nick==delIndex)
            {
                user[i].state = 1;
                flagErreaseOk = 0;
                break;
            }
        }
        if(flagErreaseOk)
        {
            printf("El usuario indicado no existe, por favor intente nuevamente\n");
        }
        else
        {
            printf("El usuario fue eliminado con exito\n");
        }
        ret = 0;
    }
    return ret;
}

/** \brief permite modificar usuarios seleccionandolos por nick
 *
 * \param (user) array de ususarios
 * \param (comment) array de post
 * \param (lenght) longitud de los arrays
 * \return 0 si funciona correctamente -1 si es un puntero a null o una longitud negativa
 *
 */

int modifyUser(Client *user, Post *comment, int lenght)
{
    int modIndex;
    int flagModifyOk = 1;
    int i;
    int ret = -1;

    if (user!=NULL && lenght>0)
    {
        getUserInputInt(&modIndex,0,lenght,"Ingrese el Nick del Usuario a modificar\n\n","Por favor ingrese un Nick valido\n\n",0);

        for(i=0;i<lenght;i++)
        {
            if(user[i].state==0 && user[i].nick==modIndex)
            {
                addUser(user,comment,lenght,0);
                flagModifyOk = 0;
                break;
            }
        }
        if(flagModifyOk)
        {
            printf("El usuario indicado no existe, por favor intente nuevamente\n");
        }
        else
        {
            printf("El usuario fue modificado con exito\n");
        }
        ret = 0;
    }
    return ret;
}

/** \brief permite ingresar un nuevo comentario validando usuario y password
 *
 * \param (user) array de ususarios
 * \param (comment) array de post
 * \param (lenght) longitud de los arrays
 * \return 0 si funciona correctamente -1 si es un puntero a null o una longitud negativa
 *
 */

int newComment(Client *user, Post *comment, int lenght)
{
    int validUser;
    int flagCheckUser;
    int validPasswd;
    int flagCheckPasswd;
    int i;
    int index;
    int ret = -1;

    if(user!=NULL && comment!=NULL && lenght>0)
    {
        validUser = getUserInputInt(&validUser,0,lenght,"Ingrese su Nick\n","Por favor ingrese un Nick valido\n",0);
        for(i=0;i<lenght;i++)
        {
            if(validUser==user[i].nick)
            {
                flagCheckUser = 0;
                index = i;
                break;
            }
        }
        if(flagCheckUser)
        {
            printf("El usuario ingresado no es valido, por favor intentelo nuevamente\n");
            return 0;
        }
        getUserInputInt(&validPasswd,0,9999,"Ingrese su clave numerica de 4 digitos\n","Por favor ingrese una clave valida",0);
        if(validPasswd==user[index].passwd)
        {
            flagCheckPasswd = 0;
        }
        if(flagCheckPasswd)
        {
            printf("La contraseña ingresada no es valida, por favor intentelo nuevamente");
            return 0;
        }
        index = searchFirstEmpty(comment,user,lenght,2);

        comment[index].userNickRef = validUser;
        getUserInputString(&comment[index].text,0,140,"Ingrese su comentario","Por favor ingrese un comentario valido",SRTINGBUFFER,0);
        comment[index].state = 0;
        ret = 0;
    }
    return ret;
}

/** \brief Permite dar like a un comentario ingresando con usuario y clave
 *
 * \param (user) array de ususarios
 * \param (comment) array de post
 * \param (lenght) longitud de los arrays
 * \return 0 si funciona correctamente -1 si es un puntero a null o una longitud negativa
 *
 */

int newLike(Client *user, Post *comment, int lenght)
{
    int validUser;
    int flagCheckUser = 1;
    int validPasswd;
    int flagCheckPasswd = 1;
    int validComment;
    int flagCheckComment = 1;

    int i;
    int index;
    int indexComment;
    int ret = -1;

    if(user!=NULL && comment!=NULL && lenght>0)
    {
        validUser = getUserInputInt(&validUser,0,lenght,"Ingrese su Nick\n","Por favor ingrese un Nick valido\n",0);
        for(i=0;i<lenght;i++)
        {
            if(validUser==user[i].nick)
            {
                flagCheckUser = 0;
                index = i;
                break;
            }
        }
        if(flagCheckUser)
        {
            printf("El usuario ingresado no es valido, por favor intentelo nuevamente\n");
            return 0;
        }
        getUserInputInt(&validPasswd,0,9999,"Ingrese su clave numerica de 4 digitos\n","Por favor ingrese una clave valida",0);
        if(validPasswd==user[index].passwd)
        {
            flagCheckPasswd = 0;
        }
        if(flagCheckPasswd)
        {
            printf("La contraseña ingresada no es valida, por favor intentelo nuevamente");
            return 0;
        }
        getUserInputString(&validComment,0,lenght,"Ingrese el identificador del comentario","Por favor ingrese un identificador valido",SRTINGBUFFER,0);
        for(i=0;i<lenght;i++)
        {
            if(validComment==comment[i].id)
            {
                flagCheckComment = 0;
                indexComment = i;
                break;
            }
            if(flagCheckComment)
            {
                printf("La contraseña ingresada no es valida, por favor intentelo nuevamente");
                return 0;
            }
        }
        comment[index].like++;
        stringSetCase(comment[indexComment].text,3);
        printf("Sumaste un like al siguiente comentario '%s'",comment[indexComment].text);
        ret = 0;
    }
    return ret;
}

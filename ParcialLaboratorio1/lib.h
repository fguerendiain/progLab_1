#ifndef __LIB
#define __LIB

typedef struct
{
    int nick;
    int passwd;
    char name[31];
    char email[31];
    int maxComment;
    int state;

}Client;

typedef struct{

    int id;
    char text[142];
    int like;
    int userNickRef;
    int state;
}Post;

/*******************************************************************************************/

int runFunctionMenu(int menu, Client *user, Post *comment, int lenght); /**< Ejecuta la opcion seleccionada por el usuario */

int initializeEmptyFlagArray(Client *user,Post *comment,int length); /**< inicializa todos los campos state de los array de usuario y comment */

int addUser(Client *user, Post *comment,int lenght, int modifyFlag); /**< Permite agregar un usuario */

int searchFirstEmpty(Post *comment, Client *user, int length, int arrayOption); /**< busca el primer elemnto libre en los array user y comment */

int listInfo(Client *user,Post *comment, int length);    /**< busca e imprime el usuario con mayor cantidad de comentarios, el comentario con mayor cantidad de likes y el valor promedio de likes */

int listPostAndLike(Client *user, Post *comment, int length);    /**< imprime los post y like ordenados primero por nombre de usuario y luego por nick */

int delUser(Client *user, int lenght);  /**< realiza el borrado logico de usuarios seleccionandolos por nick */

int modifyUser(Client *user, Post *comment, int lenght);    /**< permite modificar usuarios seleccionandolos por nick */

int newComment(Client *user, Post *comment, int lenght); /**< permite ingresar un nuevo comentario validando usuario y password */

int newLike(Client *user, Post *comment, int lenght);   /**< Permite dar like a un comentario ingresando con usuario y clave */

#endif // __LIB



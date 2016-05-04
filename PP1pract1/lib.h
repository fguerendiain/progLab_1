#ifndef __LIB
#define __LIB

int runFunctionMenu(int menu, Product *article, Suplier *provider, int lenght); /**< Ejecuta la opcion seleccionada por el usuario */

int initializeEmptyFlagArray(Product *article,Suplier *provider,int length); /**< inicializa todos los campos siEmpty de los array */

int addArticle(Product *article, Suplier *provider,int lenght);  /**< Permite agregar un articulo */

int searchFirstEmpty(Suplier *provider, Product *article, int length, int arrayOption); /**< busca el primer elemnto libre en los array article y provider */

int listArticle(Product *article, int length);   /**< imprime los datos del articulo con mayor stock y el de menor stock */

int listAll(Product *article, Suplier *provider, int length);  /**< ordena e imprime los productos primero por codigo de proveedor descendente y luego por descripcion de producto ascendente */

int delArticle(Product *article, int lenght);   /**< realiza el borrado logico de por codigo de producto */

int modifyArticle(Product *article, Suplier *provider, int lenght); /**< permite modificar articulos por el codigo del articulo */


#endif // __LIB



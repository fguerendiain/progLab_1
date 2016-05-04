#ifndef __LIB.H
#define __LIB.H

int runFunctionMenu(int menu, Product *article, Suplier *provider, int lenght); /**< Ejecuta la opcion seleccionada por el usuario */

int initializeEmptyFlagArray(Product *article,Suplier *provider,int length); /**< inicializa todos los campos de los elementos del array */

int addArticle(Product *article, Suplier *provider,int lenght);  /**< Permite agregar un articulo */

int searchFirstEmpty(Suplier *provider, Product *article, int length, int arrayOption); /**< busca el primer elemnto libre en los array article y provider */

int listArticle(Product *article, int length);
#endif // __LIB



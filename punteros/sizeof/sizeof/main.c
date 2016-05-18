#include <stdio.h>
#include <stdlib.h>

typedef struct{

int legajo;
float salario;
char name[31];
long dni;
char inicial;

}Type;

int main()
{
    Type tipo;

    int tamano;

    tamano = sizeof(short int);//tipo.legajo);
    printf("int = %d\n\n",tamano);

    tamano = sizeof(tipo.name);
    printf("string[31] = %d\n\n",tamano);

    tamano = sizeof(float);//tipo.salario);
    printf("float = %d\n\n",tamano);

    tamano = sizeof(double);//tipo.salario);
    printf("double = %d\n\n",tamano);

    tamano = sizeof(long);//tipo.dni);
    printf("long = %d\n\n",tamano);

    tamano = sizeof(tipo.inicial);
    printf("char = %d\n\n",tamano);

    tamano = sizeof(void);
    printf("void = %d\n\n",tamano);

    tamano = sizeof(Type);
    printf("struct = %d\n\n",tamano);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *a;
    a= (int*)malloc(sizeof(int));

    if(a == NULL)
    {
        printf("No hay memoria suficiente\n");
        exit(0);
    }
    else
    {
        *a = 87;
        printf("a = %d\n",*a);

    }

    free(a);

    return 0;
}

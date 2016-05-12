#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "parser.h"

void sortEmployees(Employee *employeeList, int lenght);

void clonePrintArrayPointers(Employee *pEmployeeList, Employee **arrayPointers, int lenght);

void sortPointersArray(Employee **arrayPointers, int lenght);

int printArrayPointers(Employee **arrayPointers,int length);

int main()
{

    Employee employeeList[1000];
    Employee *arrayPointers[1000];

    getEmployeeList(employeeList, 1000,"MOCK.txt"); // Made with https://www.mockaroo.com/

    clock_t start = clock();

      clonePrintArrayPointers(employeeList,arrayPointers,1000);
      sortPointersArray(arrayPointers,1000);
 //   sortEmployees(employeeList,1000);

    clock_t end = clock();

 //    printEmployeeList(employeeList, 1000);
    printArrayPointers(arrayPointers,1000);


    printf("Elapsed: %0.2f ms\n", 1000 *((double)(end-start) / CLOCKS_PER_SEC));

    return 0;
}


void sortEmployees(Employee *pEmployeeList, int lenght)
{
    Employee auxEmployee;
    int i;
    int j;

    if(pEmployeeList != NULL && lenght > 0)
    {
        for(i=0; i<lenght-1; i++)
        {
            for(j=i+1; j<lenght; j++)
            {
                if(strcmp((*(pEmployeeList+i)).name,(*(pEmployeeList+j)).name)>0)
                {
                     auxEmployee = *(pEmployeeList+i);
                    *(pEmployeeList+i) = *(pEmployeeList+j);
                    *(pEmployeeList+j) = auxEmployee;
                }
            }
        }
    }
}

void clonePrintArrayPointers(Employee *pEmployeeList, Employee **arrayPointers, int lenght)
{
    int i;
    for (i=0; i<lenght; i++)
    {
        *(arrayPointers+i) = (pEmployeeList+i);
      //  printf("%s\n",(*(arrayPointers+i))->name);
    }

}

void sortPointersArray(Employee **arrayPointers, int lenght)
{
    Employee * auxEmployee;
    int i;
    int j;

    if(arrayPointers != NULL && lenght > 0)
    {
        for(i=0; i<lenght-1; i++)
        {
            for(j=i+1; j<lenght; j++)
            {
                if(strcmp((**(arrayPointers+i)).name,(**(arrayPointers+j)).name)>0)
                {
                     auxEmployee = *(arrayPointers+i);
                    *(arrayPointers+i) = *(arrayPointers+j);
                    *(arrayPointers+j) = auxEmployee;
                }
            }
        }
    }
}

int printArrayPointers(Employee **arrayPointers,int length)
{
    int i;
    int ret = -1;
    if(*arrayPointers != NULL && length >0)
    {
        for(i=0;i<length;i++)
        {
            printf("\n%d %s %s %s %s %s",(*(arrayPointers+i))->id ,(*(arrayPointers+i))->name,(*(arrayPointers+i))->lastName,(*(arrayPointers+i))->email,(*(arrayPointers+i))->gender,(*(arrayPointers+i))->ip);
        }
        ret = 0;
    }

    return ret;
}

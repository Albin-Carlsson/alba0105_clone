#include <stdio.h>
#include <stdlib.h>

typedef char *string_t; //skapar ett namn för ett typ
typedef unsigned int age_t; //icke-negativt tal
typedef int int_fold_func(int, int); //definerar en funktionstyp 

//En funktion som tar en array av heltal, arrayens längs och en pekare
// till en funktion av typedn Int-> Int-> Int, likt accummulate 
int foldl_int_int(int numbers[], int numbers_siz, int int_fold_func *f)
{
    int result=0;
    
    //Loopa över arrayen och för varje element e utför result=f(result,e)
    for (int i=0; i< numbers_siz; i++)
    {
        result=f(result, numbers[i]);
    }
    return result;
}

int add(int a, int b)
{
    return a+b;
}

long sum(int numbers[], int numbers_siz)
{
    return foldl_int_int(numbers, numbers_siz, add);
}
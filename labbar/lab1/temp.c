#include <stdio.h>
#include <stdbool.h> //för bool
#include <stdlib.h> //för  atoi
#include <math.h> //för matematiska expressions
#include <string.h> //för strlen
#include <ctype.h> //för isdigit

bool is_number(char *str)
{
    int length=strlen(str); //tar ut längden på strängen    
    int i=0;
    if (str[i]=='-')
    {
        if (length==1)
        {
            return false; //ett minus är inte ett tal
        }
        i=1;    //så skippar man första tecknet när vi kör isdigit
    }

    for(; i<length; ++i)
    {
        if (!isdigit((unsigned char)str[i]))  //om strängen inte är ett tal
        {
            return false;
        }
    }

    return true;
}



int main( int argc, char *argv[])
{
    if (argc > 1 && is_number(argv[1]))
    {
        printf("%s is a number\n", argv[1]);
    }
    else
    {
        if (argc > 1)
        {
            printf("%s is not a number\n", argv[1]);
        }
        else
        {
            printf("Please provide a command line argument!\n");
        }
    }
}
#include <stdio.h>
#include <stdbool.h> //för bool
#include <stdlib.h> //för  atoi
#include <math.h> //för matematiska expressions
#include <string.h> //för strlen
#include <ctype.h> //för isdigit


 int gcd(int a, int b) //euklides algoritm
 {
    if (a==b)
    {
        return a;
    }

    else if (a>b){
        return gcd(a-b,b);
    }

    else
    {
        return gcd(a, b-a);
    }
}

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

bool is_positive(char *str) //kontroll funktion för negativa tal
{
    return str[0]!='-';
   
}


int main(int argc, char *argv[])
{
    if (argc!=3) //om felaktig antal mäts in
    {
        printf("You have introduced insufficient/too many arguments");
        return 0;
    }
    if (is_number(argv[2]) && is_number(argv[1])) //kontrollerar att argumenten är tal
    { 
        if (is_positive(argv[2]) && is_positive(argv[1]))
        {
            int a=atoi(argv[1]);   //konverterar karaktär till tal och lägger de i variabler
            int b=atoi(argv[2]);

            int result= gcd(a,b);
            printf("gcd(%d,%d)=%d",a,b,result);
            return 0;
        }
        printf("You can not introduce negative numbers!");
        return 0;
    
    }
    printf("You have to introduce numbers!!!");
}
#include <stdio.h>
#include <stdbool.h> //för bool
#include <stdlib.h> //för  atoi
#include <math.h> //för matematiska expressions
#include <string.h> //för strlen
#include <ctype.h> //för isdigit

int main (int argc, char*argv[])
{
    if (argc> 1)
    {
        int T=atoi(argv[1]);
        printf("1");
        for (int i=2; i<=T; ++i)
        {
           if(i%3==0)
           {
            printf(", Fizz");
           }

           else if (i%5==0)
           {
            printf(", Buzz");
           }

           else if (i%3==0 && i%5==0)
           {
            printf(", Fizz Buzz");
           }

           printf(", %d", i);
        }
    }
}
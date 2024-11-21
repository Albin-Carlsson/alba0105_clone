#include <stdio.h>

int main (void)
{
    int c=getchar(); //tar första karaktären
    int safety =1024;
    while(c!=EOF && --safety>0) //om vi inte har uppnått slutet av en sträng
    {
        putchar(c); //skriver ut karakär för karaktär
        c=getchar();
    }

    return 0;
}
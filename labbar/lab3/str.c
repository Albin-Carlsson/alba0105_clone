#include <stdio.h>
#include <string.h> //för strlen

int string_length(char *str)
{
    int i=0;
    while( str[i]!='\0')  //nullterminator
    {
        i++;
    }
    return i;
}

int print( char *str) //utan radbrytning
{
    int i=0;
    while (str[i]!='\0')
    {
        putchar(str[i]);
        i++;
    }
    return 0;
}

int println (char *str) //med radbrytning
{
    print(str);
    putchar('\n');
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc <2)
    {
        printf("Usage: %s words or string", argv[0]);
    }
    else
    {
        for (int i=1; i<argc; ++i)
        {
            printf("Expected:");
            puts(argv[i]);
            printf("Actual:");
            println(argv[i]);
        }
              
    }
    return 0;
}
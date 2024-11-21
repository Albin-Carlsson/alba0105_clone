#include <stdio.h>

void string_copy(char *source, char *dest)
{
    while (*source)
    {
        *dest=*source;
        ++dest;
        ++source;
    }
}

int string_length(char*str)
{
    char *end=str;  //end pekar på starten av strängen
    while(*end!='\0')  //så länge end pekar inte på slutet av strängen, flyttar vi till nästa
    {
        ++end;
    }
    return end-str;
}
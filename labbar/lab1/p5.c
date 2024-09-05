#include <stdio.h>
#include <stdlib.h> //för  atoi
#include <math.h> //för matematiska expressions

int main(int argc, char *argv[] )
{
    if (argc!=2)
    {
        printf("Du har inte angett ett tal");
        return 0;
    }
    int N=atoi(argv[1]);
    if (N<=1)
    {
        printf("%d är inte ett primtal", N);
        return 0;
    }

    float roten_ur_n=sqrt(N);
    int limit=floor(roten_ur_n) + 1;

    for( int x=2; x<=limit; ++x)
    {
       if (N%x==0)
       {
        printf("%d är inte ett primtal",N);
        return 0;
       }
    }

    printf("%d är ett primtal", N);
    return 0;

}
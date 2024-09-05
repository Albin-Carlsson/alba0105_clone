#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{   int total=0;
    if (argc!=3)
    {
        printf("Usage %s rows growth\n", argv[0]);
        return 0;
    }
    int rows= atoi(argv[1]);    //konverterar argumenter till heltal
    int growth= atoi(argv[2]);
            
    if (rows==0 || growth==0)
    {
        printf("Totalt 0 \n");
        return 0;
    }

    for (int i=1; i<=rows; ++i)
    {
        int num_ast= i * growth; //beräknar antal asterixar per rad
        for ( int j=1; j<=num_ast; j++)
        {
            printf("*");
        }
        printf("\n");
        total+=num_ast;
    }

        
    printf("\nTotalt: %d", total);
    return 0;
}
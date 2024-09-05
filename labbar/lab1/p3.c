#include <stdio.h>

int main(void)
{   int total=0;
    char *ast="*";
    for( int i=1;
        i<=10;
        i=i+1)
        {
        
        printf("%s\n", ast);
        for (int t=1;
            t<=i;
            t=t+1)
            {
                printf("%s", ast);
                total=total +1;
            }
            
        }
    printf("\nTotalt: %d", total);
    return 0;
                
}
#include <stdio.h>
#include <stdlib.h>

int fib (int num)
{
    int ppf=0;  //the two given fib values
    int pf=1;

    for (int i=1; i< num; ++i)
    {
        int tmp=pf;
        pf=ppf +pf;
        ppf=tmp;
    }

    return pf;
}

int my_fib(int num) //recursiv fib
{
    if(num ==0)
    {
        return 0;
    }

    if(num==1)
    {
        return 1;
    }

    else
    {
        return my_fib(num-1) + my_fib(num-2);
    }
}


long rec_sum(int numbers[], int numbers_siz, int index)
{
    if (index< numbers_siz)
    {
        return numbers[index] +rec_sum(numbers, numbers_siz, index+1);
    }
    else
    {
        return 0;
    }
}

long sum(int numbers[], int numbers_siz)
{
    return rec_sum(numbers, numbers_siz, 0);
}

int main (int argc, char *argv[])
{
    if (argc!=2)
    {
        printf("Usage: %s number \n", argv[0]);
    }

    else
    {
        int n=atoi(argv[1]);
        if (n<2)
        {
            printf("fib(%d)= %d\n", n, n);
        }
        else 
        {
            printf("Expected: fib(%s)=%d\n", argv[1], fib(n));
            printf("Actual: fib(%s)=%d\n", argv[1], my_fib(n));
        }
    }
    return 0;

}
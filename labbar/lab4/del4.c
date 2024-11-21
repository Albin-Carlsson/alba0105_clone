#include <stdio.h>
#include <string.h> //för strlen

 
void print(char *str)
{
    while (*str!='\0')
    {
        putchar(*str);
        str++;
    }
}

int main() {
    char my_string[] = "Hello, world!";
    print(my_string);  // Output: Hello, world!
    return 0;
}
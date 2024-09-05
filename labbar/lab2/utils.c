#include <stdio.h>

int ask_question_int(char *question)
{
    int result = 0; //stores the number that the user inputs
    int conversions=0;    //keeps track of whether the the input was succesfully read as an integer
 
    do
    {
        printf("%s\n", question);
        conversions= scanf("%d", &result);  //read user input,tries to convert to integer, if success conversion=1, otherwise conv<1
        int c;
        do
        {
            c=getchar();              //clears any extra characters from the input buffer until it finds a new line
        }                               
        while (c != '\n' && c!= EOF);  //with this
        putchar('\n');

    }     
    while(conversions <1);
    return result;
}

int main(void)
{
    int tal;
    tal= ask_question_int("Första talet");
    printf("Du skrev %d \n", tal);

    tal= ask_question_int("Andra talet");
    printf("Du skrev %d \n", tal);
    return 0;
}
#include <stdio.h>
#include "utils.h"
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand(time(NULL));  //seedar slumpgeneratorn med aktuell tid
    int tal= random() %10;  //slumpar ett tal mellan 0 och 1023
    char *namn;
    int counter=1;
    char *question = "Skriv in ditt namn: \n";
    namn=ask_question_string(question);
    printf("Du %s, jag tänker på et tall ... kan du gissa vilket?\n", namn);
    while (counter<15)
    { 
        int guess= ask_question_int("");  
        if (guess==tal)
        {
            printf("Bingo! \n Det tog %s %d gissningar att komma fram till %d", namn, counter, tal);
            return 0;
        }
      
        else if (guess<tal)
        { 
            printf("För litet!\n");
            counter=counter+1;
        }

        else if (guess>tal)
        {
            printf("För stort\n");
            counter=counter+1;
        }
    
    }
    
    printf("Nu har du slut på gissningar! Jag tänkte på %d", tal);
    return 0;
}
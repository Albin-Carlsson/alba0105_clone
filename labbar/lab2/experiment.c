extern char *strdup(const char*);
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //för strlen
#include <ctype.h> //för isdigit
#include "utils.h"



typedef bool check_func(char *);

typedef union {
    int int_value;
    float float_value;
    char *string_value;
} answer_t;
typedef answer_t convert_func(char*);




//kontroll funktioner
bool is_number(char *str){
    int length=strlen(str); //tar ut längden på strängen    
    int i=0;
     if (str[i]=='-'){
        if (length==1)
        {
            return false; //ett minus är inte ett tal
        }
        i=1;    //så skippar man första tecknet när vi kör isdigit
    }

    for(; i<length; ++i){
        if (!isdigit((unsigned char)str[i]))  //om strängen inte är ett tal
        {
            return false;
        }
    }
    return true;
}

//en sträng ar inte tom
bool not_empty(char *str)
{
    return strlen(str)>0;
}


answer_t ask_question (char *question, check_func *check, convert_func *convert)
{
    int buf_siz=255;
    char buf[buf_siz];
    bool valid_input=false;
    
    do
    {
        printf("%s", question);
        read_string(buf, buf_siz);
        //check if input is valid with check function
        valid_input= check(buf);
        if(!valid_input)
        {
            printf("Invalid input, try again \n");
        }
    }
    while (valid_input==false);

    //convert the input and return
    return convert(buf);
}

int ask_question_int2(char *question){
    answer_t answer= ask_question(question,is_number, (convert_func*) atoi);
    return answer.int_value; //svaret som ett heltal
}

char *ask_question_string2(char *question){
    return ask_question(question, not_empty, (convert_func *)strdup).string_value;
}




#include <stdio.h>


 

int read_string(char *buf, int buf_siz)
{
    int c;
    int count=0; //variabel för string-length
    do
    {
      c=getchar();   //tar nästa tecken
      buf[count]=c;   //lägger in karaktären i arrayen
      if(c!='\n')
      {
        count++;      //incrementerar counten
      }
    }
    while (c !='\n'&& count<buf_siz); //så länge strängen inte tar slut
    
    buf[count]='\0'; //null-terminate string
    return count;
}

char *ask_question_string(char *question, char *buf, int buf_siz)
{
  int answer= 0; //keep track if input was succesfully read
  
  do
  {
    printf("%s", question);
    answer= read_string(buf, buf_siz);

  }
  while (answer<1);
}

int main(void)
{
    int buf_siz= 255; //maximum size of the input
    int read=0;       //variable for number of characters succesfully read from input
    char buf[buf_siz];   //the array holding the string entered by the user

    puts("Läs in en sträng: ");   
    read= read_string(buf, buf_siz);  //gets the amount of characters read
    printf (" '%s' (%d tecken)\n", buf, read);   //prints string stored in buf + amount of characters

    puts("Läs in en sträng till: ");
    read= read_string(buf, buf_siz);
    printf (" '%s' (%d tecken)\n", buf, read);
    return 0;
}
#include <stdio.h>

void clear_input_buffer()
{
  int c;
   do
     {
       c = getchar();
     }
   while (c != '\n');
} 

int read_string(char *buf, int buf_siz)
{
    int i=0; //counter
    int c;
    while(i < buf_siz && c!='\n')
    {
        c=getchar();  //tar ut en karaktär
        buf[i]=c;     //lägger den i sträng arrayen
        i++;
    }
    
    if (buf[i]!= '\n')
    {
        clear_input_buffer();
    }

    buf[i-1]='\0';  //strängen vi läser är nullterminerad

    return i-1;
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
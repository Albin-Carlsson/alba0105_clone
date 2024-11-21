#include <stdio.h>

//swap med värdesemantik funkar inte pga när man anropar funktionen så skapas det
//kopior av x och y, de är dem som skickas till funktionen

void swap (int *a, int *b)
{
    int tmp= *a; //tmp får värden som a pekar på
    *a=*b;  //a pekar nu på samma värde som b
    *b=tmp;  //b pekar på tmp, alltså det som a pekade på förut
}

int main(void)
{
  int x = 7;
  int y = 42;
  swap(&x, &y); //skickar adresserna till x och y
  printf("%d, %d\n", x, y);
  return 0;
}
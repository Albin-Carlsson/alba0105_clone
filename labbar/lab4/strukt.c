#include <stdio.h>

struct point //deklarerar en struct som innehåller två fält, båda heltal
{
    int x;
    int y;
};

typedef struct point point_t; //definerar övanstående strukt som en typ som heter point_t
//point_t p={.x=10, .y=-42};  //puts the variabels into the struct

/*
struct point translate(point_t p1, point_t p2)  //definerar funktionen translate som tar emot två strukt, returnerar en strukt
{
    p1.x +=p2.x;  //x koordinaten i p1= x från p1 + x från p2
    p1.y +=p2.y;  //y koordinaten i p1= y från p1+ y från p2
    return p1; //returnerar en ny punkt, ändrar inte p1, eftersom struktar har värdesemantik(kopieras för funktionen)
}
*/

void translate(point_t *p1, point_t *p2) //definerar funktionen translate som tar emot två pekare på strukter
{
    p1->x += p2->x;  //vi lägger den x som p2 pekar på på x:en som p1 pekar på (summan)
    p1->y += p2->y;  //vi lägger den y som p2 pekar på på den y:n som p1 pekar på
}

int main()
{   
    point_t p = { .x = 10, .y = 7 };
    translate(&p, &p); //koordinaterna kommer dubbleras

    printf("point(x=%d,y=%d)\n", p.x, p.y);
    return 0;
}

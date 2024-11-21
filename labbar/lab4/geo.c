#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

struct point //deklarerar en struct som innehåller två fält, båda heltal
{
    int x;
    int y;
};

typedef struct point point_t; //definerar övanstående strukt som en typ som heter point_t


struct rectangle   //definerar en strukt för en rektangel, representeras av två punkter
{
    point_t p1;
    point_t p2;
};

typedef struct rectangle rectangle_t; //definerar rektangel strukten som en typ

 
void translate(point_t *p1, point_t *p2) //definerar funktionen translate som tar emot två pekare på strukter
{
    p1->x += p2->x;  //vi lägger den x som p2 pekar på på x:en som p1 pekar på (summan)
    p1->y += p2->y;  //vi lägger den y som p2 pekar på på den y:n som p1 pekar på
}

void print_point(point_t *p)  //funktion som printar ut strukter av typen point_t
{
    int x= p->x;  //tar x-värden från pekaren
    int y= p->y;  //tar y-värden från pekaren
    printf("(x-%d, y-%d)", x,y);
}

point_t make_point(int new_x, int new_y)
{
    point_t new_point; //skapar en strukt
    new_point.x=new_x;  //lägger i x värdet
    new_point.y=new_y;  //lägger i y värdet
    return new_point;  //returnerar den nya strukten
}

void print_rect(rectangle_t *rect)
{
    printf("rectangle(upper_left= ");
    print_point(&(rect->p1));
    printf(", lower_right= ");
    print_point(&(rect->p2));
}

rectangle_t make_rect(int x1, int y1, int x2, int y2)
{
    point_t p1=make_point(x1,y1);
    point_t p2=make_point(x2,y2);
    rectangle_t new_rect;
    new_rect.p1=p1;
    new_rect.p2=p2;
    return new_rect;
}

int area_rect(rectangle_t *rect)
{
    int x1=rect->p1.x;
    int x2=rect->p2.x;
    int y1=rect->p1.y;
    int y2=rect->p2.y;
    int area=(x1-x2)*(y1-y2);
    return abs(area);
}

bool intersects_rect(rectangle_t *r1, rectangle_t *r2)
{
   
    //kollar om en rektangel ligger till vänster genom att kolla på hörnet
    if (r1->p2.x < r2->p1.x || r2->p2.x < r1->p1.x) 
    {
        return false;
    }

    //kollar om de är övanpå
    if (r1->p2.y < r2->p1.y || r2->p2.y < r1->p1.y) 
    {
        return false;
    }

    //om inte
    return true;
}

int main()
{
    //rectangle_t rect = {make_point(0, 10), make_point(5, 0)};
    //print_rect(&rect);  // Skicka pekare till rektangeln
    //rectangle_t r =make_rect(1,2,3,4);  //skapar en rektangel
    //int area= area_rect(&r);  //räknar ut arean
    //printf("%d", area);   //skriver ut arean
    //print_rect(&r);

/*
    //testar intersect
    rectangle_t r1 = make_rect(0,10,5,0);
    rectangle_t r2 = make_rect(3,8,8,2);   
    if (intersects_rect(&r1, &r2)) {
        printf("The rectangles intersect.\n");
    } else {
        printf("The rectangles do not intersect.\n");
    }
*/

    return 0;
}
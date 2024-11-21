#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "../lab2/utils.h" 
#include <ctype.h> //för isalpha()- om det är en bokstav och isdigit()
#include <time.h>
#include <ctype.h> //for toupper()

//deklarerar en struct item för en vara
struct item{
    char *name;
    char *desc;
    int price;
    char *shelf;
};

//definerar typalias for strukten item
typedef struct item item_t;

void print_item (item_t *item)
{
    char *name=item->name;
    char *desc=item->desc;
    int price_kr=(item->price)/100; //kronor
    int price_or=item->price %100; //öre
    char *shelf=item->shelf;
    printf("Name: %s\nDesc: %s\nPrice: %d.%d SEK\nShelf: %s\n", name,desc, price_kr,price_or, shelf);
}

item_t make_item(char *name, char *desc, int price, char *shelf)
{
    item_t new_item;
    new_item.name=name;
    new_item.desc=desc;
    new_item.price=price;
    new_item.shelf=shelf;
    return new_item;
}


bool is_shelf(char *str)
{
    //om strängen är empty eller mer/mindre än 3 tecken som behövs
    if(strlen(str)==0 || strlen(str)!=3)
    {
        return false;
    }
    //om formatet stämmer
    if (isalpha(str[0]) && isdigit(str[1]) && isdigit(str[2]))
    {
        return true;
    }
    return false;
}

char *ask_question_shelf(char *question){
    return ask_question(question, is_shelf, (convert_func *)strdup).string_value;
}

item_t input_item()
{
    char *input_name=ask_question_string("What is the name of the product?");
    char *input_desc=ask_question_string("How would you describe the item?");
    int input_price=ask_question_int("What is the price?");
    char *input_shelf=ask_question_shelf("On what shelf is it?");
    item_t input_i= make_item(input_name, input_desc, input_price, input_shelf);
    return input_i;
}

char* random_word(char *array[], int size)
{
    int index=rand() % size; //slumpar ett tal inom size
    return array[index];
}

char* magick(char *arr1[], char *arr2[], char *arr3[], int size)
{
    char *buf = (char *)malloc(255 * sizeof(char));
    int pos=0;
    char *word1=random_word(arr1,size);
    while (*word1) //så länge karaktären är inte \0
    {
        char current_char=*word1; //tar karaktären som word1 pekar på, alltså den första
        buf[pos]=current_char; //lägger den i buf
        pos++; //incrementerar positionen i buf
        word1++; //för att ta nästa karaktär i word1
    } 
    buf[pos++]='-'; //lägger - till buf
    

    char *word2=random_word(arr2, size);
    while(*word2)
    {
        char current_char=*word2;
        buf[pos]=current_char;
        pos++;
        word2++;
    }
    buf[pos++]='-'; //lägger - till buf
    

    char *word3=random_word(arr3, size);
    while(*word3)
    {
        char current_char=*word3;
        buf[pos]=current_char;
        pos++;
        word3++;
    }

    buf[pos]='\0'; //nullterminerar strängen
    char *result=strdup(buf);
    free(buf);
    return result; 

}

void list_db(item_t *items, int no_items) //funktion för att skriva ut alla namn i databasen
{
    for(int i=0; i<no_items; ++i)
    {
        char *namn=items[i].name; //tar ut namnet i ordning
        printf("%d. %s \n", i+1, namn);  //skriver ut det med matchande index
    }
}


void edit_db(item_t *db)
{
    int item_index=0; //för att kunna kontrollera så att svaret ligger mellan 0 16
    do
    {
        item_index=ask_question_int("Which item would you like to edit?");
        if (item_index<=0 || item_index>16)
        {
            item_index=0;
        }
    }
    while (item_index==0);

    item_t *item = &db[item_index - 1]; //hämtar item som ska ändras
    print_item(item);
    item_t new_item=input_item();
    *item=new_item;
}

void print_menu()
{
    char *s1="[L]ägga till en vara ";
    char *s2="[T]a bort en vara ";
    char *s3="[R]edigera en vara ";
    char *s4="Ån[g]ra senaste ändringen ";
    char *s5="Lista [h]ela varukatalogen ";
    char *s6="[A]vsluta ";
    printf("\n%s\n%s\n%s\n%s\n%s\n%s\n",s1,s2,s3,s4,s5,s6);
}

bool is_character(char *str)
{
    return (not_empty(str)&&isalpha(str[0]));
}

char ask_question_menu()
{
    print_menu();  //skriver ut menyn
    bool valid_input=false; //för att kontrollera när svaret är giltig
    int buf_siz=255;
    char buf[buf_siz];
    char c; //valet
    printf("Mata in ditt val \n");
    while (valid_input==false)
    {
        read_string(buf,buf_siz);  //tar emot buf
        if(is_character(buf)) //om första tecken är en karaktär och non empty
        {
            c=toupper(buf[0]);
            //om inputen matchar med valen som är tillgängliga
            if( c=='L' || c=='T' || c=='R' || c=='G' || c=='H' || c=='A')
            {
                valid_input=true;
            }
            else
            {
                printf("Ej gilitg val, mata in ditt val igen.\n");
            }
        }
        else
        {
            printf("Ej gilitg val, mata in ditt val igen.\n");
        }
    }
    return c;
}

void add_item_to_db(item_t *db, int db_siz) //lägger till en item
{
    item_t new_item=input_item(); //tar emot de från input
    db[db_siz]= new_item; //lägger den i slutet
}

void remove_item_from_db(item_t *db, int *db_siz)
{
    list_db(db, *db_siz);
    int item_index=0;
    while (item_index==0)
    {
        item_index=ask_question_int("Which item would you like to edit?");
        if (item_index<=0 || item_index>*db_siz)
        {
            printf("The item doesn't exist.\n");
            item_index=0;
        }
    }
    item_index --;
    
    for (int i = item_index; i < *db_siz - 1; i++) {
        db[i] = db[i + 1];
    }
     (*db_siz)--;
}

void event_loop(item_t *db, int *db_siz)
{   bool stop=false;
    while(!stop)
    {
        char option=ask_question_menu();
        if (option=='L')
        {
            add_item_to_db(db, *db_siz);
        }

        if (option=='T')
        {
            remove_item_from_db(db, db_siz);
        }

        if (option=='R')
        {
            edit_db(db);
        }

        if (option=='G')
        {
            printf("Not yet implemented!");
        }

        if(option=='H')
        {
            list_db(db, *db_siz);
        }

        if (option=='A')
        {
            stop=true;
        }

    }
}

int main(int argc, char *argv[])
{

    srand(time(NULL));
    char *array1[]={"Extra", "Sharp", "Classic", "Modern", "New"}; //size 5
    char *array2[]={"ordinary", "beautiful", "strong", "handy", "helpful"}; //size 5
    char *array3[]={"lamp", "hammer", "knife", "battery", "machine"}; //size 5

    if (argc < 2)
    {
        printf("Usage: %s number\n", argv[0]);
    }

    else
    {
        item_t db[16]; //skapar arrayen db med plas för 16 item
        int db_siz=0; //antal varor i arrayen nu

        int items=atoi(argv[1]); //antalet varor som ska skapas, ges av användaren
        if (items>0 && items<=16)
        {
            for(int i=0; i<items; ++i)
            {
                //läs in en vara, lägg till den i arrayen, öka storleksräknaren
                item_t item=input_item();  //tar emot ett nytt item
                db[db_siz]=item;  //lägger den i arrayen
                ++db_siz;
            }
        }
        
        else
        {
            puts("Sorry, must have [1-16] items in database.");
            return 1; // Avslutar programmet!
        }

        for(int i=db_siz; i<16; ++i)
        {
            char *name = magick(array1, array2, array3, 5); // genererar ett namn
            char *desc = magick(array1, array2, array3, 5); // genererar en beskrivning
            int price = random() % 200000;
            char shelf[] = { random() % ('Z'-'A') + 'A',
                            random() % 10 + '0',
                            random() % 10 + '0',
                            '\0' };
            item_t item = make_item(name, desc, price, shelf);

            db[db_siz] = item;
            ++db_siz;
        }

        //skriv ut innehållet
        printf("Here's the updated list:\n");
        list_db(db, db_siz);

        event_loop(db, &db_siz);

    }
    return 0;
}


//TESTS FOR MAIN

//test for print_item()
/*
item_t i1={"apple", "red", 3050, "A25"};
print_item(&i1);
*/

//test för make_item()
/*
item_t i1= make_item("apple", "red", 305, "A25");
print_item(&i1);
*/

//test för input_item()
/*
item_t i1=input_item();
print_item(&i1);
*/

//test för is_shelf
/*
  char test[] = "AA12";
    bool result = is_shelf(test);
    
    if (result) {
        printf("Valid format.\n");
    } else {
        printf("Invalid format\n");
    }
*/

//test för random_word()
/*
    srand(time(NULL)); // Seed the random number generator

    char *arr[] = {"apple", "banana", "cherry"};
    char *word = random_word(arr, 3);
    printf("Random word: %s\n", word);
*/
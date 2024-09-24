#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "linked_list.h"


typedef struct list ioopm_list_t; 
typedef struct link ioopm_link_t;
typedef struct option option_t;
typedef bool ioopm_int_predicate(int value,int extra);
typedef void ioopm_apply_int_function(ioopm_link_t *link, int extra);

#define Success(link) (option_t) {.success=true, .ptr=link};
#define Failure() (option_t) {.success=false};

static option_t find_previous_link(ioopm_list_t *list, int index){
    //om indexet är negativ
    if (index<0)
    {
        return Failure();
    }
    
    int size=0;
    ioopm_link_t *current= list->first;

    //loopar genom listan medan vi inkrementerar size tills vi har hittat index
    do{
        if(size==index)
        {
            return Success(current);
        }
        size++;
        current=current->next;
    }
    while(current);
    return Failure();
}


ioopm_list_t *ioopm_linked_list_create(void){
    //allokerar minne för listan
    ioopm_list_t *lst=calloc(1,sizeof(ioopm_list_t));

    //allokerar minne för dummy och initierar de
    ioopm_link_t *dummy=calloc(1,sizeof(ioopm_link_t));
    dummy->value=0;
    dummy->next=NULL;

    //länkar dummyn till listan
    lst->first=dummy;
    lst->last=dummy;
    lst->size=0;

    return lst;
}

void ioopm_linked_list_destroy(ioopm_list_t *list){
    ioopm_link_t *current=list->first; //tar dummy
    ioopm_link_t *next=NULL;
    while (current!=NULL) //om dummy pekar inte på något länk
    {
        next=current->next; //sparar nästa pekare
        free(current);   //frigör current nuvarande länk
        current=next;    //sätt current till nästa länk den pekar på
    }
    free(list); //frigör listan
}

void ioopm_linked_list_append(ioopm_list_t *list, int value){
    ioopm_link_t *new_link=malloc(sizeof(ioopm_link_t));
    new_link->value=value;
    new_link->next=NULL;
    list->last->next=new_link;
    list->last=new_link;
    list->size=list->size +1;
}


void ioopm_linked_list_prepend(ioopm_list_t *list, int value){
    ioopm_link_t *new_link=malloc(sizeof(ioopm_link_t));
    ioopm_link_t *current=list->first;
    new_link->value=value;
    new_link->next=current->next;
    current->next=new_link;
    list->size=list->size +1;
}

option_t ioopm_linked_list_insert(ioopm_list_t *list, int index, int value){
    //undersöker om den hittar en previous link
    option_t result=find_previous_link(list, index);
    if (!result.success){
        return Failure();
    }
    //allokerar minne, kollar om de finns allokerat
    ioopm_link_t *new_link = malloc(sizeof(ioopm_link_t));
    if (!new_link) {
        return Failure(); 
    }
    new_link->value = value; //sätter in valuen

    //sparar länken som ska vara innan samt vad den pekar på
    ioopm_link_t *previous=result.ptr;  
    ioopm_link_t *next=previous->next;

    //länkar previous med new_link med next länk
    new_link->next=next;
    previous->next=new_link;
    list->size=list->size +1;
    return Success(new_link);
}

option_t ioopm_linked_list_remove(ioopm_list_t *list, int index){
    //undersöker om den hittar en previous link
    option_t result=find_previous_link(list, index);
    if (!result.success){
        return Failure();
    }
    
    //hämtar previous och current länk
    ioopm_link_t *previous=result.ptr;
    ioopm_link_t *to_remove=result.ptr->next;

    //kontrollerar så att den är inte null
    if (!to_remove) {
        return Failure();  
    }

    //sparar länken efter 
    ioopm_link_t *next= to_remove->next;
    
    if(!next)
    {
        list->last=previous; //om nästa länk var null, då var vår länk den sista
        //vi sätter då previous som sista nu 
    }

    ioopm_link_t *removed=to_remove;
    free(to_remove);
    previous->next=next;
    list->size=list->size -1;
    return Success(removed);
}

option_t ioopm_linked_list_get(ioopm_list_t *list, int index){
    //undersöker om den hittar en previous link
    option_t result=find_previous_link(list, index);
    if (!result.success){
        return Failure();
    }
    
    //hämtar previous och current länk
    ioopm_link_t *to_get=result.ptr->next;

    //kontrollerar så att den är inte null
    if (!to_get) {
        return Failure();  
    }
    return Success(to_get);
}

bool ioopm_linked_list_contains(ioopm_list_t *list, int element){
    ioopm_link_t * current = list->first->next; // hoppa Ã¶ver dummy

    if( current == NULL){
        return false; 
    }

    for (int i = 0; current != NULL; i ++){ 
        int value = current->value;
        if((value == element)) {
            return true;
        }
        current = current->next;
    }
    return false;
}

int ioopm_linked_list_size(ioopm_list_t *list){
    return list->size;

}


bool ioopm_linked_list_is_empty(ioopm_list_t *list){
    return list->size==0;
}


void ioopm_linked_list_clear(ioopm_list_t *list){
    ioopm_link_t *current=list->first->next; //tar det som dummy pekar på
    ioopm_link_t *next=NULL;
    while (current!=NULL) //om dummy pekar inte på något länk
    {
        next=current->next; //sparar nästa pekare
        free(current);   //frigör current nuvarande länk
        current=next;    //sätt current till nästa länk den pekar på
    }
    list->size=0;
    list->last=list->first;

    //sätter dummy pointer tillbaka till NULL
    list->first->next=NULL;
    
}

bool ioopm_linked_list_all(ioopm_list_t *list, ioopm_int_predicate *prop, int extra){
    if (ioopm_linked_list_is_empty(list)){
        return false;
    }

    ioopm_link_t *link=list->first->next;
    while(link){
        if(!prop(link->value, extra)){
            return false;
        }
        link=link->next;
    }
    return true;
}

bool ioopm_linked_list_modulo(int value, int extra) {
    int rest = value % extra;
    return (rest == 0);
}

bool ioopm_linked_list_any(ioopm_list_t *list, ioopm_int_predicate *prop, int extra){
    if (ioopm_linked_list_is_empty(list)){
        return false;
    }

    ioopm_link_t *link=list->first->next;
    while(link){
        if(prop(link->value, extra)){
            return false;
        }
        link=link->next;
    }
    return false;
}


void ioopm_linked_list_apply_to_all(ioopm_list_t *list, ioopm_apply_int_function *fun, int extra){
    if (ioopm_linked_list_is_empty(list)){
        printf("Empty list");
        return;
    }

    ioopm_link_t *current=list->first->next;
    while(current)
    {
        fun(current, extra);
        current=current->next;
    }
}

void ioopm_linked_list_change_all(ioopm_link_t *link, int extra){
    link->value=extra;
}
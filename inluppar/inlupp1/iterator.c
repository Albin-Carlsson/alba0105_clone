#include "iterator.h"
#include "common.h"
#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <string.h>


typedef struct iter ioopm_list_iterator_t;


ioopm_list_iterator_t *ioopm_list_iterator(ioopm_list_t *list) {
    ioopm_list_iterator_t *new_iter = malloc(sizeof(ioopm_list_iterator_t));
    if (!new_iter) return NULL;
    new_iter->current = list->first;
    new_iter->list = list;
    return new_iter;
}


bool ioopm_iterator_has_next(ioopm_list_iterator_t *iter) {
    if (iter->current == NULL) return false;
    return iter->current->next != NULL;
}



elem_t ioopm_iterator_next(ioopm_list_iterator_t *iter) {
    if (iter->current == NULL) {
        puts("Iterator is at the end of the list or the list is empty");
        return int_elem(0); // Eller hantera det på ett sätt som passar din applikation
    }
    ioopm_link_t * new_link = iter->current->next;
    if (new_link == NULL) {
        puts("End of list");
        return int_elem(0);
    }
    iter->current = new_link;
    return new_link->value;
}


void ioopm_iterator_reset(ioopm_list_iterator_t *iter){

    iter->current = iter->list->first;
}


elem_t ioopm_iterator_current(ioopm_list_iterator_t *iter){
    elem_t elem = iter->current->value;

    return elem;
}

void ioopm_iterator_destroy(ioopm_list_iterator_t *iter){
    free(iter);
}



static ioopm_link_t * find_previous_link(ioopm_list_iterator_t *iter, ioopm_list_t * list){

    ioopm_link_t * current = list->first->next;

    while(current){

        if(current == iter->current){
            return current;
        }
        current = current->next;
    }

    return iter->current;
}

/*
int ioopm_iterator_remove(ioopm_list_iterator_t *iter){

    ioopm_link_t * new_current= iter->current->next;

    ioopm_link_t * to_remove = iter->current;

    int to_remove_value = to_remove->value;

    free(to_remove);

    ioopm_list_t * list= iter->list; 

    ioopm_link_t * prev = find_previous_link(iter, list);

    prev->next = new_current;

    iter->current = new_current;

    return to_remove_value;

}
*/
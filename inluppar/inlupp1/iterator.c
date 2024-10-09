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


ioopm_list_iterator_t* ioopm_list_iterator(ioopm_list_t* list) {
    ioopm_list_iterator_t* new_iter = malloc(sizeof(ioopm_list_iterator_t));
    if (!new_iter){
       return NULL; 
    } 
    new_iter->current = list->first;
    new_iter->list = list;
    return new_iter;
}


bool ioopm_iterator_has_next(ioopm_list_iterator_t* iter) {
    if (iter->current == NULL){
        return false;
    }
    return iter->current->next != NULL;
}



elem_t ioopm_iterator_next(ioopm_list_iterator_t *iter){
    ioopm_link_t * new_link = iter->current->next;
    if(new_link == NULL){
        iter->current = NULL;
        puts("End of list");
        elem_t zero;
        char * return_val = zero.c= NULL;
        return zero;
    }

    iter->current = new_link;
    elem_t elem = new_link->value;
    return elem;
}


void ioopm_iterator_reset(ioopm_list_iterator_t* iter) {
    iter->current = iter->list->first;
}


elem_t ioopm_iterator_current(ioopm_list_iterator_t* iter) {
    elem_t elem = iter->current->value;
    return elem;
}

void ioopm_iterator_destroy(ioopm_list_iterator_t* iter) {
    free(iter);
}



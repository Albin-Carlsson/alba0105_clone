#pragma once
#include "linked_list.h"
#include "common.h"

/**
 * @file iterator.h
 * @author Annika Kuusrainen and Alexandra Barbu
 * @date 7 October 2024
 * @brief Iterator for linked lists.
 * 
 * This file  defines structur and functions for an iteratior that allows sequential traversal over a linked list. 
 * The iterator can move through the list, but only forwards not backwards.
 * The iterator can access elements and remove elements. An insert function has not been created. 
 * 
 * The iterator gives efficient access to the elements in the list without needing direct access to the list internals.
 * @see $CANVAS_OBJECT_REFERENCE$/assignments/gb54499f3b7b264e3af3b68c756090f5
 */

/// @brief The iterator struct for a list, holding the current element and a reference to the list.
typedef struct iter ioopm_list_iterator_t;

/// @brief Struct definition for the iterator.
struct iter {
    ioopm_link_t * current; //points to the current element in the list.
    ioopm_list_t * list; // points to the list being itertaed over.
};


/// @brief Create an iterator for a given list
/// @param list the list to be iterated over
/// @return an iteration positioned at the start of list
ioopm_list_iterator_t *ioopm_list_iterator(ioopm_list_t *list);


/// @brief Checks if there are more elements to iterate over
/// @param iter the iterator
/// @return true if there is at least one more element 
bool ioopm_iterator_has_next(ioopm_list_iterator_t* iter);

/// @brief Step the iterator forward one step
/// @param iter the iterator
/// @return elem_t the next element
elem_t ioopm_iterator_next(ioopm_list_iterator_t* iter);

/// @brief Reposition the iterator at the start of the underlying list
/// @param iter the iterator
void ioopm_iterator_reset(ioopm_list_iterator_t* iter);

/// @brief Return the current element from the underlying list
/// @param iter the iterator
/// @return elem_t the current element
elem_t ioopm_iterator_current(ioopm_list_iterator_t* iter);

/// @brief Destroy the iterator and return its resources
/// @param iter the iterator
void ioopm_iterator_destroy(ioopm_list_iterator_t* iter);
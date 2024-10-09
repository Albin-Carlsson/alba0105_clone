#pragma once
#include "common.h"
#include <stdbool.h>

/*
 * @file linked_list.h
 * @author Annika Kuusrainen and Alexandra Barbu
 * @date 07 Oct 2024
 * @brief Simple generic hash table implementation.
 *
 * This header file conains the structure and function declarations for a linked list. 
 * The list supports operations such as inserting, 
 * removing, retrieving elements and applying predicate and functions to the elements in a linked list. 
 * All elements in a list must be of the same data type, 
 * but different lists can have different data types. Beware that when creating a new linked list call the function with 
 * correct equality function to match the right datatype of the list. 
 * 
 * @see $CANVAS_OBJECT_REFERENCE$/assignments/gb54499f3b7b264e3af3b68c756090f52
 */


typedef struct list ioopm_list_t;
typedef struct link ioopm_link_t;
typedef struct option_list option_list_t;

/// @brief Function pointer type for a predicate that evaluates a condition on an element.
/// @param value The integer element from the linked list to be evaluated.
/// @param extra An additional element that may provide context or information 
/// relevant to the evaluation of the predicate.
/// @return True if the predicate holds for the given element, else false.
typedef bool ioopm_int_predicate(elem_t value, elem_t extra);

/// @brief Function pointer type for applying a function to a linked list element.
/// @param link A pointer to the link in the linked list that contains the element 
/// to be processed.
/// @param extra An additional element that may provide context or information 
/// relevant to the application of the function.
typedef void ioopm_apply_int_function(ioopm_link_t* link, elem_t extra);

/// @struct list, the struct definitions for a linked list
struct list {
    ioopm_link_t* first;
    ioopm_link_t* last;
    ioopm_eq_function* eq_fn; // Function to compare elements
    int size;
};


/// @struct link, the struct definition for a link
struct link {
    elem_t value;
    ioopm_link_t* next;
};


/// @struct option_list, the struct for option_list which is used to 
/// indicate if a operation was succesful and the affected link and value
struct option_list
{
    bool success; // indicates if the operation was successful
    ioopm_link_t *ptr; // pointer to the affected link
    elem_t value; // value of the affected link or value related to function
};


/// @brief Creates a new empty list
/// @return an empty linked list
ioopm_list_t* ioopm_linked_list_create(ioopm_eq_function* eq_fn);

/// @brief Tear down the linked list and return all its memory (but not the memory of the elements)
/// @param list the list to be destroyed
void ioopm_linked_list_destroy(ioopm_list_t* list);

/// @brief Insert at the end of a linked list in O(1) time
/// @param list the linked list that will be appended
/// @param value the value to be appended
void ioopm_linked_list_append(ioopm_list_t* list, elem_t value);

/// @brief Insert at the front of a linked list in O(1) time
/// @param list the linked list that will be prepended to
/// @param value the value to be prepended
void ioopm_linked_list_prepend(ioopm_list_t* list, elem_t value);

/// @brief Insert an element into a linked list in O(n) time.
/// The valid values of index are [0,n] for a list of n elements,
/// where 0 means before the first element and n means after
/// the last element.
/// @param list the linked list that will be extended
/// @param index the position in the list
/// @param value the value to be inserted 
/// @return option_list_t which indicates if the process was a success or fail, 
/// as well as the new link pointer and its value(if succedeed)
option_list_t ioopm_linked_list_insert(ioopm_list_t* list, int index, elem_t value);

/// @brief Remove an element from a linked list in O(n) time.
/// The valid values of index are [0,n-1] for a list of n elements,
/// where 0 means the first element and n-1 means the last element.
/// @param list the linked list
/// @param index the position in the list
/// @return option_list_t if the process succedeed, and contain a NULL pointer and the value that was removed.

option_list_t ioopm_linked_list_remove(ioopm_list_t* list, int index);

/// @brief Retrieve an element from a linked list in O(n) time.
/// The valid values of index are [0,n-1] for a list of n elements,
/// where 0 means the first element and n-1 means the last element.
/// @param list the linked list that will be extended
/// @param index the position in the list
/// @return option_list_t bool indicating success or fail,
///a pointer to the link and the value of the link
option_list_t ioopm_linked_list_get(ioopm_list_t* list, int index);

/// @brief Test if an element is in the list
/// @param list the linked list
/// @param element the element sought
/// @return true if element is in the list, else false
bool ioopm_linked_list_contains(ioopm_list_t* list, elem_t element);

/// @brief Lookup the number of elements in the linked list in O(1) time
/// @param list the linked list
/// @return the number of elements in the list
int ioopm_linked_list_size(ioopm_list_t* list);

/// @brief Test whether a list is empty or not
/// @param list the linked list
/// @return true if the number of elements int the list is 0, else false
bool ioopm_linked_list_is_empty(ioopm_list_t* list);

/// @brief Remove all elements from a linked list
/// @param list the linked list
void ioopm_linked_list_clear(ioopm_list_t* list);

/// @brief Test if a supplied property holds for all elements in a list.
/// The function returns as soon as the return value can be determined.
/// @param list the linked list
/// @param prop the property to be tested (function pointer)
/// @param extra an additional argument (may be NULL) that will be passed to all internal calls of prop
/// @return true if prop holds for all elements in the list, else false
bool ioopm_linked_list_all(ioopm_list_t* list, ioopm_int_predicate* prop, elem_t extra);

/// @brief Test if a supplied property holds for any element in a list.
/// The function returns as soon as the return value can be determined.
/// @param list the linked list
/// @param prop the property to be tested
/// @param extra an additional argument (may be NULL) that will be passed to all internal calls of prop
/// @return true if prop holds for any elements in the list, else false
bool ioopm_linked_list_any(ioopm_list_t* list, ioopm_int_predicate* prop, elem_t extra);

/// @brief Apply a supplied function to all elements in a list.
/// @param list the linked list
/// @param fun the function to be applied
/// @param extra an additional argument (may be NULL) that will be passed to all internal calls of fun
void ioopm_linked_list_apply_to_all(ioopm_list_t* list, ioopm_apply_int_function* fun, elem_t extra);

/// @brief Test function for ioopm_linked_list_all
/// @param value value given from link
/// @param extra the modulo wished
/// @return bool, if the number is divisible with the number given
bool ioopm_linked_list_modulo(elem_t value, elem_t extra);


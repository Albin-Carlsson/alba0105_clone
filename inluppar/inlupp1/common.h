#pragma once

#include <stdbool.h>
#include <stdlib.h>

typedef union elem elem_t;

union elem
{
    int i;
    bool b;
    char *c;
    float f;
};

/// Compares two elements and returns true if they are equal
typedef bool ioopm_eq_function(elem_t a, elem_t b);

#define int_elem(x) (elem_t) { .i=(x) }
#define char_elem(x) (elem_t) { .c =(x) }

/// @brief Compares two integers and returns true if they are equal
/// @param a union a, expected to be an int
/// @param b union b, expected to be an int
/// @return bool, if the integers are equal
bool int_compare(elem_t a, elem_t b);


/// @brief Compares two strings, returns true if they are equal
/// @param a string a, from union a
/// @param b union a, expected to be a string
/// @return bool, if the strings are equal
bool char_compare(elem_t a, elem_t b);


/// @brief Compares two booleans, returns true if they are equal
/// @param a union a, expected to be a bool
/// @param b union b, expected to be a bool
/// @return bool, if the booleans are equal
bool bool_compare(elem_t a, elem_t b);


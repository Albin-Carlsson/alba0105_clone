#pragma once

#include <stdbool.h>
#include <stdlib.h>

/**
 * @file common.h
 * @author Annika Kuusrainen and Alexandra Barbu
 * @date 07 Oct 2024
 * @brief This header file defines a union type `elem_t` to represent multiple data types,
 * including integers, booleans, strings, and floats. It also includes function 
 * declarations for comparing elements of these types for equality.
 * 
 * The `elem_t` union is used to store values of different types in a single variable. 
 * The provided equality functions allow for comparisons between elements of 
 * the union.
 * 
 * @see $CANVAS_OBJECT_REFERENCE$/assignments/gb54499f3b7b264e3af3b68c756090f52
 */


/// @brief Union type to hold different types of elements.
typedef union elem elem_t;

/// @brief Union definition for storing various data types.
union elem{
    int i;  //integer value
    bool b; //boolean valuea
    char* c;  //character pointer (for strings)
    float f;  //floating point value
};

/// @brief Function pointer type for comparing two elements for equality.
/// @param a The first element to compare.
/// @param b The second element to compare.
/// @return True if the elements are equal, otherwise false.
typedef bool ioopm_eq_function(elem_t a, elem_t b);

/// @brief Macro to create an element from an integer value.
/// @param x The integer value to be wrapped in the elem_t union.
/// @return An elem_t union containing the integer.
#define int_elem(x) (elem_t) { .i=(x) }

/// @brief Macro to create an element from a string value.
/// @param x The string value to be wrapped in the elem_t union.
/// @return An elem_t union containing the string.
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


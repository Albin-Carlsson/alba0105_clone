#pragma once

#include "linked_list.h"
#include <stdbool.h>
#include <stdlib.h>

/**
 * @file hash_table.h
 * @author Annika Kuusrainen and Alexandra Barbu
 * @date 07 Oct 2024
 * @brief Simple generic hash table implementation.
 *
 * This header file contains the structures for the hash table and other structs used to implement the generic hash table. The hash table is generic and can store different types of key value pairs,
 * which are represented by elem_t. This hash table uses linked lists to handle collisions in each bucket (chaining).
 * It is also possible to creeate custom hash functions and equality functions for keys and value. One hash table can only contain one type of data,
 * meaning you need to keep track of the datatype for each hash table, and make sure you call functions with the matching data type.
 * Beware when creating a hash table make sure to call with right equality function to match the datatype of the hash table.
 *
 * The hash table has a fixed number of buckets (NO_Buckets), this number can be adjusted.
 *
 * The hash table supports basic operations like insertion, lookup and deletion.
 * The ht provides support for applying functions to all elements and checking predicates for all key-value pairs in the ht.
 * @see $CANVAS_OBJECT_REFERENCE$/assignments/gb54499f3b7b264e3af3b68c756090f52
 */


 //DEFINITIONS
typedef struct hash_table ioopm_hash_table_t;
typedef struct option option_t;
typedef struct entry entry_t;

struct entry {
  elem_t key;       // holds the key
  elem_t value;   // holds the value
  entry_t* next; // points to the next entry (possibly NULL)
};


/**
 * @typedef ioopm_predicate
 * @brief Function pointer type for predicates used in the ht
 * A predicate function takes a key, value, and an extra argument,
 * a equality function is also passed in the function,
 * returning true or false based on some condition.
 */

typedef bool ioopm_predicate(elem_t key, elem_t value, elem_t extra, ioopm_eq_function* eq_fn);
/**
 * @typedef ioopm_apply_function
 * @brief Function pointer type for applying a operation to hash table elements.
 * A function that takes a key, value and an extra argument and applies some operation.
 */
typedef void ioopm_apply_function(elem_t key, elem_t* value, elem_t extra);

/**
 * @typedef ioopm_hash_func
 * @brief Function pointer type for hash functions used in the hash table.
 * A hash function takes a key and returns an integer hash value that is
 * used to find the bucket in the hash table.
 */
typedef int ioopm_hash_function(elem_t);

/**
 * @struct option
 * @brief option is used as a return value in functions where we want to be able to signal if something has gone wrong,
 but also indictae a successful operation. Option also returns the value in a
 */
struct option {
  bool success;  //whether the lookup was succesful
  elem_t value;   //the value associated with the key
};


/// @brief Create a new hash table
/// @param eq_fn_value a compare function for values
/// @param eq_fn_key a compare function for keys
/// @param hash_function a hash function for keys
/// @return A new empty hash table
ioopm_hash_table_t* ioopm_hash_table_create(ioopm_eq_function* eq_fn_value, ioopm_eq_function* eq_fn_key, ioopm_hash_function* hash_function);

/// @brief Delete a hash table and free its memory
/// @param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t* ht);

/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t* ht, elem_t key, elem_t value);

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @return the value mapped to by key 
option_t ioopm_hash_table_lookup(ioopm_hash_table_t* ht, elem_t key);

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @return the value mapped to by key 
option_t ioopm_hash_table_remove(ioopm_hash_table_t* ht, elem_t key);

/// @brief returns the number of key => value entries in the hash table
/// @param h hash table operated upon
/// @return the number of key => value entries in the hash table
int ioopm_hash_table_size(ioopm_hash_table_t* ht);

/// @brief checks if the hash table is empty
/// @param h hash table operated upon
/// @return true is size == 0, else false
bool ioopm_hash_table_is_empty(ioopm_hash_table_t* ht);

/// @brief clear all the entries in a hash table
/// @param ht hash table operated upon
void ioopm_hash_table_clear(ioopm_hash_table_t* ht);

/// @brief return the keys for all entries in a hash map (in no particular order, but same as ioopm_hash_table_values)
/// @param ht hash table operated upon
/// @return an array of keys for hash table h
ioopm_list_t* ioopm_hash_table_keys(ioopm_hash_table_t* ht);

/// @brief return the values for all entries in a hash map (in no particular order, but same as ioopm_hash_table_keys)
/// @param ht hash table operated upon
/// @return an array of values for hash table h
ioopm_list_t* ioopm_hash_table_values(ioopm_hash_table_t* ht);

/// @brief check if a hash table has an entry with a given key
/// @param ht hash table operated upon
/// @param key the key sought
bool ioopm_hash_table_has_key(ioopm_hash_table_t* ht, elem_t key);

/// @brief check if a hash table has an entry with a given value
/// @param ht hash table operated upon
/// @param value the value sought
bool ioopm_hash_table_has_value(ioopm_hash_table_t* ht, elem_t value);

/// @brief check if a predicate is satisfied by all entries in a hash table
/// @param ht hash table operated upon
/// @param pred the predicate
/// @param arg extra argument to pred
/// @param eq_fn compare function for values or keys, depending on pred function
/// @returns true if all elements in ht satisfy pred otherwise false
bool ioopm_hash_table_all(ioopm_hash_table_t* ht, ioopm_predicate* pred, elem_t arg, ioopm_eq_function* eq_fn);

/// @brief check if a predicate is satisfied by any entry in a hash table
/// @param ht hash table operated upon
/// @param pred the predicate
/// @param arg extra argument to pred
/// @param eq_fn compare function for values or keys, depending on pred function
/// @returns true if any element in ht satisfy pred otherwise false
bool ioopm_hash_table_any(ioopm_hash_table_t* ht, ioopm_predicate* pred, elem_t arg, ioopm_eq_function* eq_fn);

/// @brief apply a function to all entries in a hash table
/// @param h hash table operated upon
/// @param apply_fun the function to be applied to all elements
/// @param arg extra argument to apply_fun
void ioopm_hash_table_apply_to_all(ioopm_hash_table_t* ht, ioopm_apply_function* apply_fun, elem_t arg);

/// @brief hash function for an integer
/// @param elem expects an integer to be hashed
/// @return int, to be used as a key
int int_key_hfunc(elem_t elem);

/// @brief hash function for a string
/// @param elem expects a string to be hashed
/// @return int, to be used as key
int string_key_hfunc(elem_t elem);

/// @brief Helper function for ioopm_hash_table_insert. 
///   Updates an existing key's value or inserts a new key-value pair into the bucket.
/// @param bucket The head of the linked list (bucket).
/// @param key The key to insert or update.
/// @param value The value to associate with the key.
/// @param eq_fn The equality function used to compare keys.
void update_or_insert(entry_t* bucket, elem_t key, elem_t value, ioopm_eq_function* eq_fn);

/// @brief helper function for ioopm_hash_table_insert
///   Initializes a bucket with a new key-value pair as its first entry.
/// @param bucket The bucket to initialize.
/// @param key The key to insert.
/// @param value The value to associate with the key.
void initialize_bucket(entry_t* bucket, elem_t key, elem_t value);

/// @brief Helper function for ioopm_hash_table_insert
/// Checks if the bucket is uninitialized and matches the given key.
/// Used to determine whether to initialize the bucket with a new entry.
/// @param bucket The bucket to check.
/// @param key The key being inserted.
/// @param eq_fn The equality function for keys.
/// @return true if the bucket is uninitialized and matches the key, false otherwise.
bool is_empty_and_matching(entry_t* bucket, elem_t key, ioopm_eq_function* eq_fn);


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hash_table.h"

typedef struct entry entry_t;
typedef struct hash_table ioopm_hash_table_t;

typedef struct option option_t; //for lookup

struct option
{
  bool success;  //whether the lookup was succesful
  char *value;   //the value associated with the key
};


//macros
#define Success(v)      (option_t) { .success = true, .value = v };
#define Failure()       (option_t) { .success = false };
#define Successful(o)   (o.success == true)
#define Unsuccessful(o) (o.success == false)

struct entry 
{
    int key;       // holds the key
    char *value;   // holds the value
    entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
    entry_t buckets[17]; // array of pointers to entry_t
};

ioopm_hash_table_t *ioopm_hash_table_create(void) 
{
    // Allocate space for a ioopm_hash_table_t and set buckets to NULL with calloc
    ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
    return result;
}

void entry_destroy(entry_t *entry) 
{
    entry_t *current = entry;
    entry_t *next_entry = NULL;

    while (current) 
    {
        next_entry = current->next;
        free(current);  // Free the current entry
        current = next_entry;  // Move to the next entry in the list
    }
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) 
{
    for (int i = 0; i < 17; i++) 
    {
        entry_destroy(&ht->buckets[i]);  // Destroy all entries in each bucket
    }

    free(ht);  // Free the hash table itself
}

static entry_t *entry_create(int key, char *value, entry_t *next) 
{
    entry_t *new_entry = malloc(sizeof(entry_t));  // Allocate space for new entry

    new_entry->key = key;      // Set key
    new_entry->value = value;  // Set value
    new_entry->next = next;    // Set next pointer

    return new_entry;
}

static entry_t *find_previous_entry_for_key(entry_t *head, int key) 
{
    entry_t *current = head->next;
    entry_t *previous = NULL;

    while (current && current->key < key) 
    {
        previous = current;  // Move to the next entry
        current = current->next;
    }

    // Return the previous entry if it exists, or NULL if no previous entry is found
    return previous;
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value) 
{
  // Calculate the bucket for this entry
    int bucket = key % 17;

    // Search for the previous entry for a key
    entry_t *prev = find_previous_entry_for_key(&ht->buckets[bucket], key);
    entry_t *next = prev->next;

    if (next != NULL && next->key == key) {
        // Update the value if the key already exists
        next->value = value;
    } 
    else 
    {
      prev->next = entry_create(key, value, next);
    }
  
}



option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key) 
{
   /// Find the previous entry for key
    entry_t *tmp = find_previous_entry_for_key(&ht->buckets[key % 17], key);
    entry_t *next = tmp->next;

    if (next && next->key == key) 
    {
        // Return success with the found value
        return Success(next->value);
    } 
    else 
    {
        // Return failure
        return Failure();
    }
}


option_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key)
{
    int bucket= key%17; 
    entry_t *prev = find_previous_entry_for_key(&ht->buckets[bucket], key);
    entry_t *to_remove=prev->next;
    char *value=to_remove->value;
    if (to_remove->key!=key || to_remove==NULL)
    {
        return Failure();
    }
    else
    {
        prev->next= to_remove->next;
        
        free(to_remove);
        return Success(value);
    }

}


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "hash_table.h"
#define No_Buckets 17

#define Success(v)      (option_t) { .success = true, .value = v };
#define Failure()       (option_t) { .success = false };
#define Successful(o)   (o.success == true)
#define Unsuccessful(o) (o.success == false)


typedef struct entry entry_t;
typedef struct hash_table ioopm_hash_table_t;
typedef struct option option_t;


struct entry
{
  int key;       // holds the key
  char *value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  entry_t buckets[No_Buckets];
};





ioopm_hash_table_t *ioopm_hash_table_create(void) {

  ioopm_hash_table_t *create_ht = calloc(1, sizeof(ioopm_hash_table_t));
  

  /*
      for (int i = 0; i < No_Buckets; ++i) {
        create_ht->buckets[i].key = 0;  
        create_ht->buckets[i].value = NULL; 
        create_ht->buckets[i].next= NULL;  

      }

      */

      
  return create_ht;
}

void entry_destroy( entry_t * entry) {

    entry_t * current = entry->next;
    entry_t * next = NULL;

    while (current) {
        
        next = current->next;
        free(current);
        current = next; 

    }

}


void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) {

    for ( int i = 0 ; i <  No_Buckets; i++) {
        entry_destroy(&ht->buckets[i]);
    }

    free(ht);
}

static entry_t *entry_create( int key, char * value, entry_t * next ){

    entry_t * new_entry = malloc(sizeof(entry_t)); // allocate space in memorie for new link
    new_entry -> key = key; // set key to key in new entry
    new_entry -> next = next;  // set next pointer in new link to next
    new_entry -> value = value;

   
    return new_entry;

}


static entry_t *find_previous_entry_for_key(entry_t * head, int key1){

    entry_t* current = head -> next;
    entry_t* previous = head;

  while (current != NULL && current -> key < key1) {
   previous = previous -> next;
   current = current-> next;

  }
    
   return previous;
}




void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value){

  if (key < 0) {
    key = abs(key);
  }

  /// Calculate the bucket for this entry
  int bucket = key % No_Buckets;
  /// Search for an existing entry for a key
  entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket], key);
  entry_t *next = entry-> next;

  /// Check if the next entry should be updated or not
  if (next != NULL && next->key == key)
    {
      next->value = value;
    }
  else
    {
      entry->next = entry_create(key, value, next);
    }

}

option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key) {

  if (key < 0) {
    key = abs(key);
  }

  entry_t *tmp = find_previous_entry_for_key(&ht->buckets[key % No_Buckets], key);

  if (tmp->next == NULL){
    return Failure();
  }

  entry_t *to_lookup = tmp->next;

  if(to_lookup-> key != key){

    return Failure();
  }

  if (to_lookup && to_lookup->value)
  {
    option_t result = { .success = true, .value = to_lookup->value };
    return result;
  }
else
  {
    option_t result = { .success = false };
    return result;
  }

}

option_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key)
{
    int bucket= key%No_Buckets; 
    entry_t *prev = find_previous_entry_for_key(&ht->buckets[bucket], key);
    
  if (prev->next == NULL){
    return Failure();
  }

    entry_t *to_remove =prev->next;
    //entry_t * to_remove = current; 
    char * value = to_remove->value;
    
    if (to_remove-> key != key)  
    {
        return Failure();
    }
    else
    {
      prev->next = to_remove->next;
      free(to_remove);

      return Success(value);
    }
}

int ioopm_hash_table_size(ioopm_hash_table_t *ht){
    int size=0;
    for(int i=0; i<No_Buckets; ++i)
    {
        //exkluderar dummy
        entry_t *current_bucket=&ht->buckets[i];
        entry_t *current_entry=current_bucket->next;
        while (current_entry){
            size+=1;
            current_entry=current_entry->next;
        }
    }
    return size;
}

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
  return ioopm_hash_table_size(ht) == 0;
}


void ioopm_hash_table_clear(ioopm_hash_table_t *ht){
    for ( int i = 0 ; i <  No_Buckets; i++) {
        entry_destroy(&ht->buckets[i]);
        ht->buckets[i].next = NULL;
    }
}

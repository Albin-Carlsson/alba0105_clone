#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "hash_table.h"
#define No_Buckets 17

#define Success(v)      (option_t) { .success = true, .value = v };
#define Failure()       (option_t) { .success = false };
#define Successful(o)   (o.success == true)
#define Unsuccessful(o) (o.success == false)


typedef struct entry entry_t;
typedef struct hash_table ioopm_hash_table_t;
typedef struct option option_t;
typedef bool ioopm_predicate(elem_t key, elem_t value, elem_t extra, ioopm_eq_function *eq_fn);
typedef void ioopm_apply_function(elem_t key, elem_t *value, elem_t extra);


struct entry
{
  elem_t key;       // holds the key
  elem_t value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  entry_t buckets[No_Buckets];
  ioopm_hash_function *hash_function;
  ioopm_eq_function *eq_fn_key; // Function to compare keys
  ioopm_eq_function *eq_fn_value; // Function to compare keys

};

int int_key_hfunc(elem_t elem){
  int key=elem.i;
  if (key<0){
    key=abs(key);  //om int är negativt, tar absolutbeloppet
  }
  return key%No_Buckets;
}

int string_key_hfunc(elem_t elem){
  char *str=elem.c;
  int length=(int)strlen(str);
  return length%No_Buckets;
}

/*
int float_key_hfunc(elem_t elem){
  float flt=elem.f; 
  if(flt<0)
  {
    flt=fabs(flt);
  }
  flt=round(flt);
  return ((int)flt) % No_Buckets;
}
*/



ioopm_hash_table_t *ioopm_hash_table_create( ioopm_eq_function *eq_fn_value, ioopm_eq_function *eq_fn_key, ioopm_hash_function *hash_function) {

  ioopm_hash_table_t *create_ht = calloc(1, sizeof(ioopm_hash_table_t));
  if(create_ht!=NULL){
    create_ht->hash_function=hash_function;
    create_ht->eq_fn_key=eq_fn_key;
    create_ht->eq_fn_value=eq_fn_value;
  }
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
    entry_destroy(&(ht->buckets[i]));
  }
  free(ht);
}

static entry_t *entry_create( elem_t key, elem_t value, entry_t * next ){
  entry_t * new_entry = malloc(sizeof(entry_t)); // allocate space in memorie for new link
  new_entry -> key = key; // set key to key in new entry
  new_entry -> next = next;  // set next pointer in new link to next
  new_entry -> value = value;
  return new_entry;
}


static entry_t *find_previous_entry_for_key(entry_t *head, elem_t key1, ioopm_eq_function *eq_fn_key) {
  if (head-> next == NULL){
    return head;
  }

  entry_t *current = head->next;
  entry_t *previous = head;

  // gå genom länkarna
  while (current != NULL) {
    // kollar om länkens key matchar med vår key
    if (eq_fn_key!=NULL &&eq_fn_key(current->key, key1)) {
      break;  // returnerar previous
    }

    // gå till nästa länk
    previous = current;
    current = current->next;
    }

  // om inget hittas
  return previous;
}



void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value){
  int int_key;
  //tar fram vilken bucket
  int_key = ht->hash_function(key);

  ioopm_eq_function *eq_fn_key =ht->eq_fn_key;

  entry_t *entry = find_previous_entry_for_key(&ht->buckets[int_key], key, eq_fn_key);
  entry_t *next = entry-> next;
  if(entry){
    /// Check if the next entry should be updated or not
    if (next != NULL && eq_fn_key(next->key, key)){
      next->value = value;
    }
    else{
      entry->next = entry_create(key, value, next);
    }
  }
}



option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key) {

  int bucket= ht->hash_function(key);
  ioopm_eq_function *eq_fn_key =ht->eq_fn_key;

  entry_t *tmp = find_previous_entry_for_key(&ht->buckets[bucket], key, eq_fn_key);

  if (!tmp || tmp->next == NULL){
    return Failure();
  }

  entry_t *to_lookup = tmp->next;

  if(!eq_fn_key(to_lookup-> key, key)){
    return Failure();
  }

  elem_t to_lookup_value=to_lookup->value;
  return Success(to_lookup_value);
}


option_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key)
{
  ioopm_eq_function *eq_fn_key =ht->eq_fn_key;
  /// Calculate the bucket for this entry
  
  int bucket = ht->hash_function(key);

  entry_t *prev = find_previous_entry_for_key(&ht->buckets[bucket], key, eq_fn_key);
    
  if (prev == NULL || prev->next == NULL) {
    return Failure();
  }

  entry_t *to_remove =prev->next;
  elem_t value = to_remove->value;
    
  if (!eq_fn_key(to_remove->key, key))  
  {
    return Failure();
  }

  else
  {
    prev->next = to_remove->next;
    option_t op={.success=true, .value=value};
    free(to_remove);
    return op;
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

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht){
  return ioopm_hash_table_size(ht) == 0;
}


void ioopm_hash_table_clear(ioopm_hash_table_t *ht){
    for ( int i = 0 ; i <  No_Buckets; i++) {
        entry_destroy(&ht->buckets[i]);
        ht->buckets[i].next = NULL;
    }
}

ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht){
  

  ioopm_list_t * list = ioopm_linked_list_create(ht->eq_fn_value);
  elem_t current_key;

  if (ioopm_hash_table_is_empty(ht)) {
    return list;
  }

  for (int i = 0; i < No_Buckets; i ++){
   entry_t *current_bucket = &ht->buckets[i];

   if (current_bucket -> next == NULL){
      continue;
   }

   entry_t *current_entry = current_bucket-> next; 

    while (current_entry != NULL) {
      current_key = current_entry->key;
      ioopm_linked_list_append(list, current_key);
      current_entry = current_entry->next;
  }

  }
  return list;
}



ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *ht) {
  ioopm_list_t *list=ioopm_linked_list_create(ht->eq_fn_value);
  elem_t current_value;

  if(ioopm_hash_table_is_empty(ht)){
    return list;
  }

   for(int i=0; i<No_Buckets; ++i){
        entry_t *current_bucket=&ht->buckets[i];
        if (current_bucket ->next ==NULL){
          continue;
        }

        entry_t *current_entry=current_bucket->next;
        while(current_entry){
          current_value = current_entry->value;
          ioopm_linked_list_append(list, current_value);
          current_entry=current_entry->next;
        }
   }
   return list;
}


static bool key_equiv(elem_t key, elem_t value_ignored, elem_t x, ioopm_eq_function *eq_fn_key){
  return eq_fn_key(key,x);
}

static bool value_equiv(elem_t key_ignored, elem_t value, elem_t x, ioopm_eq_function *eq_fn_value){
  return eq_fn_value(value,x);
}


bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate *pred, elem_t arg, ioopm_eq_function *eq_fn) {
  bool is_empty=ioopm_hash_table_is_empty(ht);
  if (is_empty){
    return false;
  }
  for (int i = 0; i < No_Buckets; ++i) {
    entry_t *current = ht->buckets[i].next;
    while (current) {
      elem_t key = current->key;
      elem_t value = current->value;
        if (pred(key, value, arg, eq_fn)) {  
                return true;  
            }
            current = current->next;
        }
    }
    return false;  
}

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key){
  return ioopm_hash_table_any(ht, key_equiv, key, ht->eq_fn_key);
}

bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value){
 return ioopm_hash_table_any(ht, value_equiv, value, ht->eq_fn_value);
}


//all values/keys satisfy a predicate
bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate *pred, elem_t arg, ioopm_eq_function *eq_fn){
  if (ioopm_hash_table_is_empty(ht)) {
    return false;  // If the hash table is empty, all entries trivially satisfy the predicate
  }

  for (int i = 0; i < No_Buckets; ++i) {    
    entry_t *current = ht->buckets[i].next;
    while (current) {
      elem_t key = current->key;
      elem_t value = current->value;
      if (!pred(key, value, arg, eq_fn)) {  
        return false;  
      }
      current = current->next;
    }
  }
  return true; 
}

bool test_hash_table_all_value(ioopm_hash_table_t *ht, elem_t value){
    return ioopm_hash_table_all(ht, value_equiv, value, ht->eq_fn_value);
}

void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function *apply_fun, elem_t arg){
  for(int i=0; i<No_Buckets; ++i){
    entry_t *current = ht->buckets[i].next;
    while(current)
    {
      elem_t key = current->key;
      elem_t *value = &(current->value);
      apply_fun(key, value, arg);
      current = current->next;    
    }
    }
}

void test_change_value(elem_t key, elem_t *value, elem_t arg){
  *value=arg;
}


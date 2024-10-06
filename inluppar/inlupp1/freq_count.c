#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash_table.h"
#include "linked_list.h"
#include "common.h"
#include "iterator.h"

#define Delimiters "+-#@()[]{}.,:;!? \t\n\r"


static int cmpstringp(const void *p1, const void *p2)
{
return strcmp(*(char *const *)p1, *(char *const *)p2);
}


void sort_keys(char *keys[], size_t no_keys)
{
qsort(keys, no_keys, sizeof(char *), cmpstringp);
}


void process_word(char *word, ioopm_hash_table_t *ht)
{
  int freq;

  //puts("in process word"); //debug

  if (ioopm_hash_table_has_key(ht, (elem_t) {.c = (word)})){
    freq = ioopm_hash_table_lookup(ht, (elem_t) {.c = word}).value.i;
    ioopm_hash_table_insert(ht,(elem_t) {.c = word}, (elem_t) {.i = freq + 1} );
  }

  else {

  freq =
    ioopm_hash_table_has_key(ht, (elem_t) {.c = word})?
    (ioopm_hash_table_lookup(ht, (elem_t) {.c = word})).value.i:
    0;

  //printf("Inserting/updating word: '%s' with frequency: %d\n", word, freq + 1); //debug
  ioopm_hash_table_insert(ht, (elem_t) {.c = strdup(word)}, (elem_t) {.c = freq + 1});

    size_t size = ioopm_hash_table_size(ht);
    //printf("Current hash table size: %zu\n", size); //debug
}
}



void process_file(char *filename, ioopm_hash_table_t *ht)
{
    FILE *f = fopen(filename, "r");

    if (!f) {
        puts("error opening file");
        return;
    }

    while (true) {
        char *buf = NULL;
        size_t len = 0;

        ssize_t read = getline(&buf, &len, f);
        if (read == -1) {
          
            if (feof(f)) {
                free(buf);
                break; 
            } else {
                perror("getline error"); 
                free(buf);
                break; 
            }
        }

        //printf("Read line: %s", buf); // Debug output

        //puts("in loop");
        for (char *word = strtok(buf, Delimiters); word && *word; word = strtok(NULL, Delimiters)) {
            //puts("calling process word"); //debug
            process_word(word, ht);
        }

        free(buf);
    }

    puts("end of file");
    fclose(f);
}

void free_all_duplicates(ioopm_hash_table_t *ht) {
 
    ioopm_list_t *keys_list = ioopm_hash_table_keys(ht); 
    ioopm_list_iterator_t *keys_i = ioopm_list_iterator(keys_list); 

    while (ioopm_iterator_has_next(keys_i)) {
      
        elem_t key = ioopm_iterator_next(keys_i);
    
        free(key.c);
    }

    ioopm_iterator_destroy(keys_i);
    ioopm_linked_list_destroy(keys_list); 
}


int main(int argc, char *argv[])
{
ioopm_hash_table_t *ht = ioopm_hash_table_create(int_compare, char_compare, string_key_hfunc);

if (argc > 1)
{
for (int i = 1; i < argc; ++i)
{
process_file(argv[i], ht);
}

    ioopm_list_t * list = ioopm_hash_table_keys(ht);
    ioopm_list_iterator_t *keys_i = ioopm_list_iterator(list); 
    char **keys = calloc(ioopm_hash_table_size(ht), sizeof(char *));  

    for(int i = 0; ioopm_iterator_has_next(keys_i) == true; i++){
      
      keys[i] = ioopm_iterator_next(keys_i).c; 
    }

    size_t size = ioopm_hash_table_size(ht);
    sort_keys(keys, size);

    for (int i = 0; i < size; ++i)
    {

      option_t freq = (ioopm_hash_table_lookup(ht, (elem_t) {.c = keys[i]}));
      if(freq.success == true){
        printf("%s: %d\n", keys[i], freq.value.i);
      }else{
        printf("something went wrong.."); 
        break;
      }
    }


    ioopm_iterator_destroy(keys_i);
    ioopm_linked_list_destroy(list);
    free(keys);

  }
  else
  {
    puts("Usage: freq-count file1 ... filen :(");
  }

  free_all_duplicates(ht);
  ioopm_hash_table_destroy(ht);
}

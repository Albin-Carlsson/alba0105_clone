#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash_table.h"
#include "linked_list.h"
#include "common.h"
#include "iterator.h"

#include <CUnit/Basic.h>

// declarations of the functions to be tested
void process_word(char *word, ioopm_hash_table_t *ht);
void process_file(char *filename, ioopm_hash_table_t *ht);
void free_all_duplicates(ioopm_hash_table_t *ht);

int init_suite(void)
{
  // Change this function if you want to do something *before* you
  // run a test suite
  return 0;
}

int clean_suite(void)
{
  // Change this function if you want to do something *after* you
  // run a test suite
  return 0;
}

// Helper function to create a hash table for testing
static ioopm_hash_table_t *create_test_hash_table()
{
  return ioopm_hash_table_create(int_compare, char_compare, string_key_hfunc);
}

// Test case for process_word: inserting a new word
void test_process_word_insert_new()
{
  ioopm_hash_table_t *ht = create_test_hash_table();
  char *word = "test";

  process_word(word, ht);

  option_t result = ioopm_hash_table_lookup(ht, char_elem(word));
  CU_ASSERT_TRUE(result.success);
  CU_ASSERT_EQUAL(result.value.i, 1);

  free_all_duplicates(ht);
  ioopm_hash_table_destroy(ht);
}

// inserting the same word twice should increment its frequency to 2
void test_process_word_insert_duplicate()
{
  ioopm_hash_table_t *ht = create_test_hash_table();
  char *word = "duplicate";

  process_word(word, ht);
  process_word(word, ht);

  option_t result = ioopm_hash_table_lookup(ht, (elem_t){.c = word});
  CU_ASSERT_TRUE(result.success);
  CU_ASSERT_EQUAL(result.value.i, 2);

  free_all_duplicates(ht);
  ioopm_hash_table_destroy(ht);
}

void test_process_word_multiple_unique_words()
{
  ioopm_hash_table_t *ht = create_test_hash_table();

  // Array of unique words to insert
  char *words[] = {"apple", "banana", "cherry", "date", "elderberry"};
  size_t num_words = sizeof(words) / sizeof(words[0]);

  // Insert each word into the hash table
  for (size_t i = 0; i < num_words; i++)
  {
    process_word(words[i], ht);
  }

  // Verify that each word exists with a frequency of 1
  for (size_t i = 0; i < num_words; i++)
  {
    option_t result = ioopm_hash_table_lookup(ht, (elem_t){.c = words[i]});
    CU_ASSERT_TRUE(result.success);
    CU_ASSERT_EQUAL(result.value.i, 1);

    // Optional: Print for debugging purposes
    // printf("Word: %s, Frequency: %d\n", words[i], result.value.i);
  }

  // Verify that the hash table size matches the number of unique words
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), num_words);

  free_all_duplicates(ht);
  ioopm_hash_table_destroy(ht);
}

// Test case for processing an empty file
void test_process_file_empty()
{
  // Setup
  ioopm_hash_table_t *ht = create_test_hash_table();
  char *test_filename = "empty_file.txt";

  // Create an empty file
  FILE *file = fopen(test_filename, "w");
  assert(file);
  fclose(file);

  // Run the function
  process_file(test_filename, ht);

  // Check that the hash table is still empty
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);

  // Cleanup
  free_all_duplicates(ht);
  ioopm_hash_table_destroy(ht);
  remove(test_filename);
}

// Test case for processing a valid file with multiple words
void test_process_file_multiple_words()
{
  // Setup
  ioopm_hash_table_t *ht = create_test_hash_table();
  char *test_filename = "test_file.txt";

  // Create test file with known content
  FILE *file = fopen(test_filename, "w");
  assert(file);
  fprintf(file, "apple banana apple orange\nbanana apple\n");
  fclose(file);

  // Run the function
  process_file(test_filename, ht);

  // Check that the word counts are correct
  CU_ASSERT_EQUAL(ioopm_hash_table_lookup(ht, (elem_t){.c = "apple"}).value.i, 3);
  CU_ASSERT_EQUAL(ioopm_hash_table_lookup(ht, (elem_t){.c = "banana"}).value.i, 2);
  CU_ASSERT_EQUAL(ioopm_hash_table_lookup(ht, (elem_t){.c = "orange"}).value.i, 1);

  // Cleanup
  free_all_duplicates(ht);
  ioopm_hash_table_destroy(ht);
  remove(test_filename); // Delete the test file after use
}

// Test case for file that doesn't exist
void test_process_file_nonexistent()
{
  // Setup
  ioopm_hash_table_t *ht = create_test_hash_table();
  char *test_filename = "nonexistent_file.txt";

  // Run the function (the file doesn't exist)
  process_file(test_filename, ht);

  // Check that nothing was inserted into the hash table
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);

  // Cleanup
  ioopm_hash_table_destroy(ht);
}

// Test case for processing a file with repeated words
void test_process_file_repeated_words()
{
  // Setup
  ioopm_hash_table_t *ht = create_test_hash_table();
  char *test_filename = "repeated_words.txt";

  // Create test file with repeated content
  FILE *file = fopen(test_filename, "w");
  assert(file);
  fprintf(file, "hello hello hello\n");
  fclose(file);

  // Run the function
  process_file(test_filename, ht);

  // Check that the word counts are correct
  CU_ASSERT_EQUAL(ioopm_hash_table_lookup(ht, (elem_t){.c = "hello"}).value.i, 3);

  // Cleanup
  free_all_duplicates(ht);
  ioopm_hash_table_destroy(ht);
  remove(test_filename);
}

int main()
{
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite my_test_suite = CU_add_suite("My awesome test suite", init_suite, clean_suite);
  if (my_test_suite == NULL)
  {
    // If the test suite could not be added, tear down CUnit and exit
    CU_cleanup_registry();
    return CU_get_error();
  }

  // This is where we add the test functions to our test suite.
  // For each call to CU_add_test we specify the test suite, the
  // name or description of the test, and the function that runs
  // the test in question. If you want to add another test, just
  // copy a line below and change the information
  if (

      (CU_add_test(my_test_suite, "test process word insert new", test_process_word_insert_new) == NULL) ||
      (CU_add_test(my_test_suite, "test process word insert duplicate", test_process_word_insert_duplicate) == NULL) ||
      (CU_add_test(my_test_suite, "test process word multiple unique", test_process_word_multiple_unique_words) == NULL) ||
      (CU_add_test(my_test_suite, "test process file empty", test_process_file_empty) == NULL) ||
      (CU_add_test(my_test_suite, "test process file multiple words", test_process_file_multiple_words) == NULL) ||
      (CU_add_test(my_test_suite, "test process file nonexistent file", test_process_file_nonexistent) == NULL) ||
      (CU_add_test(my_test_suite, "test process file repeated words", test_process_file_repeated_words) == NULL) ||


      0

  )
  {
    // If adding any of the tests fails, we tear down CUnit and exit
    CU_cleanup_registry();
    return CU_get_error();
  }

  // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
  // Use CU_BRM_NORMAL to only print errors and a summary
  CU_basic_set_mode(CU_BRM_VERBOSE);

  // This is where the tests are actually run!
  CU_basic_run_tests();

  // Tear down CUnit before exiting
  CU_cleanup_registry();
  return CU_get_error();
}

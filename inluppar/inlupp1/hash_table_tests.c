#include "hash_table.h"
#include <CUnit/Basic.h>

//Helper functions declarations
void test_change_value(elem_t key, elem_t* value, elem_t arg);
bool test_hash_table_all_value(ioopm_hash_table_t* ht, elem_t value);

int init_suite(void) {
  // Change this function if you want to do something *before* you
  // run a test suite
  return 0;
}

int clean_suite(void) {
  // Change this function if you want to do something *after* you
  // run a test suite
  return 0;
}

void test_create_destroy() {
  ioopm_hash_table_t* ht = ioopm_hash_table_create(char_compare, int_compare, int_key_hfunc);
  CU_ASSERT_PTR_NOT_NULL(ht);
  ioopm_hash_table_destroy(ht);
}


void test_insert_hash_table() {
  ioopm_hash_table_t* ht = ioopm_hash_table_create(char_compare, int_compare, int_key_hfunc);
  CU_ASSERT_PTR_NOT_NULL(ht);
  ioopm_hash_table_insert(ht, int_elem(0), char_elem("zero"));

  option_t result = ioopm_hash_table_lookup(ht, int_elem(0));
  elem_t elem = result.value;
  char* value = elem.c;

  CU_ASSERT_TRUE(result.success);
  CU_ASSERT_STRING_EQUAL(value, "zero");

  ioopm_hash_table_insert(ht, int_elem(-1), char_elem("-1"));
  result = ioopm_hash_table_lookup(ht, int_elem(-1));
  CU_ASSERT_TRUE(result.success);
  ioopm_hash_table_destroy(ht);
}



void test_insert_once() {
  // Create the hash table
  ioopm_hash_table_t* ht = ioopm_hash_table_create(char_compare, int_compare, int_key_hfunc);
  CU_ASSERT_PTR_NOT_NULL(ht); // Ensure the hash table was created successfully

  // Insert a key-value pair
  ioopm_hash_table_insert(ht, int_elem(1), char_elem("one"));

  // Lookup the inserted key
  option_t result = ioopm_hash_table_lookup(ht, int_elem(1));
  CU_ASSERT_TRUE(result.success); // Assert that the lookup was successful

  // Check if the retrieved value is correct
  elem_t v = result.value;
  char* v1 = v.c; // Get the string from the returned elem_t
  CU_ASSERT_STRING_EQUAL(v1, "one"); // Assert that the value matches "one"

  // Destroy the hash table
  ioopm_hash_table_destroy(ht);
}




void test_lookup_empty() {
  ioopm_hash_table_t* ht = ioopm_hash_table_create(char_compare, int_compare, int_key_hfunc);

  option_t result = ioopm_hash_table_lookup(ht, int_elem(1));
  CU_ASSERT_FALSE(result.success);

  //CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, -1));
  ioopm_hash_table_destroy(ht);
}


void test_remove() {

  ioopm_hash_table_t* ht = ioopm_hash_table_create(char_compare, int_compare, int_key_hfunc);;
  ioopm_hash_table_insert(ht, int_elem(1), char_elem("one"));

  option_t result = ioopm_hash_table_lookup(ht, int_elem(1));
  CU_ASSERT_TRUE(result.success);
  elem_t val = result.value;
  char* val1 = val.c;
  CU_ASSERT_PTR_NOT_NULL(val1);

  result = ioopm_hash_table_remove(ht, int_elem(1));
  result = ioopm_hash_table_lookup(ht, int_elem(1));

  CU_ASSERT_FALSE(result.success);
  ioopm_hash_table_destroy(ht);
}



void test_remove2() {
  ioopm_hash_table_t* ht = ioopm_hash_table_create(char_compare, int_compare, int_key_hfunc);
  int key1 = 5;
  char* value1 = "hej";
  int key2 = 22;
  char* value2 = "hejsan";
  int key3 = 39;
  char* value3 = "halloj";
  option_t op;

  // Insert 3 entries into ht
  ioopm_hash_table_insert(ht, int_elem(key1), char_elem(value1));
  ioopm_hash_table_insert(ht, int_elem(key2), char_elem(value2));
  ioopm_hash_table_insert(ht, int_elem(key3), char_elem(value3));

  // Remove key2 value from ht, check if remove function returns correct values 
  op = ioopm_hash_table_remove(ht, int_elem(key2));
  elem_t val = op.value;
  char* val1 = val.c;
  printf("Removed value: %s\n", val1); // Debug output
  CU_ASSERT_TRUE(op.success);

  op = ioopm_hash_table_lookup(ht, int_elem(key2));
  CU_ASSERT_FALSE(op.success);

  //Remove third entry 
  op = ioopm_hash_table_remove(ht, int_elem(key1));
  CU_ASSERT_TRUE(op.success);

  //Trying to remove key3 twice from ht
  op = ioopm_hash_table_remove(ht, int_elem(key3));
  op = ioopm_hash_table_remove(ht, int_elem(key3));
  CU_ASSERT_FALSE(op.success);

  ioopm_hash_table_destroy(ht);
}



void test_negativ_number() {
  ioopm_hash_table_t* ht = ioopm_hash_table_create(char_compare, int_compare, int_key_hfunc);
  ioopm_hash_table_insert(ht, int_elem(-1), char_elem("-1"));

  option_t op = ioopm_hash_table_lookup(ht, int_elem(-1));
  elem_t v = op.value;
  char* v1 = v.c;
  CU_ASSERT_STRING_EQUAL(v1, "-1");
  ioopm_hash_table_destroy(ht);
}


void test_count_entries() {
  ioopm_hash_table_t* ht = ioopm_hash_table_create(char_compare, int_compare, int_key_hfunc);
  int size = ioopm_hash_table_size(ht);
  //empty hash_table
  CU_ASSERT_FALSE(size);

  ioopm_hash_table_insert(ht, int_elem(1), char_elem("1"));
  size = ioopm_hash_table_size(ht);
  //hash_table with one entry
  CU_ASSERT_EQUAL(size, 1);

  ioopm_hash_table_insert(ht, int_elem(18), char_elem("1"));
  ioopm_hash_table_insert(ht, int_elem(3), char_elem("3"));
  size = ioopm_hash_table_size(ht);
  //hash table with multiple entries
  CU_ASSERT_EQUAL(size, 3);

  ioopm_hash_table_destroy(ht);

}

void test_is_empty_hash_table() {
  ioopm_hash_table_t* ht = ioopm_hash_table_create(char_compare, int_compare, int_key_hfunc);
  bool is_empty = ioopm_hash_table_is_empty(ht);
  CU_ASSERT_TRUE(is_empty);

  ioopm_hash_table_insert(ht, int_elem(1), char_elem("1"));
  is_empty = ioopm_hash_table_is_empty(ht);
  CU_ASSERT_FALSE(is_empty);

  ioopm_hash_table_destroy(ht);
}

void test_clear_hash_table() {
  ioopm_hash_table_t* ht = ioopm_hash_table_create(char_compare, int_compare, int_key_hfunc);
  ioopm_hash_table_clear(ht);
  bool is_empty = ioopm_hash_table_is_empty(ht);
  CU_ASSERT_TRUE(is_empty);

  ioopm_hash_table_insert(ht, int_elem(1), char_elem("1"));
  ioopm_hash_table_clear(ht);
  is_empty = ioopm_hash_table_is_empty(ht);
  CU_ASSERT_TRUE(is_empty);

  ioopm_hash_table_destroy(ht);
}



void test_get_keys() {

  ioopm_hash_table_t* ht = ioopm_hash_table_create(char_compare, int_compare, int_key_hfunc);
  int keys[5] = { 3, 10, 42, 0, 99 };
  bool found[5] = { false };

  ioopm_hash_table_insert(ht, int_elem(3), char_elem("three"));
  ioopm_hash_table_insert(ht, int_elem(10), char_elem("ten"));
  ioopm_hash_table_insert(ht, int_elem(42), char_elem("fortytwo"));
  ioopm_hash_table_insert(ht, int_elem(0), char_elem("zero"));
  ioopm_hash_table_insert(ht, int_elem(99), char_elem("ninetynine"));

  ioopm_list_t* all_keys = ioopm_hash_table_keys(ht);

  for (int i = 0; i < 5; i++) {
    int key_found = 0;
    for (int j = 0; j < 5; j++) {
      option_list_t get = ioopm_linked_list_get(all_keys, i);
      elem_t val = get.ptr->value;
      int val1 = val.i;
      if (val1 == keys[j]) {
        found[j] = 1;
        key_found = 1;
        break;
      }
    }
    if (!key_found) {
      CU_FAIL("Found a key that was never inserted!");
    }
  }

  printf("Keys found in the hash table:\n");
  for (int i = 0; i < 5; i++) {
    option_list_t get = ioopm_linked_list_get(all_keys, i);
    elem_t val = get.ptr->value;
    int val1 = val.i;
    printf("all_keys[%d] = %d\n", i, val1);
  }
  ioopm_hash_table_destroy(ht);
  ioopm_linked_list_destroy(all_keys);
}



//test för ioopm_hash_table_get_values
void test_get_values() {
  int keys[5] = { 3, 10, 42, 0, 99 };
  char* values[5] = { "three", "ten", "fortytwo", "zero", "ninetynine" };
  ioopm_hash_table_t* ht = ioopm_hash_table_create(char_compare, int_compare, int_key_hfunc);


  for (int i = 0; i < 5; ++i) {
    ioopm_hash_table_insert(ht, int_elem(keys[i]), char_elem(values[i]));
  }

  ioopm_list_t* all_keys = ioopm_hash_table_keys(ht);
  ioopm_list_t* all_values = ioopm_hash_table_values(ht);

  for (int i = 0; i < 5; ++i) {
    option_list_t get_keys1 = ioopm_linked_list_get(all_keys, i);
    option_list_t get_value1 = ioopm_linked_list_get(all_values, i);

    elem_t keys1 = get_keys1.ptr->value;
    elem_t values1 = get_value1.ptr->value;

    int keys2 = keys1.i;
    char* value2 = values1.c;

    bool key_found = false;

    //nu går vi genom och ser om keys och values i den ny arrayen matchar med de förra
    for (int j = 0; j < 5; ++j) {
      if (keys[j] == keys2) {
        //om de inte matchar
        if (strcmp(value2, values[j]) != 0) {
          CU_FAIL("Found a value that doesn't match the original!");
        }

        //om de matchar
        key_found = true;
        break; //går till nästa key,value
      }
    }

    if (!key_found) {
      CU_FAIL("Found a key that was never inserted!");
    }
  }

  printf("Keys and values found in the hash table:\n");
  for (int i = 0; i < 5; ++i) {
    option_list_t get_keys = ioopm_linked_list_get(all_keys, i);
    option_list_t get_values = ioopm_linked_list_get(all_values, i);

    int key = get_keys.ptr->value.i;
    char* value = get_values.ptr->value.c;
    printf("Key: %d, Value: %s\n", key, value);
  }

  ioopm_linked_list_destroy(all_values);
  ioopm_hash_table_destroy(ht);
  ioopm_linked_list_destroy(all_keys);

}



void test_has_key() {
  ioopm_hash_table_t* ht = ioopm_hash_table_create(char_compare, int_compare, int_key_hfunc);

  bool found;

  //looking for a key in an empty hash_table
  found = ioopm_hash_table_has_key(ht, int_elem(1));
  CU_ASSERT_FALSE(found);

  //looking for an existing key
  ioopm_hash_table_insert(ht, int_elem(1), char_elem("one"));
  found = ioopm_hash_table_has_key(ht, int_elem(1));
  CU_ASSERT_TRUE(found);

  //looking for a non existing key
  found = ioopm_hash_table_has_key(ht, int_elem(2));
  CU_ASSERT_FALSE(found);

  ioopm_hash_table_destroy(ht);
}


void test_has_value() {
  ioopm_hash_table_t* ht = ioopm_hash_table_create(char_compare, int_compare, int_key_hfunc);

  bool found;

  //looking for a value in an empty hash_table
  found = ioopm_hash_table_has_value(ht, char_elem("one"));
  CU_ASSERT_FALSE(found);

  //looking for an existing value
  char* str1 = "one";
  ioopm_hash_table_insert(ht, int_elem(1), char_elem(str1));
  found = ioopm_hash_table_has_value(ht, char_elem(str1));
  CU_ASSERT_TRUE(found);

  //looking for a strdup of a value
  char* str = strdup(str1);
  found = ioopm_hash_table_has_value(ht, char_elem(str));
  CU_ASSERT_TRUE(found);

  //looking for a non existing key
  found = ioopm_hash_table_has_value(ht, char_elem("two"));
  CU_ASSERT_FALSE(found);

  free(str);
  ioopm_hash_table_destroy(ht);
}

//test for ioopm_hash_table_all
void test_hash_table_all()
{
  bool result;
  ioopm_hash_table_t* ht = ioopm_hash_table_create(char_compare, int_compare, int_key_hfunc);

  char* str = "one";

  //testar med en tom ht
  result = test_hash_table_all_value(ht, char_elem(str));
  CU_ASSERT_FALSE(result);

  //testar med en ht där 'alla' sträng matchar all funktionen
  ioopm_hash_table_insert(ht, int_elem(1), char_elem(str));
  result = test_hash_table_all_value(ht, char_elem(str));
  CU_ASSERT_TRUE(result);

  //testar med en ht där all funktionen inte stämmer
  char* str2 = "two";
  ioopm_hash_table_insert(ht, int_elem(2), char_elem(str2));
  result = test_hash_table_all_value(ht, char_elem(str));
  CU_ASSERT_FALSE(result);


  ioopm_hash_table_destroy(ht);

}

//test för ioopm_hash_table_apply_to_all mha test_change_values
void test_hash_table_apply_all() {
  ioopm_hash_table_t* ht = ioopm_hash_table_create(char_compare, int_compare, int_key_hfunc);

  char* str = "one";
  char* str2 = "two";
  //insertar samma sträng i 3 olika länkar
  ioopm_hash_table_insert(ht, int_elem(1), char_elem(str));
  ioopm_hash_table_insert(ht, int_elem(2), char_elem(str));
  ioopm_hash_table_insert(ht, int_elem(3), char_elem(str));

  //anropar apply to all för att ändra alla values i ht
  ioopm_hash_table_apply_to_all(ht, test_change_value, char_elem(str2));
  bool result = ioopm_hash_table_has_value(ht, char_elem(str2));
  CU_ASSERT_TRUE(result);


  //tar alla values ut mha ioopm_hash_table_values
  ioopm_list_t* all_values = ioopm_hash_table_values(ht);

  //loopar genom all_values arrayen för att säkerställa att alla values==den ny strängen
  for (int i = 0; i < 3; ++i) {
    option_list_t value_op = ioopm_linked_list_get(all_values, i);
    if (value_op.success) {
      elem_t value = value_op.ptr->value;
      char* str_value = value.c;
      if (strcmp(str_value, str2) != 0) {
        CU_FAIL("Value does not match expected string!")
      }
    }
    else {
      CU_FAIL("failed to retrieve value from list");
    }

  }
  // Clean up
  ioopm_linked_list_destroy(all_values);
  ioopm_hash_table_destroy(ht);

}

int main() {
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite my_test_suite = CU_add_suite("My awesome test suite", init_suite, clean_suite);
  if (my_test_suite == NULL) {
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


    (CU_add_test(my_test_suite, "test_create_destroy", test_create_destroy) == NULL) ||
    (CU_add_test(my_test_suite, "test_insert_once", test_insert_once) == NULL) ||
    (CU_add_test(my_test_suite, "test insert hash table", test_insert_hash_table) == NULL) ||
    (CU_add_test(my_test_suite, "test lookup empty", test_lookup_empty) == NULL) ||
    (CU_add_test(my_test_suite, "test remove", test_remove) == NULL) ||
    (CU_add_test(my_test_suite, "test remove2", test_remove2) == NULL) ||
    (CU_add_test(my_test_suite, "hash table lookup negativ", test_negativ_number) == NULL) ||
    (CU_add_test(my_test_suite, "test count entries", test_count_entries) == NULL) ||
    (CU_add_test(my_test_suite, "test is empty hashtable", test_is_empty_hash_table) == NULL) ||
    (CU_add_test(my_test_suite, "test clear hash table", test_clear_hash_table) == NULL) ||
    (CU_add_test(my_test_suite, "test get keys", test_get_keys) == NULL) ||
    (CU_add_test(my_test_suite, "test get values", test_get_values) == NULL) ||
    (CU_add_test(my_test_suite, "test has key", test_has_key) == NULL) ||
    (CU_add_test(my_test_suite, "test has value", test_has_value) == NULL) ||
    (CU_add_test(my_test_suite, "test hash table all", test_hash_table_all) == NULL) ||
    (CU_add_test(my_test_suite, "test hash table apply all", test_hash_table_apply_all) == NULL) ||
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

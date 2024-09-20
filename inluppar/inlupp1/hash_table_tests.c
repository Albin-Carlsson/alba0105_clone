#include "hash_table.h"
#include <CUnit/Basic.h>


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
   ioopm_hash_table_t *ht = ioopm_hash_table_create();
   CU_ASSERT_PTR_NOT_NULL(ht);
   ioopm_hash_table_destroy(ht);
}


void test_insert_hash_table() {
    ioopm_hash_table_t *ht = ioopm_hash_table_create();
    CU_ASSERT_PTR_NOT_NULL(ht); 
    ioopm_hash_table_insert(ht, 0, "zero");
    
    option_t result = ioopm_hash_table_lookup(ht, 0);

    CU_ASSERT_TRUE(result.success);
    CU_ASSERT_STRING_EQUAL(result.value, "zero"); 

    ioopm_hash_table_destroy(ht);

}


void test_insert_once() {

  ioopm_hash_table_t * ht = ioopm_hash_table_create();
  
  CU_ASSERT_PTR_NOT_NULL(ht);
  
  int key = 1;

  option_t result = ioopm_hash_table_lookup(ht, key);

  CU_ASSERT_FALSE(result.success);

  ioopm_hash_table_insert(ht, key, "one");

  option_t value = ioopm_hash_table_lookup(ht, 1);

  CU_ASSERT_TRUE(value.success);

  char * v = value.value;

  CU_ASSERT_STRING_EQUAL(v, "one"); 

  ioopm_hash_table_destroy(ht);


}




void test_lookup_empty()
{
   ioopm_hash_table_t *ht = ioopm_hash_table_create();
   for (int i = 0; i < 18; ++i) /// 18 is a bit magical
     {

      option_t result = ioopm_hash_table_lookup(ht, i);
       CU_ASSERT_PTR_NULL(result.success);
     }

     option_t result1 = ioopm_hash_table_lookup(ht, -1);

   CU_ASSERT_PTR_NULL(result1.success);
     //CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, -1));
   ioopm_hash_table_destroy(ht);
}


void test_remove(){

  ioopm_hash_table_t * ht = ioopm_hash_table_create();
  ioopm_hash_table_insert(ht, 1, "one");

  option_t result = ioopm_hash_table_lookup(ht, 1);

  CU_ASSERT_TRUE(result.success);

  CU_ASSERT_PTR_NOT_NULL(result.value);


  option_t result1 = ioopm_hash_table_remove(ht, 1);

  option_t result2 = ioopm_hash_table_lookup(ht, 1);

  CU_ASSERT_FALSE(result2.success);

  ioopm_hash_table_destroy(ht);

}

void test_remove2(){
    ioopm_hash_table_t *ht = ioopm_hash_table_create();
    int key1 = 5; 
    char *value1 = "hej"; 
    int key2 = 22; 
    char *value2 = "hejsan"; 
    int key3 = 39;
    char *value3 = "halloj"; 
    option_t op; 

    option_t op1;

    // Insert 3 entries into ht
    ioopm_hash_table_insert(ht, key1, value1);
    ioopm_hash_table_insert(ht, key2, value2); 
    ioopm_hash_table_insert(ht, key3, value3); 

    // Remove key2 value from ht, check if remove function returns correct values 
    op = ioopm_hash_table_remove(ht, key2); 
    printf("Removed value: %s\n", op.value); // Debug output

     CU_ASSERT_TRUE(op.success); 

    op1 = ioopm_hash_table_lookup(ht, key2);

    CU_ASSERT_FALSE(op1.success); 

    //Remove third entry 
    op = ioopm_hash_table_remove(ht, key1); 
    CU_ASSERT_TRUE(op.success);

    //Trying to remove key3 twice from ht
    op = ioopm_hash_table_remove(ht, key3);

    op = ioopm_hash_table_remove(ht, key3); 
    CU_ASSERT_FALSE(op.success); 
     
    ioopm_hash_table_destroy(ht);
}

void test_negativ_number(){

  ioopm_hash_table_t* ht = ioopm_hash_table_create();

  ioopm_hash_table_insert(ht, -1, "-1");

  option_t op = ioopm_hash_table_lookup(ht, -1);

  char * v = op.value;


 CU_ASSERT_STRING_EQUAL(v, "-1"); 

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

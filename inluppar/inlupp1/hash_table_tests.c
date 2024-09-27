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


  result = ioopm_hash_table_remove(ht, 1);

  result = ioopm_hash_table_lookup(ht, 1);

  CU_ASSERT_FALSE(result.success);

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


void test_count_entries(){
  ioopm_hash_table_t* ht=ioopm_hash_table_create();
  int size= ioopm_hash_table_size(ht);
  //empty hash_table
  CU_ASSERT_FALSE(size);

  ioopm_hash_table_insert(ht, 1, "1");
  size=ioopm_hash_table_size(ht);
  //hash_table with one entry
  CU_ASSERT_EQUAL(size, 1);

  ioopm_hash_table_insert(ht, 18, "1");
  ioopm_hash_table_insert(ht, 3, "3");
  size=ioopm_hash_table_size(ht);
  //hash table with multiple entries
  CU_ASSERT_EQUAL(size,3);

  ioopm_hash_table_destroy(ht);

}

void test_is_empty_hash_table(){
  ioopm_hash_table_t *ht=ioopm_hash_table_create();
  bool is_empty=ioopm_hash_table_is_empty(ht);
  CU_ASSERT_TRUE(is_empty);

  ioopm_hash_table_insert(ht, 1, "1");
  is_empty=ioopm_hash_table_is_empty(ht);
  CU_ASSERT_FALSE(is_empty);

  ioopm_hash_table_destroy(ht);
}

void test_clear_hash_table(){
  ioopm_hash_table_t*ht=ioopm_hash_table_create();
  ioopm_hash_table_clear(ht);
  bool is_empty=ioopm_hash_table_is_empty(ht);
  CU_ASSERT_TRUE(is_empty);

  ioopm_hash_table_insert(ht, 1, "1");
  ioopm_hash_table_clear(ht);
  is_empty=ioopm_hash_table_is_empty(ht);
  CU_ASSERT_TRUE(is_empty);

  ioopm_hash_table_destroy(ht);
}



void test_get_keys(){

    ioopm_hash_table_t *ht = ioopm_hash_table_create();

    int keys[5] = {3, 10, 42, 0, 99}; 

    bool found[5] = {false};

    ioopm_hash_table_insert(ht, 3, "three");
    ioopm_hash_table_insert(ht, 10, "ten");
    ioopm_hash_table_insert(ht,42, "fortytwo");
    ioopm_hash_table_insert(ht, 0, "zero");
    ioopm_hash_table_insert(ht, 99, "ninetynine");

ioopm_list_t *all_keys = ioopm_hash_table_keys(ht);

for (int i = 0; i < 5; i++) {
    int key_found = 0;
    for (int j = 0; j < 5; j++) {
      option_list_t get = ioopm_linked_list_get(all_keys, i);
      int val = get.ptr->value;
        if (val == keys[j]) {
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
      int val = get.ptr->value;

        printf("all_keys[%d] = %d\n", i, val );
    }


ioopm_hash_table_destroy(ht);  
ioopm_linked_list_destroy(all_keys); 

}



//test för ioopm_hash_table_get_values
void test_get_values(){
  int keys[5] = {3, 10, 42, 0, 99}; 
  char *values[5] = {"three", "ten", "fortytwo", "zero", "ninetynine"};
  ioopm_hash_table_t *ht=ioopm_hash_table_create();
  
  for(int i=0; i<5; ++i){
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }

  ioopm_list_t *all_keys = ioopm_hash_table_keys(ht);
  char **all_values=ioopm_hash_table_values(ht);

  for(int i=0; i<5; ++i){
      option_list_t get = ioopm_linked_list_get(all_keys, i);
      int val = get.ptr->value;
    int k=val;
    char *v=all_values[i];
    bool key_found=false;

    //nu går vi genom och ser om keys och values i den ny arrayen matchar med de förra
    for (int j=0; j<5; ++j){
      if(keys[j]==k){
        //om de inte matchar
        if (strcmp(v, values[j]) != 0){
          CU_FAIL("Found a value that doesn't match the original!");
        }

        //om de matchar
        key_found=true;
        break; //går till nästa key,value
      }
    }

    if (!key_found){
      CU_FAIL("Found a key that was never inserted!");
    }
  }

  printf("Keys and values found in the hash table:\n");
for (int i = 0; i < 5; ++i) {
        option_list_t get = ioopm_linked_list_get(all_keys, i);
      int val = get.ptr->value;
    printf("Key: %d, Value: %s\n", val, all_values[i]);
}

  free(all_values);
  ioopm_hash_table_destroy(ht);
  ioopm_linked_list_destroy(all_keys);

}


void test_has_key(){
  ioopm_hash_table_t *ht=ioopm_hash_table_create();
  bool found;

  //looking for a key in an empty hash_table
  found=ioopm_hash_table_has_key(ht,1);
  CU_ASSERT_FALSE(found);

  //looking for an existing key
  ioopm_hash_table_insert(ht, 1, "one");
  found=ioopm_hash_table_has_key(ht,1);
  CU_ASSERT_TRUE(found);

  //looking for a non existing key
  found=ioopm_hash_table_has_key(ht,2);
  CU_ASSERT_FALSE(found);

  ioopm_hash_table_destroy(ht);
}


void test_has_value(){
  ioopm_hash_table_t *ht=ioopm_hash_table_create();
  bool found;

  //looking for a value in an empty hash_table
  found=ioopm_hash_table_has_value(ht,"one");
  CU_ASSERT_FALSE(found);

  //looking for an existing value
  char *str1="one";
  ioopm_hash_table_insert(ht, 1, str1);
  found=ioopm_hash_table_has_value(ht,str1);
  CU_ASSERT_TRUE(found);

  //looking for a strdup of a value
  char *str=strdup(str1);
  found=ioopm_hash_table_has_value(ht,str);
  CU_ASSERT_TRUE(found);

  //looking for a non existing key
  found=ioopm_hash_table_has_value(ht,"two");
  CU_ASSERT_FALSE(found);

  free(str);
  ioopm_hash_table_destroy(ht);
}

//test for ioopm_hash_table_all
void test_hash_table_all()
{
  bool result;
  ioopm_hash_table_t *ht=ioopm_hash_table_create();
  char *str="one";

  //testar med en tom ht
  result= test_hash_table_all_value(ht,str );
  CU_ASSERT_FALSE(result);

  //testar med en ht där 'alla' sträng matchar all funktionen
  ioopm_hash_table_insert(ht, 1, str);
  result= test_hash_table_all_value(ht,str);
  CU_ASSERT_TRUE(result);

  //testar med en ht där all funktionen inte stämmer
  char *str2="two";
  ioopm_hash_table_insert(ht,2,str2);
  result= test_hash_table_all_value(ht,str);
  CU_ASSERT_FALSE(result);

  
  ioopm_hash_table_destroy(ht);

}

//test för ioopm_hash_table_apply_to_all mha test_change_values
void test_hash_table_apply_all(){
  ioopm_hash_table_t *ht=ioopm_hash_table_create();
  char *str="one";
  char *str2="twoo";
  //insertar samma sträng i 3 olika länkar
  ioopm_hash_table_insert(ht, 1, str);
  ioopm_hash_table_insert(ht, 2, str);
  ioopm_hash_table_insert(ht, 3, str);

  //anropar apply to all för att ändra alla values i ht
  ioopm_hash_table_apply_to_all(ht, test_change_value, str2);

  //tar alla values ut mha ioopm_hash_table_values
  char **all_values=ioopm_hash_table_values(ht);

  //loopar genom all_values arrayen för att säkerställa att alla values==den ny strängen
  for (int i = 0; i < 3; ++i) {
        if (strcmp(all_values[i], str2) != 0) {
            CU_FAIL("Value does not match expected string!");
        }
  }
  bool result=ioopm_hash_table_has_value(ht, str2);
  CU_ASSERT_TRUE(result);

    // Clean up
    free(all_values);
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

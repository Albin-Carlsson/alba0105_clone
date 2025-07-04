#include "iterator.h"
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


void test_iter_has_next() {

  ioopm_list_t* list = ioopm_linked_list_create(int_compare);

  ioopm_linked_list_append(list, int_elem(1));

  ioopm_list_iterator_t* iter = ioopm_list_iterator(list);

  bool result = ioopm_iterator_has_next(iter);

  CU_ASSERT_TRUE(result);

  ioopm_iterator_destroy(iter);
  ioopm_linked_list_destroy(list);

}

void test_iter_next() {

  ioopm_list_t* list = ioopm_linked_list_create(int_compare);
  ioopm_list_iterator_t* iter = ioopm_list_iterator(list);

  ioopm_linked_list_append(list, int_elem(1));
  ioopm_linked_list_append(list, int_elem(2));

  elem_t elem = ioopm_iterator_next(iter);

  CU_ASSERT_EQUAL(1, elem.i);

  elem = ioopm_iterator_next(iter);

  CU_ASSERT_EQUAL(2, elem.i);

  ioopm_iterator_destroy(iter);

  ioopm_linked_list_destroy(list);
}


void test_next_empty() {
  ioopm_list_t* list = ioopm_linked_list_create(int_compare);
  ioopm_list_iterator_t* iter = ioopm_list_iterator(list);

  elem_t result = ioopm_iterator_next(iter);

  int result1 = result.i;

  CU_ASSERT_EQUAL(0, result1);

  ioopm_iterator_destroy(iter);
  ioopm_linked_list_destroy(list);
}



void test_has_next_empty() {

  ioopm_list_t* list = ioopm_linked_list_create(int_compare);
  ioopm_list_iterator_t* iter = ioopm_list_iterator(list);

  ioopm_linked_list_append(list, int_elem(1));
  bool result = ioopm_iterator_has_next(iter);
  CU_ASSERT_TRUE(result);

  elem_t next = ioopm_iterator_next(iter);
  result = ioopm_iterator_has_next(iter);
  CU_ASSERT_FALSE(result);

  next = ioopm_iterator_next(iter);
  result = ioopm_iterator_has_next(iter);
  CU_ASSERT_FALSE(result);

  ioopm_iterator_destroy(iter);
  ioopm_linked_list_destroy(list);
}



void test_iter_reset() {
  ioopm_list_t* list = ioopm_linked_list_create(int_compare);
  ioopm_list_iterator_t* iter = ioopm_list_iterator(list);

  ioopm_linked_list_append(list, int_elem(1));
  ioopm_linked_list_append(list, int_elem(2));

  elem_t elem = ioopm_iterator_next(iter);
  elem = ioopm_iterator_next(iter);
  CU_ASSERT_EQUAL(2, elem.i);


  ioopm_iterator_reset(iter);
  elem = ioopm_iterator_next(iter);
  CU_ASSERT_EQUAL(1, elem.i);

  ioopm_iterator_destroy(iter);
  ioopm_linked_list_destroy(list);

}


void test_iter_current() {

  ioopm_list_t* list = ioopm_linked_list_create(int_compare);
  ioopm_list_iterator_t* iter = ioopm_list_iterator(list);

  ioopm_linked_list_append(list, int_elem(1));
  ioopm_linked_list_append(list, int_elem(2));

  elem_t elem = ioopm_iterator_next(iter);
  elem = ioopm_iterator_next(iter);

  elem_t val = ioopm_iterator_current(iter);

  CU_ASSERT_EQUAL(2, val.i);

  ioopm_iterator_destroy(iter);
  ioopm_linked_list_destroy(list);
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
    (CU_add_test(my_test_suite, "test iter has next", test_iter_has_next) == NULL) ||
    (CU_add_test(my_test_suite, "test iter next", test_iter_next) == NULL) ||
    (CU_add_test(my_test_suite, "test iter reset", test_iter_reset) == NULL) ||
    (CU_add_test(my_test_suite, "test iter current", test_iter_current) == NULL) ||
    (CU_add_test(my_test_suite, "test next empty", test_next_empty) == NULL) ||
    (CU_add_test(my_test_suite, "test has next empty", test_has_next_empty) == NULL) ||





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
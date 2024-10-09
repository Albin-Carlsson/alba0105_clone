#include "linked_list.h"
#include "common.h"
#include <CUnit/Basic.h>


//Helper functions definitions
void ioopm_linked_list_change_all(ioopm_link_t* link, elem_t extra);

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

void test_list_create()
{
  ioopm_list_t* lst = ioopm_linked_list_create(int_compare);
  CU_ASSERT_PTR_NOT_NULL(lst);
  ioopm_linked_list_destroy(lst);
}

//för att testa destroy, använd valgrind så man har inga allokerade minne

void test_list_append()
{
  //skappar en ny lista, lägger in int:2
  ioopm_list_t* list = ioopm_linked_list_create(int_compare);
  elem_t new_value = int_elem(2);

  ioopm_linked_list_append(list, new_value);
  ioopm_link_t* ptr = list->first->next;
  //Kollar om pekaren är inte tom
  CU_ASSERT_PTR_NOT_NULL(ptr);

  //samt kollar om valuen som finns i 
  int value = ptr->value.i;
  CU_ASSERT_EQUAL(new_value.i, value);
  CU_ASSERT_NOT_EQUAL(new_value.i, 3);

  //skapar en ny lista med strängar
  ioopm_list_t* str_list = ioopm_linked_list_create(char_compare);
  elem_t new_string = char_elem("two");
  //lägger in strängen i den nya listan
  ioopm_linked_list_append(str_list, new_string);

  ioopm_link_t* str_ptr = str_list->first->next;
  //kollar om pekaren är inte null
  CU_ASSERT_PTR_NOT_NULL(str_ptr);
  char* str = str_ptr->value.c;

  //kollar om strängen matchar med de som har matats in
  CU_ASSERT_TRUE(strcmp(str, "two") == 0);
  CU_ASSERT_FALSE(strcmp(str, "three") == 0);

  ioopm_linked_list_destroy(str_list);
  ioopm_linked_list_destroy(list);
}


void test_list_prepend()
{
  //TEST FÖR INT
  ioopm_list_t* list = ioopm_linked_list_create(int_compare);
  elem_t new_value = int_elem(2);
  //lägger 2 in i listan
  ioopm_linked_list_prepend(list, new_value);
  ioopm_link_t* ptr = list->first->next;
  CU_ASSERT_PTR_NOT_NULL(ptr); //kollar om pointern är inte null
  int value = ptr->value.i;   //tar fram valuen som har lagts in
  CU_ASSERT_EQUAL(new_value.i, value);  //kollar om denna finns i listan
  CU_ASSERT_NOT_EQUAL(new_value.i, 3);

  elem_t new_value2 = int_elem(4);
  ioopm_linked_list_prepend(list, new_value2);
  ptr = list->first->next;
  value = ptr->value.i;
  CU_ASSERT_EQUAL(new_value2.i, value); //kollar om prepend har lagt elementet i början
  ioopm_linked_list_destroy(list);

  //TEST FÖR STRÄNG
  ioopm_list_t* str_list = ioopm_linked_list_create(char_compare);
  elem_t new_string = char_elem("two");
  //lägger in strängen i den nya listan
  ioopm_linked_list_prepend(str_list, new_string);
  ioopm_link_t* str_ptr = str_list->first->next;
  //kollar om pekaren är inte null
  CU_ASSERT_PTR_NOT_NULL(str_ptr);
  char* str = str_ptr->value.c;

  //kollar om strängen matchar med de som har matats in
  CU_ASSERT_TRUE(strcmp(str, "two") == 0);
  CU_ASSERT_FALSE(strcmp(str, "three") == 0);

  //lägger till ett annat element
  elem_t first_str = char_elem("first");
  ioopm_linked_list_prepend(str_list, first_str);

  //tar fram pointern
  str_ptr = str_list->first->next;
  CU_ASSERT_PTR_NOT_NULL(str_ptr);
  str = str_ptr->value.c;
  //kollar om strängen matchar med de som har matats in
  CU_ASSERT_TRUE(strcmp(str, "first") == 0);
  CU_ASSERT_FALSE(strcmp(str, "three") == 0);

  ioopm_linked_list_destroy(str_list);
}


void test_list_insert()
{
  //TEST FOR INT
  ioopm_list_t* list = ioopm_linked_list_create(int_compare);

  //ett försök med valid index
  int index = 0;
  elem_t value = int_elem(4);
  option_list_t result = ioopm_linked_list_insert(list, index, value);
  CU_ASSERT_TRUE(result.success);  //om den har gått igenom
  CU_ASSERT_EQUAL(result.ptr->value.i, value.i);  //om value av den nya pointer är den samma som vi har insertad


  //ett försök med felaktig index-större än size
  index = 4;
  result = ioopm_linked_list_insert(list, index, value);
  CU_ASSERT_FALSE(result.success);

  //ett försök med negativ index
  index = -4;
  result = ioopm_linked_list_insert(list, index, value);
  CU_ASSERT_FALSE(result.success);

  ioopm_linked_list_destroy(list);
}


void test_list_remove()
{
  ioopm_list_t* list = ioopm_linked_list_create(int_compare);

  int index = 0;
  elem_t value = int_elem(4);
  //lägger i två element
  option_list_t result = ioopm_linked_list_insert(list, index, value);
  CU_ASSERT_TRUE(result.success);  //om den är inserted

  index = 1;
  result = ioopm_linked_list_insert(list, index, value);
  CU_ASSERT_TRUE(result.success);  //om den är inserted

  //tar bort ett element med valid index
  result = ioopm_linked_list_remove(list, 0);
  CU_ASSERT_TRUE(result.success);

  //tar bort ett element med invalid-index- större än size-1
  result = ioopm_linked_list_remove(list, 1);
  CU_ASSERT_FALSE(result.success);

  //tar bort ett element med negativ index
  result = ioopm_linked_list_remove(list, -1);
  CU_ASSERT_FALSE(result.success);

  //tar bort ett element som är sist
  result = ioopm_linked_list_remove(list, 0);
  CU_ASSERT_TRUE(result.success);

  ioopm_linked_list_destroy(list);
}


void test_list_get() {
  ioopm_list_t* list = ioopm_linked_list_create(int_compare);
  //skapar två element som ska läggas in i listan
  int index = 0;
  elem_t value = int_elem(4);
  int index2 = 1;
  elem_t value2 = int_elem(3);
  option_list_t result = ioopm_linked_list_insert(list, index, value);
  option_list_t result2 = ioopm_linked_list_insert(list, index2, value2);

  //ser till att båda länk är med i listan
  CU_ASSERT_TRUE(result.success);
  CU_ASSERT_TRUE(result2.success);

  //index är valid
  option_list_t valid = ioopm_linked_list_get(list, index2);
  CU_ASSERT_TRUE(valid.success);
  CU_ASSERT_EQUAL(valid.ptr->value.i, value2.i);


  //index är större än size (finns inte med)
  option_list_t invalid = ioopm_linked_list_get(list, 3);
  CU_ASSERT_FALSE(invalid.success);

  //index är negativ
  invalid = ioopm_linked_list_get(list, -4);
  CU_ASSERT_FALSE(invalid.success);
  ioopm_linked_list_destroy(list);

}


void test_list_contains() {

  ioopm_list_t* list = ioopm_linked_list_create(int_compare);
  ioopm_linked_list_prepend(list, int_elem(3));

  //lägger value 3, kollar om de finns
  bool result = ioopm_linked_list_contains(list, int_elem(3));
  CU_ASSERT_TRUE(result);

  //kollar om value 4 finns, nej
  bool false_result = ioopm_linked_list_contains(list, int_elem(4));
  CU_ASSERT_FALSE(false_result);

  ioopm_linked_list_destroy(list);

}

void test_list_size() {
  ioopm_list_t* list = ioopm_linked_list_create(int_compare);
  //tom lista, alltså size=0
  int size = ioopm_linked_list_size(list);
  CU_ASSERT_EQUAL(size, 0);

  //lägger två element
  option_list_t result = ioopm_linked_list_insert(list, 0, int_elem(1));
  option_list_t result2 = ioopm_linked_list_insert(list, 1, int_elem(2));
  //ser till att båda länk är med i listan
  CU_ASSERT_TRUE(result.success);
  CU_ASSERT_TRUE(result2.success);
  size = ioopm_linked_list_size(list);
  CU_ASSERT_EQUAL(size, 2);

  //tar bort ett element
  result = ioopm_linked_list_remove(list, 0);
  CU_ASSERT_TRUE(result.success);
  size = ioopm_linked_list_size(list);
  CU_ASSERT_EQUAL(size, 1);

  ioopm_linked_list_destroy(list);

}

void test_list_is_empty() {
  ioopm_list_t* list = ioopm_linked_list_create(int_compare);
  //empty lista
  bool empty = ioopm_linked_list_is_empty(list);
  CU_ASSERT_TRUE(empty);

  //lägger ett element
  option_list_t result = ioopm_linked_list_insert(list, 0, int_elem(1));
  empty = ioopm_linked_list_is_empty(list);
  CU_ASSERT_FALSE(empty);

  ioopm_linked_list_destroy(list);


}

void test_list_clear() {
  ioopm_list_t* list = ioopm_linked_list_create(int_compare);
  //lägger ett element i listan
  option_list_t result = ioopm_linked_list_insert(list, 0, int_elem(1));
  bool empty = ioopm_linked_list_is_empty(list);
  CU_ASSERT_FALSE(empty);

  ioopm_linked_list_clear(list);
  empty = ioopm_linked_list_is_empty(list);
  CU_ASSERT_TRUE(empty);
  //kollar om både first och last pekar på dummy
  CU_ASSERT_PTR_EQUAL(list->first, list->last);

  ioopm_linked_list_destroy(list);
}

void test_list_all() {
  ioopm_list_t* list = ioopm_linked_list_create(int_compare);

  //testar på en tom lista
  bool result = ioopm_linked_list_all(list, ioopm_linked_list_modulo, int_elem(2));
  CU_ASSERT_FALSE(result);

  //testar på en lista där alla ellement uppfyller prop
  ioopm_linked_list_append(list, int_elem(2));
  ioopm_linked_list_append(list, int_elem(4));
  ioopm_linked_list_append(list, int_elem(6));
  result = ioopm_linked_list_all(list, ioopm_linked_list_modulo, int_elem(2));
  CU_ASSERT_TRUE(result);

  //testar på en lista med blandade element
  ioopm_linked_list_append(list, int_elem(3));
  result = ioopm_linked_list_all(list, ioopm_linked_list_modulo, int_elem(2));
  CU_ASSERT_FALSE(result);

  ioopm_linked_list_destroy(list);
}


void test_list_any() {
  ioopm_list_t* list = ioopm_linked_list_create(int_compare);

  //testar på en tom lista
  bool result = ioopm_linked_list_all(list, ioopm_linked_list_modulo, int_elem(2));
  CU_ASSERT_FALSE(result);

  //testar på en lista där inget element uppfyller prop
  ioopm_linked_list_append(list, int_elem(3));
  result = ioopm_linked_list_all(list, ioopm_linked_list_modulo, int_elem(2));
  CU_ASSERT_FALSE(result);

  option_list_t t = ioopm_linked_list_remove(list, 0);

  //testar på en lista med bara ett element
  ioopm_linked_list_append(list, int_elem(2));
  result = ioopm_linked_list_all(list, ioopm_linked_list_modulo, int_elem(2));
  CU_ASSERT_TRUE(result);


  //testar på en lista där alla ellement uppfyller prop
  ioopm_linked_list_append(list, int_elem(4));
  ioopm_linked_list_append(list, int_elem(6));
  result = ioopm_linked_list_all(list, ioopm_linked_list_modulo, int_elem(2));
  CU_ASSERT_TRUE(result);
  ioopm_linked_list_destroy(list);
}


void test_list_apply_to_all() {
  ioopm_list_t* list = ioopm_linked_list_create(int_compare);
  ioopm_linked_list_append(list, int_elem(4));
  ioopm_linked_list_append(list, int_elem(6));
  ioopm_linked_list_apply_to_all(list, ioopm_linked_list_change_all, int_elem(1));

  //kollar på value in i de 2 index, ser om de är 1
  int value = 1;
  option_list_t valid = ioopm_linked_list_get(list, 0);
  int valid_value = valid.ptr->value.i;
  CU_ASSERT_EQUAL(valid_value, value);



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
    (CU_add_test(my_test_suite, "test list create", test_list_create) == NULL) ||
    (CU_add_test(my_test_suite, "test list append", test_list_append) == NULL) ||
    (CU_add_test(my_test_suite, "test list prepend", test_list_prepend) == NULL) ||
    (CU_add_test(my_test_suite, "test list insert", test_list_insert) == NULL) ||
    (CU_add_test(my_test_suite, "test list remove", test_list_remove) == NULL) ||
    (CU_add_test(my_test_suite, "test list get", test_list_get) == NULL) ||
    (CU_add_test(my_test_suite, "test list contains", test_list_contains) == NULL) ||
    (CU_add_test(my_test_suite, "test list size", test_list_size) == NULL) ||
    (CU_add_test(my_test_suite, "test list is empty", test_list_is_empty) == NULL) ||
    (CU_add_test(my_test_suite, "test list clear", test_list_clear) == NULL) ||
    (CU_add_test(my_test_suite, "test list all", test_list_all) == NULL) ||
    (CU_add_test(my_test_suite, "test list apply all", test_list_apply_to_all) == NULL) ||
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
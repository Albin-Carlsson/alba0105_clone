hash_test: hash_table_tests.c
		gcc -Wall -I/opt/homebrew/opt/cunit/include -L/opt/homebrew/opt/cunit/lib linked_list.c hash_table.c hash_table_tests.c -lcunit -o hash_table_tests  --coverage

hash_table: hash_table.c
		gcc -Wall hash_table.c 

mem_check: hash_table_tests
	valgrind -s  ./hash_table_tests  

full_mem_check: hash_table_tests
	valgrind -s --leak-check=full  ./hash_table_tests  

list_test: linked_list_tests.c
		gcc -Wall -I/opt/homebrew/opt/cunit/include -L/opt/homebrew/opt/cunit/lib linked_list.c linked_list_tests.c -lcunit -o linked_list_tests

list_mem_check: linked_list_tests
	valgrind -s ./linked_list_tests

list_full_mem_check: linked_list_tests
	valgrind -s --leak-check=full ./linked_list_tests

list_test1:linked_list_tests.c
	gcc linked_list_tests.c linked_list.c -o linked_list_tests -lcunit

iter_test: iterator.c
	gcc -o iterator_tests linked_list.c iterator.c iterator_tests.c  -lcunit 

iter_mem: iterator_tests.c
	valgrind -s --leak-check=full  ./iterator_tests

freq: freq_count.c
	gcc -Wall hash_table.c linked_list.c iterator.c  hasfreq_count.c -o freq_count

freq_mem: freq_count.c
	valgrind -s --leak-check=full  ./freq_count

profile: freq_count.c
	gcc -pg -o my_program freq_count.c hash_table.c linked_list.c iterator.c

clean: 
	rm *.gcno 




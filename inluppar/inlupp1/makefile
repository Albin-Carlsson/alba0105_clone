#Explanation:
#make file_test -compiles the test for the specific file
#make file_mem_check  -runs the file through valgrind
#make file_full_mem_check   -runs the file through valgrind for the descriptive rapport
#make file_coverage   -coverage test 


hash_test: hash_table_tests.c
	gcc -Wall -I/opt/homebrew/opt/cunit/include -L/opt/homebrew/opt/cunit/lib linked_list.c hash_table.c hash_table_tests.c -lcunit -o hash_table_tests  

ht_mem_check: hash_table_tests
	valgrind -s  ./hash_table_tests  

ht_full_mem_check: hash_table_tests
	valgrind -s --leak-check=full  ./hash_table_tests  

ht_coverage: hash_table_tests.c
	gcc -Wall linked_list.c hash_table.c hash_table_tests.c -lcunit -o hash_table_tests --coverage


list_test:linked_list_tests.c
	gcc linked_list_tests.c linked_list.c -o linked_list_tests -lcunit

list_mem_check: linked_list_tests
	valgrind -s ./linked_list_tests

list_full_mem_check: linked_list_tests
	valgrind -s --leak-check=full ./linked_list_tests

list_coverage:linked_list_tests.c
	gcc linked_list_tests.c linked_list.c -o linked_list_tests -lcunit --coverage



iter_test: iterator_tests.c
	gcc -o iterator_tests linked_list.c iterator.c iterator_tests.c  -lcunit 

iter_mem_check: iterator_tests.c
	valgrind -s --leak-check=full  ./iterator_tests

iter_coverage: iterator_tests.c
	gcc -o iterator_tests linked_list.c iterator.c iterator_tests.c  -lcunit --coverage


freq: freq_count.c
	gcc -Wall hash_table.c linked_list.c iterator.c freq_count.c -o freq_count

freq_mem: freq_count.c
	valgrind -s --leak-check=full  ./freq_count

freq_test: freq_count_tests.c
	gcc -DTESTING freq_count_tests.c freq_count.c linked_list.c hash_table.c iterator.c -lcunit -o freq_count_tests

freq_mem_check: freq_count_tests
	valgrind -s ./freq_count_tests

freq_coverage: freq_count_tests.c
	gcc -DTESTING freq_count_tests.c freq_count.c linked_list.c hash_table.c iterator.c -lcunit --coverage -o freq_count_tests


#compiling the freq_count file with the profiling tool
profile: freq_count.c
	gcc -pg -o my_program freq_count.c hash_table.c linked_list.c iterator.c

clean: 
	rm -f *.gcno  *.gcda *.info *.gcov hash_hable_tests linked_list_tests iterator_tests freq_count_tests
	rm -rf coverage_report/

comp_test: hash_test list_test iter_test freq_test

test: hash_test list_test iter_test freq_test
	./hash_table_tests
	./linked_list_tests
	./iterator_tests
	./freq_count_tests

cov_test: ht_coverage list_coverage iter_coverage freq_coverage

# Generate Coverage Report with lcov
cov_report: cov_test
	lcov --rc lcov_branch_coverage=1 --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage_report
	


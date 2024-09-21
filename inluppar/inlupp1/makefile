hash_test: hash_table_tests.c
		gcc -Wall -I/opt/homebrew/opt/cunit/include -L/opt/homebrew/opt/cunit/lib hash_table.c hash_table_tests.c -lcunit -o hash_table_tests

hash_table: hash_table.c
		gcc -Wall hash_table.c 

mem_check: hash_table_tests
	valgrind -s  ./hash_table_tests  

full_mem_check: hash_table_tests
	valgrind -s --leak-check=full  ./hash_table_tests  
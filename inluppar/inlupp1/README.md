#Getting started
In order to be able to run the program you need to have a C compiler (in our case we use gcc), a virtual machine (if you have non-linux OS), CUnit testing framework, valgrind installed (for checking any memory leaks), and gcov tool installed(for checking the coverage of the tests).

#Running tests
In order to run tests for the code we have created makefile commandos. For example, for running the tests of hash_table_tests.c file, follow the instructions:
$make hash_test
$./hash_table_tests
Please check the makefile provided to run the test on all files.

##Coverage tests
The tool used for checking the coverage is gcov. In order to test the coverage of our tests, run the following commands:
$make file_coverage
$./file_test
$gcov -b -c file
(file is the desired .gcda file)

Current coverage procents:
File                      Line coverage %          Branch coverage %
hash_table.c                    98                         100
linked_list.c                   99                         100
iterator.c                     100                         100
freq_count.c                    95                         100


#Good to know
##Error handling
In order to handle errors from functions (such as a failed insert or remove) we have introduced the struct option(both for the hash table and lists). Most of the functions return such a struct that indicates if the operation was successfull through a true bool, and if so a pointer to the variable that has been changed or the false bool if it failed. 

##Important information
-The hashtable doesn't take ownership over its keys and values
-It is the programmer's responsibility to correctly introduce elements into the hash table/linked list based on the comparing function provided (can't introduce integers in a list where the comparison function takes char parameters).

#Initial Profiling Results

The results presented below can be found in the analysis.txt. Here are the commandos needed for that:
$make profile
$./my program file.txt (the file is the different files we tested on)
$gprof my_program gmon.out > analysis.txt



For each input, what are the top 3 functions?
1k-long-words: 1.char_compare  2.key_equiv. 3.find_previous_entry_for_key
10k-long-words: 1.ioopm_hash_table_size.   2.char_compare.  3.key_equiv
16k-long-words: 1.ioopm_hash_table_size.   2.char_compare.  3.key_equiv
Small:1.char_compare.  2.key_equiv.  3.ioopm_hash_table_size


For each input, are the top 3 functions in your code (that you have written), or is it in library functions?
It is the code that we have written.


Are the top 3 functions in your code consistent across the inputs? Why? Why not?
Consistent Functions:
char_compare and key_equiv appear in the top 3 for all inputs, showing that these operations are central to the program’s execution, regardless of input size. This consistency is due to the fact that these functions are fundamental for the hash table's functioning, so they are called frequently, no matter the size of the input. 

Inconsistencies:
find_previous_entry_for_key is present only in the smallest input (1k-long-words), while it disappears in larger inputs. This is caused because n small inputs, there may not be many different keys, so collisions are more likely to occur in hash tables. 

ioopm_hash_table_size reaches the top in larger inputs (10k, 16k, Small) but does not appear in the top 3 for the smallest input (1k-long-words). This is because the functions does more operations as the data structure increases.


Is there some kind of trend? (Possibly several)
There are trends that can be noticed through profiling:
1.Comparison functions are dominant, since they are fundamental functions for a hash_table (insertion)
2.Size functions increase in importance for larger inputs.


Do the results correspond with your expectations?
The results match our expectations. It seems reasonable that comparison functions dominate while handling hash table operations, since they are mandatory for each one . We had also thought about how "resource-craving" the size function is, since it simply iterates over the entire hash table, and later used in different other functions. 

We considered the presence of find_previous_key in the top 3 profiled functions unexpected, especially with smaller data, but this shows that there is room for improvement with our code. 

Based on these results, do you see a way to make your program go faster?
Yes, the result show there is definetly room for improvement. We could change the way we control the size of the hash table from iterating through it to just storing a variable that keeps track of it in the struct. However, the behaviour of find_previous_link needs to be analyzed, as well as the multiple calls that are made to it. 

#ifndef BUBBLE_SORT
#define BUBBLE_SORT

#include <assert.h>
#include <stdio.h>

int   set_string_addresses (char* buffer, char** raw_address, int number_of_raws, int array_size);
int   bubble_sort          (char** raw_address, int number_of_raws);
int   quick_sort           (char** raw_address, int number_of_raws, int (*compare_func)(char* str1, char* str2));

#endif // BUBBLE_SORT
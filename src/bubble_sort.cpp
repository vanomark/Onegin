#include "bubble_sort.h"
#include "comparers.h"

int set_string_addresses(char* buffer, char** raw_address, int number_of_raws, int array_size)
{   
    assert(raw_address);
    assert(buffer);

    for (int i = 0, raw_number = 0; i < array_size; i++) {

        if (buffer[i] == '\n') {
            buffer[i] = '\0';
            raw_number++; 

            if (i + 1 <= array_size - number_of_raws) {                      
                raw_address[raw_number] = &buffer[i + 1];     
            } else {
                buffer[i] = '\0';
                raw_address[raw_number] = 0;
                break;
            }   
        } 
    }

    return 0;
}

int quick_sort(char** raw_address, int number_of_raws, int (*compare_func)(char*, char*))
{
    assert(raw_address);

    for(int sort_count = 0; sort_count < number_of_raws; sort_count++) {
        for (int i = 1; i < number_of_raws; i++) {

            char *str = 0;
            if ((*compare_func)(raw_address[i-1], raw_address[i]) > 0) {       
                
                str = *(char **) ( (size_t) raw_address + (i-1) * sizeof(char *) );
                raw_address[i-1] = raw_address[i];
                raw_address[i] = str;

            } 
        }
    }

    return 0;
}
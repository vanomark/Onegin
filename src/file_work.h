#ifndef FILE_WORK
#define FILE_WORK

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int   get_file_info        (const char* name_of_file, char** buffer, char*** raw_address, int* size_of_file, int* number_of_raws);
int   tell_file_size       (FILE* fp);
int   create_text_file     (const char* name_of_file, int number_of_raws, char** raw_address);

const int min_str_length = 10;

struct text_file_stat {
    FILE*  name_of_file;
    char*  buffer;
    char** raw_address;
    int    number_of_raws;
    int    size_of_file;
};

#endif //FILE_WORK
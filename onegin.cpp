#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/stat.h>
// #include <TXLib.h>

int   get_file_info        (const char* name_of_file, char** buffer, char*** raw_address, int* size_of_file, int* number_of_raws);
int   tell_file_size       (FILE* fp);
int   set_string_addresses (char* buffer, char** raw_address, int number_of_raws, int array_size);
int   bubble_sort          (char** raw_address, int number_of_raws);
int   quick_sort           (char** raw_address, int number_of_raws, int (*compare_func)(char* str1, char* str2));
int   string_compare       (char* str1, char* str2);
int   rev_string_compare   (char* str1, char* str2);
int   turn_lowercase       (char* str);
int   create_text_file     (const char* name_of_file, int number_of_raws, char** raw_address);

const int min_str_length = 10;

struct text_file_stat {
    FILE*  name_of_file;
    char*  buffer;
    char** raw_address;
    int    number_of_raws;
    int    size_of_file;
};

int main(const int argc, char* const argv[])
{   
    text_file_stat onegin = {};

    get_file_info("start_file.txt", &onegin.buffer, &onegin.raw_address, &onegin.size_of_file, &onegin.number_of_raws);

    assert(onegin.buffer);
    assert(onegin.raw_address);

    set_string_addresses(onegin.buffer, onegin.raw_address, onegin.number_of_raws, onegin.size_of_file);    
    quick_sort(onegin.raw_address, onegin.number_of_raws, &string_compare);
    create_text_file("finish_file.txt", onegin.number_of_raws, onegin.raw_address);

    return 0;
}

int get_file_info(const char* name_of_file, char** buffer, char*** raw_address, int* size_of_file, int* number_of_raws)
{   
    assert(name_of_file);
    
    FILE *openfile = fopen(name_of_file, "r");
    *size_of_file = tell_file_size(openfile);
    *buffer = (char *) calloc(*size_of_file + 1, sizeof(char));
    *number_of_raws = *size_of_file - fread(*buffer, sizeof(char), *size_of_file, openfile);
    *raw_address = (char **) calloc(*number_of_raws + 1, sizeof(char *));
    *raw_address[0] = *buffer;

    assert(buffer);
    assert(size_of_file);
    assert(number_of_raws);
    assert(raw_address);

    fclose(openfile);

    return 0;
}

int tell_file_size(FILE* fp)
{
    fseek(fp, 0, SEEK_END);
    int size_of_file = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    return size_of_file;
}

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
int rev_string_compare(char *str1, char *str2)
{
    assert(str1);
    assert(str2);

    for (int i = strlen(str1) - 1, j = strlen(str2) - 1; i > 0, j > 0; i--, j--) {
        
        while (!isalpha(str1[i]) && i > 0)
            i--;
        while (!isalpha(str2[j]) && j > 0)
            j--;

        char ch1 = str1[i];
        char ch2 = str2[j];

        turn_lowercase(&ch1);
        turn_lowercase(&ch2);

        if (ch1 - ch2 != 0)
            return ch1 - ch2;
    }

    return 0;
}

int string_compare(char *str1, char *str2)
{   
    assert(str1);
    assert(str2);

    for (int i = 0, j = 0; i <= strlen(str1), j <= strlen(str2); i++, j++) {

        while (!isalpha(str1[i]) && str1[i] != '\0')
            i++;
        while (!isalpha(str2[j]) && str2[j] != '\0')
            j++;

        char ch1 = str1[i];
        char ch2 = str2[j];

        turn_lowercase(&ch1);
        turn_lowercase(&ch2);
        
        if (i == 0) 
            str1[i] = (char) toupper(str1[i]);
        if (j == 0)
            str2[j] = (char) toupper(str2[j]);

        if (ch1 - ch2 != 0)
            return ch1 - ch2;
    }

    return 0;
}

int turn_lowercase(char *str) 
{   
    assert(str);

    int i = 0;
    while (str[i] != '\0') {
        str[i] = (char) tolower(str[i]);
        i++;
    }

    return 0;
}

int create_text_file(const char* name_of_file, int number_of_raws, char** raw_address)
{   
    assert(name_of_file);
    assert(raw_address);

    FILE *finish_file = fopen(name_of_file, "wb");
    assert(finish_file);

    for (int raw_number = 0; raw_number < number_of_raws; raw_number++) {
        if (strlen(raw_address[raw_number]) > min_str_length) 
            fprintf(finish_file, "%-50s\n", raw_address[raw_number]);
    }
    fclose(finish_file);

    return 0;
}

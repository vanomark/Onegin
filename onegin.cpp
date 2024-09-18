#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/stat.h>
// #include <TXLib.h>

int     tell_file_size              (FILE * fp);
int     determine_string_addresses  (char* *raw_address, char* buffer, int number_of_raws, int array_size);
void    bubble_sort                 (char* *raw_address, int number_of_raws);
int     string_compare              (char *str1, char *str2);
int     turn_lowercase              (char *str);
int     create_text_file            (const char * name_of_file, int number_of_raws, char* *raw_address);

typedef int(* compare_func_t)(void *a, void *b);

int main()
{   
    FILE*   openfile        = NULL;
    char*   buffer          = NULL;
    char**  raw_address     = NULL;
    int     size_of_file    = 0;
    int     number_of_raws  = 0;

    openfile = fopen("start_file.txt", "r");

    size_of_file = tell_file_size(openfile);
    buffer = (char *) calloc(size_of_file + 1, sizeof(char));

    number_of_raws = size_of_file - fread(buffer, sizeof(char), size_of_file, openfile);
    fclose(openfile);

    raw_address = (char **) calloc(number_of_raws + 1, sizeof(char *));

    assert(openfile);
    assert(buffer);
    assert(raw_address);

    raw_address[0] = buffer;
    buffer[size_of_file + 1] = '\0';

    determine_string_addresses(raw_address, buffer, number_of_raws, size_of_file);    
    bubble_sort(raw_address, number_of_raws);
    create_text_file("finish_file.txt", number_of_raws, raw_address);

    return 0;
}

int tell_file_size(FILE * fp)
{
    fseek(fp, 0, SEEK_END);
    int size_of_file = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    return size_of_file;
}

int determine_string_addresses(char* *raw_address, char* buffer, int number_of_raws, int array_size)
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

void bubble_sort(char* *raw_address, int number_of_raws) 
{   
    assert(raw_address);

    printf("%d\n", number_of_raws);

    for(int sort_count = 0; sort_count < number_of_raws; sort_count++) {
        for (int i = 1; i < number_of_raws; i++) {

            char *str = 0;
            if (string_compare(raw_address[i-1], raw_address[i]) > 0) {       
                
                str = raw_address[i-1];
                raw_address[i-1] = raw_address[i];
                raw_address[i] = str;

            } 
        }
    }
}

int string_compare(char *str1, char *str2)
{   
    assert(str1);
    assert(str2);

    for (size_t i = 0; i < strlen(str1); i++) {

        char ch1 = str1[i];
        char ch2 = str2[i];

        turn_lowercase(&ch1);
        turn_lowercase(&ch2);
        
        if (i == 0) {
            str1[i] = (char) toupper(str1[i]);
            str2[i] = (char) toupper(str2[i]);
        }

        if (!isalnum(ch1)) {
            
        }

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

int create_text_file(const char * name_of_file, int number_of_raws, char* *raw_address)
{   
    assert(name_of_file);
    assert(raw_address);

    FILE *finish_file = fopen(name_of_file, "wb");
    assert(finish_file);

    for (int raw_number = 0; raw_number < number_of_raws; raw_number++) {
        if (strlen(raw_address[raw_number]) > 22) //todo
            fprintf(finish_file, "%s\n", raw_address[raw_number]);
    }
    fclose(finish_file);

    return 0;
}


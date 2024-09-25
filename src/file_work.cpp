#include "file_work.h"

int get_file_info(const char* name_of_file, char** buffer, char*** raw_address, int* size_of_file, int* number_of_raws)
{   
    FILE *open_file = 0;
    if ((open_file = fopen(name_of_file, "r")) == 0) {
        fclose(open_file);
        open_file = fopen("onegin_text.txt", "r");
    }
    assert(open_file);

    *size_of_file = tell_file_size(open_file);
    *buffer = (char *) calloc(*size_of_file + 1, sizeof(char));
    *number_of_raws = *size_of_file - fread(*buffer, sizeof(char), *size_of_file, open_file);
    *raw_address = (char **) calloc(*number_of_raws + 1, sizeof(char *));
    *raw_address[0] = *buffer;

    assert(buffer);
    assert(size_of_file);
    assert(number_of_raws);
    assert(raw_address);

    fclose(open_file);

    return 0;
}

int tell_file_size(FILE* fp)
{
    fseek(fp, 0, SEEK_END);
    int size_of_file = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    return size_of_file;
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
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/stat.h>
// #include <TXLib.h>

void    bubble_sort          (char* *raw_address, int number_of_raws);
int     turn_lowercase       (char *str);
int     string_compare       (char *str1, char *str2);

int main()
{   
    FILE *onegin = fopen("start_file.txt", "rb");
    assert(onegin);
    
    fseek(onegin, 0, SEEK_END);
    int size_of_file = ftell(onegin);
    fseek(onegin, 0, SEEK_SET);

    char *buffer = (char *) calloc(size_of_file + 1, sizeof(char));
    assert(buffer);
    buffer[size_of_file + 1] = '\0';
    
    fprintf(stderr, "address of buffer: %d\n", buffer);

    printf("%d %d %d\n", fread(buffer, sizeof(char), size_of_file, onegin), size_of_file, sizeof(buffer));
    fprintf(stderr, "address of buffer: %d\n", buffer);
                                                                               // int ptrsize = 10;

    int number_of_raws = 0;
    for (int i = 0; i < size_of_file; i++) {
        if (buffer[i] == '\n')       
            number_of_raws++; 
    }   
    
    char* *raw_address = (char* *) calloc(number_of_raws + 1, sizeof(char));
    raw_address[0] = buffer;

    for (int i = 0, raw_number = 0; i < size_of_file; i++) {

        if (i == 0) 
            printf("%d: %d\n", i, &buffer[i]);

        if (buffer[i] != '\r' )
            printf("%c", buffer[i]);

        if (buffer[i] == '\r') {
            buffer[i] = '\0';
            raw_number++; 
            fprintf(stderr, "\naddress of %d elem of buffer: %d\n", i, &buffer[i]);
            fprintf(stderr, "%d %d %d\n", raw_number, number_of_raws, sizeof(raw_address));

            if (i + 2 <= size_of_file) {                      // i i+1 i+2
                raw_address[raw_number] = &buffer[i + 2];     // \r \n A
                printf("%d: %s\n", raw_number-1, raw_address[raw_number-1]);
            } else {
                fprintf(stderr, "ABABABFKEFMEWMFPWEMFPWEPFWEFWPEOFPWOEFPOW\n[%d] [%c] [%s]\n", i, buffer[i], raw_address[raw_number]);
                buffer[i] = '\0';
                raw_address[raw_number] = 0;
                break;
            }   
            
        
        } 
    }
       
    fclose(onegin);

                                                                                // int number_of_raws = 0;
                                                                                // for (int i = 0, raw_number = 0; i < size_of_file; i++) {
                                                                                //     number_of_raws = raw_number;

                                                                                //     printf("%c", buffer[i]);

                                                                                //     if (buffer[i] == '\r') {
                                                                                //         buffer[i] = '\0';
                                                                                        
                                                                                //         printf("%d %d %d\n", raw_number, ptrsize, sizeof(raw_address));

                                                                                //         if (raw_number >= ptrsize) {
                                                                                //             printf("HUUY\n\n");
                                                                                //             ptrsize *= 2;
                                                                                            
                                                                                //             printf("%d %d \n", raw_number, ptrsize);

                                                                                //             raw_address = (char **) realloc(raw_address, (ptrsize + 1) * sizeof(char));
                                                                                //             assert(raw_address);
                                                                                //         }
                                                                                //         raw_address[raw_number] = buffer + i + 2;      
                                                                                //         raw_number++; 
                                                                                //     }
                                                                                // }   
                                                                                // fclose(onegin);

    for (int raw_number = 0; raw_number < number_of_raws; raw_number++) {
        if (1)
            printf("%s\n", raw_address[raw_number]);
    }
    
    bubble_sort(raw_address, number_of_raws);
    raw_address[number_of_raws + 1] = 0;

    for (int i = 0; i < number_of_raws; i++) {
        printf("%s\n", raw_address[i]);


    }

    FILE *finish_file = fopen("finish_file.txt", "wb");
    assert(finish_file);

    for (int raw_number = 0; raw_number < number_of_raws; raw_number++) {
        if (1)
            printf("%s\n", raw_address[raw_number]);
            fprintf(finish_file, "%s\n", raw_address[raw_number]);
    }
    fclose(finish_file);

    return 0;
}

void bubble_sort(char* *raw_address, int number_of_raws) 
{   
    assert(raw_address);

    printf("%d\n", number_of_raws);

    for(int sort_count = 0; sort_count < number_of_raws; sort_count++) {
        for (int i = 1; i < number_of_raws; i++) {

            // printf("prev %d %s \n curr %d %s \n", raw_address[i-1], raw_address[i-1], raw_address[i], raw_address[i]);
            char *str = 0;
            if (string_compare(raw_address[i-1], raw_address[i]) > 0) {       
                
                str = raw_address[i-1];
                raw_address[i-1] = raw_address[i];
                raw_address[i] = str;

            } 
        }
    }
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

int string_compare(char *str1, char *str2)
{   
    assert(str1);
    assert(str2);

    for (size_t i = 0; i < strlen(str1); i++) {

        char ch1 = *(str1 + i);
        char ch2 = *(str2 + i);

        turn_lowercase(&ch1);
        turn_lowercase(&ch2);
        
        if (ch1 - ch2 != 0)
            return ch1 - ch2;
    }

    return 0;
}

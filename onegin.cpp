#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

const int number_of_raws = 9;
const int length_of_raw = 50;

void bubble_sort(char *index[]);
int turn_lowercase(char *str);
int string_compare(const char *str1, const char *str2);

int main()
{   
    char string[length_of_raw] = "";
    char text[number_of_raws][length_of_raw] = {};
    char *index[number_of_raws] = {};

    printf("%d\n", strlen("skdfkjdsjkvbkfjvekjfverjnvkejrnkvjenrkjvenrjvnkenkrevkerjnvkerjvksjdcnkenkfcrkec"));

    FILE *onegin = fopen("start_file.txt", "r");
    for (int i = 0; fscanf(onegin, "%s", string) != EOF; i++) {
        printf("%s\n", string);
        strcpy(text[i], string);
        printf("%s\n", text[i]);
    }   

    for (int i = 0; i < number_of_raws; i++)
            index[i] = text[0] + i * length_of_raw;

    for (int i = 0; i < number_of_raws; i++) {
        printf("%d: %s\n", (size_t) index[i], index[i]);

        for (int j = 0; j < length_of_raw; j++) {
            printf("%d: %c\n", (size_t) index[i] + j, index[i][j]);
        }
    }


    printf("%d\n", strcmp("abcd", "abcs"));
    bubble_sort(&index[0]);

    for (int i = 0; i < number_of_raws; i++) {
        printf("%d: %s\n", (size_t) index[i], index[i]);

        for (int j = 0; j < length_of_raw; j++) {
            printf("%d: %c\n", (size_t) index[i] + j, index[i][j]);
        }
    }

    return 0;
}

void bubble_sort(char* *index) 
{   
    assert(index);
    
    for(int sort_count = 0; sort_count < number_of_raws; sort_count++) {
        char *str = 0;
        for (int i = 1; i < number_of_raws; i++) {

            if (string_compare(index[i-1], index[i]) > 0) {

                str = index[i-1];
                index[i-1] = index[i];
                index[i] = str;


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

int string_compare(const char *str1, const char *str2)
{   
    assert(str1);
    assert(str2);

    for (int i = 0; i < length_of_raw; i++) {

        char ch1 = *(str1 + i);
        char ch2 = *(str2 + i);

        turn_lowercase(&ch1);
        turn_lowercase(&ch2);

        if (ch1 - ch2 > 0)
            return 1;
        if (ch1 - ch2 < 0)
            return -1;
    }

    return 0;
}


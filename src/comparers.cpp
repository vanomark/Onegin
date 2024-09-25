#include "comparers.h"

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

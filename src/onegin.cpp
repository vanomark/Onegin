// #include <TXLib.h>

#include "bubble_sort.h"
#include "comparers.h"
#include "file_work.h"

int main(const int argc, char* const argv[])
{   
    text_file_stat onegin = {};

    get_file_info(argv[1], &onegin.buffer, &onegin.raw_address, &onegin.size_of_file, &onegin.number_of_raws);

    assert(onegin.buffer);
    assert(onegin.raw_address);

    set_string_addresses(onegin.buffer, onegin.raw_address, onegin.number_of_raws, onegin.size_of_file);  

    if (!strcmp(argv[2], "-1"))
        quick_sort(onegin.raw_address, onegin.number_of_raws, &rev_string_compare);
    else
        quick_sort(onegin.raw_address, onegin.number_of_raws, &string_compare);

    create_text_file("sorted_text.txt", onegin.number_of_raws, onegin.raw_address);

    return 0;
}

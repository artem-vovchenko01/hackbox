#include "hack_utils.h"

int str_ends_with(const char *str, const char *suffix)
{
    int str_len = strlen(str);
    int suffix_len = strlen(suffix);
    if (str_len >= suffix_len)
    {
        str += str_len - suffix_len;
        return strcmp(str, suffix);
    }
    return -1;
}


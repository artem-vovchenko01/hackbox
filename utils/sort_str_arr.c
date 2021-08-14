#include "utils_include.h"

int str_cmp(const void *v1, const void *v2);

void str_arr_sort(char **str_arr, int n)
{
    qsort(str_arr, n, sizeof(char *), str_cmp);
}

int str_cmp(const void *v1, const void *v2)
{
    const char *s1 = *(const char **) v1;
    const char *s2 = *(const char **) v2;
    return strcmp(s1, s2);
}
 

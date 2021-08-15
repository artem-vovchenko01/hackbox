#include<stdarg.h>
#include "utils_include.h"

char *strcat_all(int n, ...)
{
    va_list arg_list;
    char *my_arg;
    va_start(arg_list, n);
    char *res = malloc(sizeof(char));
    res[0] = '\0';
    int total_len = 0;
    while (n--)
    {
        my_arg = va_arg(arg_list, char *);
        total_len += strlen(my_arg);
        
        res = realloc(res, total_len);
        strcat(res, my_arg);
    }
    va_end(arg_list);
    return res;
}


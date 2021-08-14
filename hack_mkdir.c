#include "hackbox.h"
#define DIR_EXISTS "mkdir: cannot create directory \"%s\": File exists\n"

int hack_mkdir(char **args, int n)
{
    int ret = 0;
    struct stat dir_stat = {0};
    while (n-- > 0)
    {
        if (stat(*args, &dir_stat) == -1)
        {
            mkdir(*args, 0755);
        }
        else
        {
            fprintf(stderr, DIR_EXISTS, *args);
            ret = 1;
        }
        args++;
    }
    return ret;
}




#include "hackbox.h"
#include <errno.h>

#define ERR_MSG "mkdir: cannot create directory '%s': %s\n"
#define DIR_PERM 0755

int hack_mkdir(char **args, int n)
{
    int ret, lasterr = 0;
    while (n-- > 0)
    {
        if ((ret = mkdir(*args, DIR_PERM)))
        {
            fprintf(stderr, ERR_MSG, *args, strerror(errno));
            lasterr = ret;
        }
        args++;
    }
    return lasterr;
}


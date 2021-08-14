#include "hackbox_include.h"
#include "hackbox.h"
#include <errno.h>

#define ERR_MSG "mkdir: cannot create directory '%s': %s\n"
#define DIR_PERM 0755
#define ERR_NO_ARGS "mkdir: missing operand\n"

int hack_mkdir(char **files, int n)
{
    int ret = 0;
    if (n == 0)
    {
        fprintf(stderr, ERR_NO_ARGS);
        return 1;
    }
    while (n-- > 0)
    {
        if (mkdir(*files, DIR_PERM))
        {
            fprintf(stderr, ERR_MSG, *files, strerror(errno));
            ret = 1;
        }
        files++;
    }
    return ret;
}


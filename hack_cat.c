#include "hackbox.h"
#include <stdio.h>
#define NO_FILE "No such file or directory"
#define NO_PERM "Permission denied"

int hack_cat(char **files, int n)
{
    FILE *fp;
    char ch;
    int ret_val = 0;
    while (n-- > 0)
    {
        if (access(*files, F_OK) == 0)
        {
            if (access(*files, R_OK) == 0)
            {
                fp = fopen(*files, "r");
                while ((ch = fgetc(fp)) != EOF)
                {
                    putchar(ch);
                }
                fclose(fp);
            }
            else
            {
                fprintf(stderr, "%s: %s\n", *files, NO_PERM);
                ret_val = 1;
            }
        }
        else
        {
            fprintf(stderr, "%s: %s\n", *files, NO_FILE);
            ret_val = 1;
        }
        files++;
    }
    return ret_val;
}

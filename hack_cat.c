#include "hackbox.h"
#include <stdio.h>
#define NO_FILE "cat: %s: No such file or directory\n"
#define NO_PERM "cat: %s: Permission denied\n"

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
                fprintf(stderr, NO_PERM, *files);
                ret_val = 1;
            }
        }
        else
        {
            fprintf(stderr, NO_FILE, *files);
            ret_val = 1;
        }
        files++;
    }
    return ret_val;
}

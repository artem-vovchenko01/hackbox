#include "hackbox_include.h"

#define ERR_ONE_OP "cp: missing destination file operand after '%s'\n"

int is_dir(char *dir);
int copy(char *src, char *dest);

int hack_cp(char **args, int n)
{
    if (n > 2)
    {
        char *dir = args[n - 1];
        n--;
        if (is_dir(dir))
        {
            while (n--)
            {
                copy(*args, strcat_all(3, dir, "/", *args));
                args++;
            }
        }
    }
    else if (n == 2)
    {
        char *src = *args;
        char *dest = *(++args);
        copy(src, dest);
    }
    else
    {
        fprintf(stderr, ERR_ONE_OP, *args);
    }
    return 0; 
}

int is_dir(char *dir)
{
    struct stat st;
    stat(dir, &st);
    return S_ISDIR(st.st_mode);
}

int copy(char *src, char *dest)
{
    FILE *fp_src = fopen(src, "r");
    FILE *fp_dest = fopen(dest, "w");
    char ch;
    while ((ch = fgetc(fp_src)) != EOF)
    {
        fputc(ch, fp_dest);
    }
    fclose(fp_src);
    fclose(fp_dest);
    return 0;
}

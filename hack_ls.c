#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>

#include "hackbox_include.h"
#include "hackbox.h"
#include "dirent.h"

#define ERR_MSG "ls: cannot open directory '%s': %s\n"
#define ERR_CODE 2

enum list_type
{
    t_short,
    t_long
};

int iterate_dir(char *dir, enum list_type l_type);

int hack_ls(char **dirs, int n)
{
    int ret = 0;
    enum list_type lst = t_short;
    if (n == 0)
    {
        return iterate_dir(".", lst);
    }

    int print_dir_name = 0;
    if (n > 1)
        print_dir_name = 1;

    while (n-- > 0)
    {
        if (print_dir_name)
            printf("%s:\n", *dirs);
        if (iterate_dir(*(dirs++), lst))
            ret = ERR_CODE;
        if (n > 0)
            printf("\n");
    }
    return ret;
}

int iterate_dir(char *dir, enum list_type l_type)
{
    char **files = NULL;
    DIR *d = opendir(dir);
    struct dirent *dir_entry;
    int count = 0;
    if (d)
    {
        while ((dir_entry = readdir(d)) != NULL)
        {
            files = realloc(files, (++count * sizeof(char *)));
            files[count - 1] = dir_entry -> d_name;
        }
    }
    else
    {
        fprintf(stderr, ERR_MSG, dir, strerror(errno));
        return ERR_CODE;
    }

    str_arr_sort(files, count);

    char *f_name = NULL;
    for (int i = 0; i < count; i++)
    {
        f_name = files[i]; 
        if (strcmp(f_name, ".") && strcmp(f_name, ".."))
        {
            printf("%s\n", f_name);
        }
    }
    return 0;
}

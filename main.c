#include "hackbox_include.h"
#include "hackbox.h"
#include <stdio.h>
#include <string.h>
#include "utils/hack_utils.h"
#define HELP "Avaialable commands: \n"          \
"hackbox mkdir <dirnames> \n"                   \
"hackbox ls [ -l ] [ <dirnames> ] \n"           \
"hackbox cp <src> [ <more_srcs> ] <dest> \n"    \
"hackbox cat <files> \n"                        \
"hackbox help \n"

int main(int argc, char **argv)
{
    char *f_name = *argv;
    if (str_ends_with(f_name, "hackbox") == 0)
    {
        if (argc == 1)
        {
            printf(HELP);
            return 1;
        }
        argv++;
        argc--;
    }
    char *bin_name = *argv;
    if (argc > 1)
        argv++;
    argc--;
    if (strcmp(bin_name, "ls") == 0)
    {
        return hack_ls(argv, argc);
    } 
    else if (strcmp(bin_name, "mkdir") == 0)
    {
        return hack_mkdir(argv, argc);
    }
    else if (strcmp(bin_name, "cat") == 0)
    {
        return hack_cat(argv, argc);
    }
    else if (strcmp(bin_name, "cp") == 0)
    {
        return hack_cp(argv, argc);
    }
    else if (strcmp(bin_name, "help") == 0)
    {
        printf(HELP);
    }
    return 0;
}

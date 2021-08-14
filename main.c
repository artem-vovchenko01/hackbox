#include "hackbox.h"
#include <stdio.h>
#include <string.h>
#include "utils/hack_utils.h"

int main(int argc, char **argv)
{
    char *f_name = *argv;
    if (str_ends_with(f_name, "hackbox") == 0)
    {
        if (argc == 1)
        {
            // show help
            return 0;
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
        printf("ls\n");
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
        printf("cp\n");
    }
    else if (strcmp(bin_name, "help") == 0)
    {
        printf("help\n");
    }
    return 0;
}

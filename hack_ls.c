#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#include "hackbox_include.h"
#include "hackbox.h"
#include "dirent.h"

#define ERR_MSG "ls: cannot open directory '%s': %s\n"
#define ERR_CODE 2

void print_long_info(char *dir, char *file);

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
    if (!strcmp(*dirs, "-l"))
    {
        lst = t_long;
        dirs++;
        n--;
    }
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
            if (l_type == t_long)
            {
                print_long_info(dir, f_name);
            }
            printf("%s\n", f_name);
        }
    }
    return 0;
}

void print_long_info(char *dir, char *file)
{
    struct stat f_stat;
    char *path = strcat_all(3, dir, "/", file);
    stat(path, &f_stat);
    printf((S_ISREG(f_stat.st_mode)) ? "-" : "d");

    printf((f_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((f_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((f_stat.st_mode & S_IXUSR) ? "x" : "-");

    printf((f_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((f_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((f_stat.st_mode & S_IXGRP) ? "x" : "-");

    printf((f_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((f_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((f_stat.st_mode & S_IXOTH) ? "x" : "-");

    printf("%3d", f_stat.st_nlink);
    struct passwd *pwd = getpwuid(f_stat.st_uid);
    printf(" %s ", pwd -> pw_name);

    struct group *grp = getgrgid(f_stat.st_gid);
    printf(" %s ", grp -> gr_name);
    printf("%8d", f_stat.st_size);
    char *time = ctime(&f_stat.st_mtime);
    time[strlen(time) - 1] = '\0';
    printf(" %s ", time);
}



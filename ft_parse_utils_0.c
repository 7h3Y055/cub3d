#include "cub3d.h"


void    check_extention(t_ptr *ptr, char const **argv)
{
    if ((!ft_strchr(argv[1], '.') || ft_strrchr(argv[1], '.') == argv[1])\
     || ft_strcmp(ft_strrchr(argv[1], '.'), ".cub") != 0)
        exit(ft_error(ptr, "file name is not .cub extention!\n", 1));
}

int    ft_open(t_ptr *ptr, char const *path)
{
    int fd;

    fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        ft_error(ptr, "", 0);
        perror(path);
        exit(1);
    }
    return (fd);
}

char *get_texture_path(t_ptr *ptr, char *str)
{
    int i;
    int tmp_i;
    char *path;

    i = 0;
    while (ft_isspace(str[i]))
        i++;
    i += 2;
    while (ft_isspace(str[i]))
        i++;
    tmp_i = i;
    while (!ft_isspace(str[i]))
        i++;
    while (ft_isspace(str[i]))
        i++;
    if (str[i])
        exit(ft_error(ptr, "Error1\n", 1));
    path = ft_strndup(&str[tmp_i], i - tmp_i - 1);
    return (path);
}


int skip_comma(char *str, int i)
{
    while (ft_isspace(str[i]))
        i++;
    if (str[i] == ',')
        i++;
    while (ft_isspace(str[i]))
        i++;
    return (i);
}

int skip_digit(t_ptr *ptr, char *str, int i)
{
    while (ft_isspace(str[i]))
        i++;
    if (ft_isdigit(str[i]))
    {
        while (ft_isdigit(str[i]))
            i++;
    }
    else
        exit(ft_error(ptr, "Error3\n", 1));
    while (ft_isspace(str[i]))
        i++;
    return (i);
}
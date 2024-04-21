#include "cub3d.h"

void    check_extention(char const **argv)
{
    if ((!ft_strchr(argv[1], '.') || ft_strrchr(argv[1], '.') == argv[1])\
     || ft_strcmp(ft_strrchr(argv[1], '.'), ".cub") != 0)
        exit(ft_error("file name is not .cub extention!\n", 1));
}

int    ft_open(char const *path)
{
    int fd;

    fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        ft_error("", 0);
        perror(path);
        exit(1);
    }
    return (fd);
}

char *get_texture_path(char *str)
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
    {
        ft_error("Error\n", 1);
        return (NULL);
    }
    path = ft_strndup(&str[tmp_i], i - tmp_i);
    return (path);
}

int    ft_init_texture(t_ptr *ptr, char *str)
{
    int i;

    i = 0;
    while (ft_isspace(str[i]))
        i++;
    if (!ptr->parse.no && ft_strncmp(&str[i], "NO", 2) == 0)
        ptr->parse.no = get_texture_path(str);
    else if (!ptr->parse.so && ft_strncmp(&str[i], "SO", 2) == 0)
        ptr->parse.so = get_texture_path(str);
    else if (!ptr->parse.we && ft_strncmp(&str[i], "WE", 2) == 0)
        ptr->parse.we = get_texture_path(str);
    else if (!ptr->parse.ee && ft_strncmp(&str[i], "EA", 2) == 0)
        ptr->parse.ee = get_texture_path(str);
    else if (!str[i])
        return (0);
    else
        exit(ft_error("Error\n", 1));
    return (1);
}

// int check_valide_color_2(char *str)
// {
//     int i;

//     i = 0;
//     printf("%s", str);
//     return 0;
// }

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

int skip_digit(char *str, int i)
{
    while (ft_isspace(str[i]))
        i++;
    if (ft_isdigit(str[i]))
    {
        while (ft_isdigit(str[i]))
            i++;
    }
    else
        exit(ft_error("Error3\n", 1));
    while (ft_isspace(str[i]))
        i++;
    return (i);
}

int check_valide_color(char *str)
{
    int i;

    i = 0;
    i = skip_digit(str, i);
    i = skip_comma(str, i);
    i = skip_digit(str, i);
    i = skip_comma(str, i);
    i = skip_digit(str, i);
    if (str[i])
        return (1);
    return (0);
}

int *get_color(char *str)
{
    int i;
    char *tmp;
    int *color;

    color = malloc(sizeof(int) * 3);
    i = 0;
    while (ft_isspace(str[i]))
        i++;
    i += 1;
    while (ft_isspace(str[i]))
        i++;
    if (check_valide_color(&str[i]))
        exit(ft_error("Error4\n", 1));
    tmp = ft_strrchr(str, ',');
    tmp[ft_strlen(tmp) - 1] = 0;




    color[2] = ft_atoi(&tmp[1]);
    *tmp = 0;
    tmp = ft_strrchr(str, ',');
    color[1] = ft_atoi(&tmp[1]);
    *tmp = 0;
    color[0] = ft_atoi(&str[i]);
    if (color[0] > 255 || color[1] > 255 || color[2] > 255)
    {
        free(color);
        exit(ft_error("Error5\n", 1));
    }
    return (color);
}

int ft_init_floor_ceiling(t_ptr *ptr, char *str)
{
    int i;

    i = 0;
    while (ft_isspace(str[i]))
        i++;
    if (!ptr->parse.floor && ft_strncmp(&str[i], "F", 1) == 0)
        ptr->parse.floor = get_color(str);
    else if (!ptr->parse.ceiling && ft_strncmp(&str[i], "C", 1) == 0)
        ptr->parse.ceiling = get_color(str);
    else if (!str[i])
        return (0);
    else
        exit(ft_error("Error\n", 1));
    return (1);
}

void    ft_init_map2d(t_ptr *ptr, char *str)
{
    printf("%s", str);
}

void    ft_init(t_ptr *ptr, int fd)
{
    char *line;
    int n;

    n = 0;
    while (n != 4)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        n += ft_init_texture(ptr, line);
    }
    n = 0;
    while (n != 2)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        n += ft_init_floor_ceiling(ptr, line);
    }
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        ft_init_map2d(ptr, line);
    }
}

void ft_parse(t_ptr *ptr, int argc, char const **argv)
{
    int fd;

    if (argc != 2)
        exit(ft_error("need one parameter have path of map\n", 1));
    check_extention(argv);
    fd = ft_open(argv[1]);
    ft_init(ptr, fd);
}

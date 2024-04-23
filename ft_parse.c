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

int check_valide_color(t_ptr *ptr, char *str)
{
    int i;

    i = 0;
    i = skip_digit(ptr, str, i);
    i = skip_comma(str, i);
    i = skip_digit(ptr, str, i);
    i = skip_comma(str, i);
    i = skip_digit(ptr, str, i);
    if (str[i])
        return (1);
    return (0);
}

int *get_color(t_ptr *ptr, char *str)
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
    if (check_valide_color(ptr, &str[i]))
        exit(ft_error(ptr, "Error4\n", 1));
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
        exit(ft_error(ptr, "Error5\n", 1));
    }
    return (color);
}
int ft_just_whitespaces(char *str, int i)
{
    while (str[i] && ft_isspace(str[i]))
        i++;
    if (!str[i])
        return (1);
    return (0);
}
int    ft_init_texture(t_ptr *ptr, char *str)
{
    int i;

    i = 0;
    while (ft_isspace(str[i]))
        i++;
    if (!ptr->parse.no && ft_strncmp(&str[i], "NO", 2) == 0)
        ptr->parse.no = get_texture_path(ptr, str);
    else if (!ptr->parse.so && ft_strncmp(&str[i], "SO", 2) == 0)
        ptr->parse.so = get_texture_path(ptr, str);
    else if (!ptr->parse.we && ft_strncmp(&str[i], "WE", 2) == 0)
        ptr->parse.we = get_texture_path(ptr, str);
    else if (!ptr->parse.ea && ft_strncmp(&str[i], "EA", 2) == 0)
        ptr->parse.ea = get_texture_path(ptr, str);
    else if (!ptr->parse.floor && ft_strncmp(&str[i], "F", 1) == 0)
        ptr->parse.floor = get_color(ptr, str);
    else if (!ptr->parse.ceiling && ft_strncmp(&str[i], "C", 1) == 0)
        ptr->parse.ceiling = get_color(ptr, str);
    else if (ft_just_whitespaces(str, i))
        return (0);
    else if (str[i] && str[i] != '\n')
    {
        printf("[%s]\n", &str[i]);
        exit(ft_error(ptr, "Error2\n", 1));
    }
    return (1);
}

char    **allocate_memory_for_map2d(t_ptr *ptr, int y, int x)
{
    int i;
    char **map2d;

    i = 0;
    map2d = ft_calloc(sizeof(char *), (y + 1));
    if (!map2d)
        exit(ft_error(ptr, "malloc error\n", 1));
    while (i < y)
    {
        map2d[i] = ft_calloc(sizeof(char) , (x + 1));
        if (!map2d[i])
            exit(ft_error(ptr, "malloc error\n", 1));
        i++;
    }
    return (map2d);
}


void    ft_init_map2d(t_ptr *ptr, char *str)
{
    int i;
    int y;
    int x;

    i = 0;
    y = 0;
    x = 0;
    ptr->parse.map2d = allocate_memory_for_map2d(ptr, ptr->parse.y, ptr->parse.x);
    while (str[i] && !ft_just_whitespaces(str, i))
    {
        if (str[i] == '\n')
        {
            x = 0;
            y++;
        }
        else
            ptr->parse.map2d[y][x++] = str[i];
        i++;
    }
    if (i > 1 && str[i - 1] == '\n')
        ptr->parse.map2d[y] = NULL;
    ptr->parse.map2d[y + 1] = NULL;
}

char    *ft_read_map(t_ptr *ptr, int fd)
{
    char *buffer;
    char *line;
    char *tmp;

    ptr->parse.y = 0;
    ptr->parse.x = 0;
    buffer = ft_calloc(1, 1);
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        if (!ft_just_whitespaces(line, 0))
        {
            if (ptr->parse.x < (int)ft_strlen(line))
                ptr->parse.x = (int)ft_strlen(line);
            tmp = ft_strjoin(buffer, line);
            free(buffer);
            buffer = tmp;
            free(line);
            ptr->parse.y++;
        }
    }
    return (buffer);
}

void    ft_init(t_ptr *ptr, int fd)
{
    char *line;
    int  n;

    n = 0;
    while (n < 6)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        n += ft_init_texture(ptr, line);
        free(line);
    }
    line = ft_read_map(ptr, fd);
    ft_init_map2d(ptr, line);
}

int check_valid_map(t_ptr *ptr, int y, int x)
{
   if (!ptr->parse.map2d[y + 1] || (ptr->parse.map2d[y + 1][x] == '\0' || ptr->parse.map2d[y + 1][x] == ' '))
        return (1);
   else if (!ptr->parse.map2d[y - 1] || (ptr->parse.map2d[y - 1][x] == '\0' || ptr->parse.map2d[y - 1][x] == ' '))
        return (2);
   else if (ptr->parse.map2d[y][x + 1] == '\0' || ptr->parse.map2d[y][x + 1] == ' ')
        return (3);
   else if (ptr->parse.map2d[y][x - 1] == '\0' || ptr->parse.map2d[y][x - 1] == ' ')
        return (4);
    return (0);
}

void    check_valide_map(t_ptr *ptr)
{
    int y;
    int x;
    int n;

    y = 0;
    n = 0;
    while (y < ptr->parse.y)
    {
        x = 0;
        while (x < ptr->parse.x)
        {
            if (ptr->parse.map2d[y][x] == '0' && check_valid_map(ptr, y, x))
                exit(ft_error(ptr, "Invalid map: map is not closed by wall (1)\n", check_valid_map(ptr, y, x)));
            else if (ptr->parse.map2d[y][x] == 'N')
                n++;
            else if (ptr->parse.map2d[y][x] && ptr->parse.map2d[y][x] != '0' && ptr->parse.map2d[y][x] != '1' && ptr->parse.map2d[y][x] != ' ')
                exit(ft_error(ptr, "Invalid map: contain invalid character!\n", check_valid_map(ptr, y, x)));
            x++;
        }
        y++;
    }
    if (n == 0 || n > 1)
        exit(ft_error(ptr, "Invalid map: less or more than one player starting point (N)\n", 1));
}

void ft_parse(t_ptr *ptr, int argc, char const **argv)
{
    int fd;

    ft_bzero(ptr, sizeof(t_ptr));
    if (argc != 2)
        exit(ft_error(ptr, "need one parameter have path of map\n", 1));
    check_extention(ptr, argv);
    fd = ft_open(ptr, argv[1]);
    ft_init(ptr, fd);
    check_valide_map(ptr);
}

#include "cub3d.h"


void    ft_init_player_position(t_ptr *ptr, int y, int x,  char c)
{
    ptr->player.y = y * SCALE + SCALE / 2;
    ptr->player.x = x * SCALE + SCALE / 2;


    if (c == 'N')
        ptr->player.angle = PI + PI / 2;
    else if (c == 'S')
        ptr->player.angle = PI / 2;
    else if (c == 'E')
        ptr->player.angle = 0;
    else if (c == 'W')
        ptr->player.angle = PI;
}

void    ft_init_map2d(t_ptr *ptr, char *str)
{
    int i;
    int y;
    int x;
    int n;

    n = 0;
    i = 0;
    y = 0;
    x = 0;
    ptr->map2d = allocate_memory_for_map2d(ptr, ptr->parse.y + 2, ptr->parse.x + 1);
    while (ptr->map2d[y])
    {
        if (!str[i] || str[i] == '\n')
        {
            while (x < ptr->parse.x - 1)
                ptr->map2d[y][x++] = ' ';
            x = 0;
            y++;
            if (!str[i])
                break;
        }
        else if (str[i] != 'N' && str[i] != 'S' && str[i] != 'W' && str[i] != 'E')
            ptr->map2d[y][x++] = str[i];
        else
        {
            n++;
            ft_init_player_position(ptr, y, x, str[i]);
            ptr->map2d[y][x++] = '0';
        }
        i++;
    }
    if (n == 0 || n > 1)
        exit(ft_error(ptr, "Invalid map: less or more than one player starting point (N or E or S or W)\n", 1));
    y = 0;
    ptr->map2d[ptr->parse.y] = NULL;
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
            if (ptr->parse.x < (int)ft_strlen(line) - 1)
                ptr->parse.x = (int)ft_strlen(line) - 1;
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
    while (n < 7)
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

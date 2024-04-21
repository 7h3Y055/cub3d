#include "cub3d.h"

int ft_error(char *str, int n)
{
    ft_putstr_fd("[cub3d]: ", 2);
    ft_putstr_fd(str, 2);
    return n;
}
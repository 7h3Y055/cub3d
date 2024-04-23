#include "cub3d.h"

int ft_error(t_ptr *ptr,char *str, int n)
{
    (void)ptr;//free all memory allocation
    ft_putstr_fd("[cub3d]: ", 2);
    ft_putstr_fd(str, 2);
    return n;
}
#ifndef CUB3D_H
#define CUB3D_H

#include <mlx.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include "get_next_line.h"


#define SCALE 100


typedef struct s_parse
{
    char *no;
    char *so;
    char *we;
    char *ea;

    int *floor;
    int *ceiling;

    int x;
    int y;
    char **map2d;
} t_parse;

typedef struct s_win
{
    void *mlx;
    void *win;
} t_win;


typedef struct s_ptr
{
    t_parse parse;
    t_win   win;

    char **map2d;
} t_ptr;


void ft_parse(t_ptr *ptr, int argc, char const **argv);
int ft_error(t_ptr *ptr, char *str, int n);
void    test(t_ptr *ptr);
char    **allocate_memory_for_map2d(t_ptr *ptr, int y, int x);

#endif
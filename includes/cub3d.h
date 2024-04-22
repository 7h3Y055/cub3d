#ifndef CUB3D_H
#define CUB3D_H

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include "get_next_line.h"



typedef struct s_parse
{
    char *no;
    char *so;
    char *we;
    char *ee;

    int *floor;
    int *ceiling;

    int x;
    int y;
} t_parse;


typedef struct s_ptr
{
    t_parse parse;
    char **map2d;

} t_ptr;


void ft_parse(t_ptr *ptr, int argc, char const **argv);
int ft_error(char *str, int n);

#endif
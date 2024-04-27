#ifndef CUB3D_H
#define CUB3D_H

#include <mlx.h>
#include <math.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include "get_next_line.h"


#define	HEIGHT 1080
#define	WIDTH 720


#define RAD 6.2831853072
#define NINETY_DEGREE 1.5707963268
#define SCALE 50
#define SCALE_P 10
#define PLAYER_SPEED 7 // > 1
#define ROTATION_SPEED 0.050

#define EYE_ANGLE 0.523599

#define W_M       13
#define D_M       2
#define S_M       1
#define A_M       0

#define RIGHT_M   124
#define LEFT_M    123
#define ESC_M    53

#define W 0
#define D 1
#define S 2
#define A 3
#define L 4
#define R 5
#define E 6


typedef struct s_point
{
	long long	x;
	long long	y;
}	t_point;

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
} t_parse;

typedef struct	s_img_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img_data;

typedef struct s_win
{
    void 		*mlx;
    void 		*win;
	t_img_data	img;
} t_win;

typedef struct s_player
{
    size_t y;
    size_t x;

    double angle;
} t_player;


typedef struct s_ptr
{
    t_parse parse;
    t_win   win;
    t_player player;
    int     keys[7];
    char **map2d;
    char **map2d_scaled;
} t_ptr;


void ft_parse(t_ptr *ptr, int argc, char const **argv);
int ft_error(t_ptr *ptr, char *str, int n);
void    create_scaled_map(t_ptr *ptr);
char    **allocate_memory_for_map2d(t_ptr *ptr, int y, int x);


void go_up(t_ptr *ptr);
void go_left(t_ptr *ptr);
void go_down(t_ptr *ptr);
void go_right(t_ptr *ptr);
void right_angle(t_ptr *ptr);
void left_argle(t_ptr *ptr);



void	create_map(t_img_data *img, char **map);
void	put_player_to_image(t_img_data *img, t_player player);
void	init_mlx(t_ptr *ptr);
void	render_map(t_ptr ptr);
void	put_arrow(t_ptr *ptr);


int key_pressed(int keycode, t_ptr *ptr);
int key_released(int keycode, t_ptr *ptr);

#endif

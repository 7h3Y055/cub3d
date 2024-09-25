/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:11:53 by ybouchma          #+#    #+#             */
/*   Updated: 2024/05/19 10:10:32 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include "libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define HEIGHT 1280
# define WIDTH 720

# define RED 0xFF0000
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define DOOR_H 0xFFF000
# define DOOR_W 0x0F00FF
# define GREEN 0x36FF00
# define GRAY 0x808080
# define BLEU 0x0021FF

# define DEBUG 0
# define DEBUG_SCALE 10
# define SCALE_P 2

# define MAP_H 320
# define MAP_W 180

# define ENEMY_SPACE 15
# define PLAYER_SPACE 3

# define RAD 6.2831853072
# define NINETY_DEGREE 1.5707963268
# define PI 3.141592653589793
# define SCALE 100
# define ENEMY_SPEED 4
# define PLAYER_SPEED 10
# define ROTATION_SPEED 0.05
# define EYE_ANGLE 60
# define MAGIC_NUMBER 0.00001

# define W_M 13
# define D_M 2
# define S_M 1
# define A_M 0
# define P_M 35
# define F_M 3

# define RIGHT_M 124
# define LEFT_M 123
# define UP_M 126
# define DOWN_M 125
# define ESC_M 53
# define ESP_M 49

# define W 0
# define D 1
# define S 2
# define A 3
# define L 4
# define R 5
# define E 6
# define O 7
# define ES 8

typedef struct s_point
{
	double		x;
	double		y;
	int			face;
	size_t		first_point_in_wall;
	double		ray_l;
}				t_point;

typedef struct s_rays
{
	t_point		next;
	double		n;
}				t_rays;

typedef struct s_parse
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			*floor;
	int			*ceiling;
	int			x;
	int			y;
}				t_parse;

typedef struct s_img_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img_data;

typedef struct s_win
{
	void		*mlx;
	void		*win;
	t_img_data	img;
}				t_win;

typedef struct s_obunga
{
	double		x;
	double		y;
	int			img_w;
	int			img_h;
	size_t		img_x;
	char		*path;
	t_img_data	img;
	size_t		dst;
	double		angle;
}				t_obunga;

typedef struct s_player
{
	size_t		y;
	size_t		x;
	double		angle;
}				t_player;

typedef struct s_texture
{
	int			no_w;
	int			no_h;
	t_img_data	no_img;
	int			so_w;
	int			so_h;
	t_img_data	so_img;
	int			we_w;
	int			we_h;
	t_img_data	we_img;
	int			ea_w;
	int			ea_h;
	t_img_data	ea_img;
	int			d_w;
	int			d_h;
	t_img_data	d_img;
}				t_texture;

typedef struct s_flags
{
	t_point		tmp;
	int			n_p;
	int			dst;
	size_t		y;
	int			consts;
	int			img;
	t_point		a;
	t_point		next;
}				t_flags;

typedef struct s_jumps
{
	int			jump_stats;
	int			jump_hight;
	int			jump_speedup;
	int			jump_speeddown;
	int			consts;
}				t_jumps;

typedef struct s_ptr
{
	t_rays		*rays;
	t_parse		parse;
	t_win		win;
	t_player	player;
	t_obunga	obunga;
	int			keys[11];
	char		*line;
	t_jumps		jumps;
	int			updown;
	t_texture	texture;
	char		**map2d;
	int			start;
	int			map_scale;
	t_flags		flgas;
}				t_ptr;

void			ft_parse(t_ptr *ptr, int argc, char const **argv);
int				ft_error(t_ptr *ptr, char *str, int n);
char			**allocate_memory_for_map2d(t_ptr *ptr, int y, int x);
void			go_up(t_ptr *ptr);
void			go_left(t_ptr *ptr);
void			go_down(t_ptr *ptr);
void			go_right(t_ptr *ptr);
void			right_angle(t_ptr *ptr);
void			left_argle(t_ptr *ptr);
double			distance(t_ptr ptr, t_point next, int flag);
void			put_rays(t_ptr *ptr);
void			put_obunga_to_img(t_ptr *ptr);
void			init_mlx(t_ptr *ptr);
void			ft_init(t_ptr *ptr, int fd);
int				ft_open(t_ptr *ptr, char const *path);
void			check_extention(t_ptr *ptr, char const **argv);
char			*get_texture_path(t_ptr *ptr, char *str);
void			free_all(t_ptr *ptr);
char			*get_image_color(t_ptr *ptr, t_point next, int img_x,
					int img_y);
void			init_obunga_angle(t_ptr *ptr);
int				skip_comma(char *str, int i);
int				skip_digit(t_ptr *ptr, char *str, int i, int *color);
int				ft_just_whitespaces(char *str, int i);
int				ft_init_texture(t_ptr *ptr, char *str);
void			init_param_y_up(t_ptr *ptr, t_point *next, t_point *a,
					double angle);
void			init_param_y_down(t_ptr *ptr, t_point *next, t_point *a,
					double angle);
void			init_param_x_right(t_ptr *ptr, t_point *next, t_point *a,
					double angle);
void			init_param_x_left(t_ptr *ptr, t_point *next, t_point *a,
					double angle);
int				btw_range(double a, double min, double max);
double			d2rad(double d);
t_point			init_obunga(t_ptr *ptr, t_point *next, double p_angle, int c);
int				check_wall(t_ptr *ptr, t_point point);
void			init_param_x(t_ptr *ptr, t_point *next, t_point *a,
					double angle);
void			init_param_y(t_ptr *ptr, t_point *next, t_point *a,
					double angle);
double			calculate_incrementation(void);
void			valid_color(t_ptr *ptr, int *color);
int				get_pixel_color(t_ptr *ptr, t_point next, size_t y);
void			check_player_move(t_ptr *ptr, long long y, long long x);
int				color_unit_pixel(char map_unit);
void			jump_init(t_ptr *ptr);
int				destroy_all(t_ptr *ptr);
void			render_map(t_ptr ptr);
void			raycasting(t_ptr *ptr);
void			put_minimap(t_ptr *ptr);
void			my_mlx_pixel_put(t_img_data *img, int x, int y, int color);
void			create_square(t_ptr *ptr, double ray_l, size_t x, t_point next);
void			midle_line(t_ptr *ptr);
double			fix_rad_overflow(double a);
int				key_pressed(int keycode, t_ptr *ptr);
int				key_released(int keycode, t_ptr *ptr);
size_t			scalebetween(size_t unscaledNum, size_t maxAllowed, size_t min,
					size_t max);
void			obunga_move(t_ptr *ptr);
void			check_player_death(t_ptr *ptr);
int				handle_input(t_ptr *ptr);
int				check_wall_obunga(t_ptr *ptr, size_t n);
void			jump(t_ptr *ptr);
int				get_obunga_color(t_ptr *ptr, size_t y, size_t x);
int				rgb2int(int r, int g, int b);

#endif

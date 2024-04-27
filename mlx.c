#include "cub3d.h"

void	my_mlx_pixel_put(t_img_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	put_arrow(t_ptr *ptr)
{
	t_point	next_point;
	int i;
	double	a = ptr->player.angle - EYE_ANGLE;

	next_point.y = sin(ptr->player.angle) * PLAYER_SPEED + ptr->player.y;
    next_point.x = cos(ptr->player.angle) * PLAYER_SPEED + ptr->player.x;
	while (a <= ptr->player.angle + EYE_ANGLE)
	{
		i = 1;
		while (1)
		{
			next_point.y = sin(a) * i + ptr->player.y;
			next_point.x = cos(a) * i + ptr->player.x;
			if (ptr->map2d_scaled[next_point.y][next_point.x] != '0')
				break ;
			my_mlx_pixel_put(&ptr->win.img, next_point.x, next_point.y, 0);
			i++;
		}
		a += 0.0005;
	}
}

int	color_unit_pixel(char map_unit)
{
	if (map_unit == '1')
		return (0x002177);
	else if (map_unit == '0')
		return (0xffffff);
	else
		return (0);
}

void	create_map(t_img_data *img, char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			my_mlx_pixel_put(img, x, y, color_unit_pixel(map[y][x]));
			x++;
		}
		y++;
	}
}

void	put_player_to_image(t_img_data *img, t_player player)
{
	size_t x;
	size_t y;
	size_t x_max;
	size_t y_max;

	y = player.y - SCALE_P;
	x_max = player.x + SCALE_P;
	y_max = player.y + SCALE_P;
	while (y <= y_max)
	{
		x = player.x - SCALE_P;
		while (x <= x_max)
		{
			my_mlx_pixel_put(img, x, y, 0xFE2D00);
			x++;
		}
		y++;
	}
}

void	init_mlx(t_ptr *ptr)
{
	ptr->win.mlx = mlx_init();
	ptr->win.win = mlx_new_window(ptr->win.mlx, ptr->parse.x * SCALE, ptr->parse.y * SCALE, "Cub3D");
}

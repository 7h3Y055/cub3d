#include "cub3d.h"

void	my_mlx_pixel_put(t_img_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

double d2rad(double d)
{
	return (d * PI/180);
}

void	put_arrow(t_ptr *ptr)
{
	double angle = ptr->player.angle;

	
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

void	create_map(t_ptr *ptr)
{
	int	x;
	int	y;

	y = 0;
	while (y < ptr->parse.y * SCALE)
	{
		x = 0;
		while (x < ptr->parse.x * SCALE)
		{
			if (x % SCALE != 0 && y % SCALE != 0)
				my_mlx_pixel_put(&ptr->win.img, x, y, color_unit_pixel(ptr->map2d[y / SCALE][x / SCALE]));
			else
				my_mlx_pixel_put(&ptr->win.img, x, y, GRAY);
			x++;
		}
		y++;
	}
}

void	put_player_to_image(t_img_data *img, t_player player)
{
	size_t x;
	size_t y;
	size_t n;
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
	n = 1;
	while (n < 20)
	{
		my_mlx_pixel_put(img, player.x + (cos(player.angle) * n), player.y + (sin(player.angle) * n), 0xFE2D00);
		n++;
	}
}

void	init_mlx(t_ptr *ptr)
{
	ptr->win.mlx = mlx_init();

	ptr->win.win = mlx_new_window(ptr->win.mlx, ptr->parse.x * SCALE, ptr->parse.y * SCALE, "Cub3D map2d");

	ptr->win.img.img = mlx_new_image(ptr->win.mlx, ptr->parse.x * SCALE, ptr->parse.y * SCALE);

	ptr->win.img.addr = mlx_get_data_addr(ptr->win.img.img, &ptr->win.img.bits_per_pixel, &ptr->win.img.line_length,
				&ptr->win.img.endian);

}

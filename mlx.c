#include "cub3d.h"

void	my_mlx_pixel_put(t_img_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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

void	render_map(t_ptr ptr)
{
	t_img_data	img;

	img.img = mlx_new_image(ptr.win.mlx, ptr.parse.x * SCALE, ptr.parse.y * SCALE);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
				&img.endian);
	create_map(&img, ptr.map2d_scaled);
	put_player_to_image(&img, ptr.player);
	mlx_clear_window(ptr.win.mlx, ptr.win.win);
	mlx_put_image_to_window(ptr.win.mlx, ptr.win.win, img.img, 0, 0);
}
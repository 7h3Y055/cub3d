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

int	exeed_map(t_ptr *ptr, t_point p)
{
	if (p.x >= ptr->parse.x * SCALE || p.y >= ptr->parse.y * SCALE
		|| p.x < 0 || p.y < 0)
		{
			puts("w9f");	
		return (1);
		}
	return (0);
}

long long	distance(t_player p, t_point next)
{
	return (sqrt((p.x - next.x) * (p.x - next.x) + (p.y - next.y) * (p.y - next.y)));
}

void x(t_ptr *ptr, t_point *next, double angle)
{
	long long i = 1;
	long long d = distance(ptr->player, *next);
	t_point a;

	i = 1;
	while (i < d && !exeed_map(ptr, *next))
	{
		next->x = ptr->player.x + (cos(ptr->player.angle) * i);
		next->y = ptr->player.y + (sin(ptr->player.angle) * i);
		my_mlx_pixel_put(&ptr->win.img, next->x, next->y, GREAN);
		i++;
	}




	my_mlx_pixel_put(&ptr->win.img, next->x, next->y, RED);
	my_mlx_pixel_put(&ptr->win.img, next->x, next->y + 1, RED);
	my_mlx_pixel_put(&ptr->win.img, next->x, next->y - 1 , RED);
	my_mlx_pixel_put(&ptr->win.img, next->x - 1, next->y, RED);
	my_mlx_pixel_put(&ptr->win.img, next->x + 1, next->y, RED);
}

void	init_param_y(t_ptr *ptr, t_player player, t_point *next, t_point *a)
{
	if (player.angle > PI && player.angle < RAD)
	{
		if (player.angle > PI + PI / 2)//puts("up rigth");
		{
			next->y = player.y / SCALE * SCALE - 1;
			next->x = player.x + (player.y - next->y) / tan(RAD - player.angle);
			a->y = -SCALE;
			a->x = SCALE / tan(RAD - player.angle);
		}
		else if (player.angle < PI + PI / 2)//puts("up left");
		{
			next->y = player.y / SCALE * SCALE - 1;
			next->x = player.x + (player.y - next->y) / tan(RAD - player.angle);
			a->y = -SCALE;
			a->x = a->y / tan(player.angle - PI);
		}
		else // up
		{
			next->y = next->y = player.y / SCALE * SCALE - 1;; 
			next->x = player.x; 
			a->y = -SCALE;
			a->x = 0;
		}
	}
	else if (player.angle < PI && player.angle > 0)//puts("down");
	{
		if (player.angle < PI / 2)//puts("down rigth");
		{
			next->y = player.y / SCALE * SCALE + SCALE;
			next->x = player.x + (next->y - player.y) / tan(player.angle);
			a->y = SCALE;
			a->x = a->y / tan(player.angle);
		}
		else if (player.angle > PI / 2)//puts("down left");
		{
			next->y = player.y / SCALE * SCALE + SCALE;
			next->x = player.x + (next->y - player.y) / tan(player.angle);
			a->y = SCALE;
			a->x = -a->y / tan(PI - player.angle);
		}
		else //puts("down");
		{
			next->y = next->y = player.y / SCALE * SCALE + SCALE;
			next->x = player.x; 
			a->y = SCALE;
			a->x = 0;
		}
	}
}

void	put_arrow(t_ptr *ptr)
{
	t_player player = ptr->player;
	t_point	next;
	t_point	a;

	init_param_y(ptr, player, &next, &a);
	while (!exeed_map(ptr, next))
	{
		if (ptr->map2d[next.y / SCALE][next.x / SCALE] != '0')
			break ;
		next.x += a.x;
		next.y += a.y;
	}
	x(ptr, &next, player.angle);
	puts("walo");
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

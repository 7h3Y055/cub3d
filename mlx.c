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
			// puts("w9f");	
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

	if (!exeed_map(ptr, *next))
	{
		my_mlx_pixel_put(&ptr->win.img, next->x, next->y, RED);
		// my_mlx_pixel_put(&ptr->win.img, next->x, next->y + 1, RED);
		// my_mlx_pixel_put(&ptr->win.img, next->x, next->y - 1 , RED);
		// my_mlx_pixel_put(&ptr->win.img, next->x - 1, next->y, RED);
		// my_mlx_pixel_put(&ptr->win.img, next->x + 1, next->y, RED);
	}
	// i = 1;
	// while (i < d && !exeed_map(ptr, *next))
	// {
	// 	next->x = ptr->player.x + (cos(angle) * i);
	// 	next->y = ptr->player.y + (sin(angle) * i);
	// 	my_mlx_pixel_put(&ptr->win.img, next->x, next->y, GREAN);
	// 	i++;
	// }



}

void	init_param_y(t_ptr *ptr, t_point *next, t_point *a, double angle)
{
	if (angle > PI && angle < RAD)
	{
		if (angle > PI + PI / 2)//puts("up rigth");
		{
			next->y = ptr->player.y / SCALE * SCALE - 1;
			next->x = ptr->player.x + (ptr->player.y - next->y) / tan(RAD - angle);
			a->y = -SCALE;
			a->x = SCALE / tan(RAD - angle);
		}
		else if (angle < PI + PI / 2)//puts("up left");
		{
			next->y = ptr->player.y / SCALE * SCALE - 1;
			next->x = ptr->player.x + (ptr->player.y - next->y) / tan(RAD - angle);
			a->y = -SCALE;
			a->x = a->y / tan(angle - PI);
		}
		else // up
		{
			next->y = next->y = ptr->player.y / SCALE * SCALE - 1;; 
			next->x = ptr->player.x; 
			a->y = -SCALE;
			a->x = 0;
		}
	}
	else if (angle < PI && angle > 0)//puts("down");
	{
		if (angle < PI / 2)//puts("down rigth");
		{
			next->y = ptr->player.y / SCALE * SCALE + SCALE;
			next->x = ptr->player.x + (next->y - ptr->player.y) / tan(angle);
			a->y = SCALE;
			a->x = a->y / tan(angle);
		}
		else if (angle > PI / 2)//puts("down left");
		{
			next->y = ptr->player.y / SCALE * SCALE + SCALE;
			next->x = ptr->player.x + (next->y - ptr->player.y) / tan(angle);
			a->y = SCALE;
			a->x = -a->y / tan(PI - angle);
		}
		else //puts("down");
		{
			next->y = next->y = ptr->player.y / SCALE * SCALE + SCALE;
			next->x = ptr->player.x; 
			a->y = SCALE;
			a->x = 0;
		}
	}
	else//<----- ----->
	{
		//to do
		next->x = ptr->parse.x * SCALE;
		next->y = ptr->parse.y * SCALE;
		a->x = ptr->parse.x * SCALE;
		a->y = ptr->parse.y * SCALE;
	}
}

void	init_param_x(t_ptr *ptr, t_point *next, t_point *a, double angle)
{
	if (angle > PI + PI / 2) //puts("RIGHT UP");
	{
		next->x = ptr->player.x / SCALE * SCALE + SCALE;
		next->y = ptr->player.y - (next->x - ptr->player.x) * tan(RAD - angle);
		a->x = SCALE;
		a->y = -SCALE * tan(RAD - angle);
	}
	else if (angle < PI / 2) //puts("RIGHT DOWN");
	{
		next->x = ptr->player.x / SCALE * SCALE + SCALE;
		next->y = ptr->player.y + (next->x - ptr->player.x) * tan(angle);
		a->x = SCALE;
		a->y = SCALE * tan(angle);
	}
	else if (angle > PI / 2 && angle <= PI)//puts("LEFT down");
	{
		next->x = ptr->player.x / SCALE * SCALE - 1;
		next->y = ptr->player.y + tan (PI - angle) * (ptr->player.x - next->x);
		a->x = -SCALE;
		a->y = SCALE * tan(PI - angle);
	}
	else if (angle > PI && angle < PI + PI / 2)//puts("LEFT UP");
	{
		next->x = ptr->player.x / SCALE * SCALE - 1;
		next->y = ptr->player.y - (ptr->player.x - next->x) * tan(angle - PI);
		a->x = -SCALE;
		a->y = -SCALE * tan(angle - PI);
	}
	else
	{
		next->x = ptr->parse.x * SCALE;
		next->y = ptr->parse.y * SCALE;
		a->x = ptr->parse.x * SCALE;
		a->y = ptr->parse.y * SCALE;
	}
}



t_point	ray(t_ptr *ptr, double angle)
{
	t_point	next;
	t_point	nexty;
	t_point	nextx;
	t_point	ax;
	t_point	ay;

	init_param_y(ptr, &nexty, &ay, angle);
	init_param_x(ptr, &nextx, &ax, angle);
	while (1)
	{
		if (distance(ptr->player, nexty) > distance(ptr->player, nextx))
		{
			next = nextx;
			next.color = GREEN;
			nextx.x += ax.x;
			nextx.y += ax.y;
		}
		else
		{
			next = nexty;
			next.color = WHITE;
			nexty.x += ay.x;
			nexty.y += ay.y;
		}
		if (exeed_map(ptr, next) || ptr->map2d[(long long)(next.y / SCALE)][(long long)(next.x / SCALE)] != '0')
			break ;
	}
	return (next);
}

double function_(double a)
{
	a = a - (int)(a / RAD) * RAD;
	if (a < 0)
		a = RAD + a;
	return (a);
}

void	put_arrow(t_ptr *ptr)
{
	double	a = function_(ptr->player.angle - EYE_ANGLE);
	size_t c = 0;
	t_player	p = ptr->player;
	t_point		next;
	double xx;

	int	n;

	while (c <= HEIGHT)
	{
		next = ray(ptr, a);
		// x(ptr, &next, a);
		xx = ptr->player.angle - a;
		if (xx < 0)
			xx += RAD;
		if (xx > RAD)
			xx -= RAD;
		n = distance(p, next) * cos(xx);
		create_square(&ptr->img3d, n, c,next.color);
		c++;
		a = function_(a + 0.00081812308687);
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
	// ptr->win.win = mlx_new_window(ptr->win.mlx, ptr->parse.x * SCALE, ptr->parse.y * SCALE, "Cub3D map2d");
	ptr->win3d = mlx_new_window(ptr->win.mlx, HEIGHT, WIDTH, "Cub3D map3D");
	// ptr->win.img.img = mlx_new_image(ptr->win.mlx, ptr->parse.x * SCALE, ptr->parse.y * SCALE);
	// ptr->win.img.addr = mlx_get_data_addr(ptr->win.img.img, &ptr->win.img.bits_per_pixel, &ptr->win.img.line_length,
	// 			&ptr->win.img.endian);
	ptr->img3d.img = mlx_new_image(ptr->win.mlx,HEIGHT ,WIDTH);
	ptr->img3d.addr = mlx_get_data_addr(ptr->img3d.img, &ptr->img3d.bits_per_pixel, &ptr->img3d.line_length,
				&ptr->img3d.endian);
}

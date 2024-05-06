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

double	distance(t_player p, t_point next)
{
	return (sqrt((p.x - next.x) * (p.x - next.x) + (p.y - next.y) * (p.y - next.y)));
}

void x(t_ptr *ptr, t_point *next, double angle)
{
	long long i = 1;
	long long d = distance(ptr->player, *next);
	t_point a;

	/*if (!exeed_map(ptr, *next))
	{
		my_mlx_pixel_put(&ptr->win.img, (double)next->x / SCALE * DEBUG_SCALE, (double)next->y / SCALE * DEBUG_SCALE, RED);
		my_mlx_pixel_put(&ptr->win.img, (double)next->x / SCALE * DEBUG_SCALE + 1, (double)next->y / SCALE * DEBUG_SCALE, RED);
		my_mlx_pixel_put(&ptr->win.img, (double)next->x / SCALE * DEBUG_SCALE - 1, (double)next->y / SCALE * DEBUG_SCALE, RED);
		my_mlx_pixel_put(&ptr->win.img, (double)next->x / SCALE * DEBUG_SCALE, (double)next->y / SCALE * DEBUG_SCALE - 1, RED);
		my_mlx_pixel_put(&ptr->win.img, (double)next->x / SCALE * DEBUG_SCALE, (double)next->y / SCALE * DEBUG_SCALE + 1, RED);
	}*/
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
			next->y = ptr->player.y / SCALE * SCALE - MAGIC_NUMBER;
			next->x = ptr->player.x + (ptr->player.y - next->y) / tan(RAD - angle);
			a->y = -SCALE;
			a->x = SCALE / tan(RAD - angle);
		}
		else if (angle < PI + PI / 2)//puts("up left");
		{
			next->y = ptr->player.y / SCALE * SCALE - MAGIC_NUMBER;
			next->x = ptr->player.x + (ptr->player.y - next->y) / tan(RAD - angle);
			a->y = -SCALE;
			a->x = a->y / tan(angle - PI);
		}
		else // up
		{
			next->y = ptr->player.y / SCALE * SCALE - MAGIC_NUMBER; 
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
			next->y = ptr->player.y / SCALE * SCALE + SCALE;
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
		next->x = ptr->player.x / SCALE * SCALE - MAGIC_NUMBER;
		next->y = ptr->player.y + tan (PI - angle) * (ptr->player.x - next->x);
		a->x = -SCALE;
		a->y = SCALE * tan(PI - angle);
	}
	else if (angle > PI && angle < PI + PI / 2)//puts("LEFT UP");
	{
		next->x = ptr->player.x / SCALE * SCALE - MAGIC_NUMBER;
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

void check_faces(t_ptr *ptr, t_point *next, t_point nexty, t_point nextx)
{

	// printf("%f:%f\n", distance(ptr->player, nexty) , distance(ptr->player, nextx));
	// if (next.x == nexty.x && next)
	// 	next->color = GREEN;
	// else
		// next->color = WHITE;
}

int check_wall(t_ptr *ptr, t_point point)
{
	if (exeed_map(ptr, point) || ptr->map2d[(long long)point.y / SCALE][(long long)point.x / SCALE] != '0')
		return (1);
	return (0);
}

double calculate_incrementation()
{
	return (d2rad(1. / ((double)HEIGHT / EYE_ANGLE)));
	// return (0.00081812308687);
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
			if (check_wall(ptr, nextx) && ((angle < PI / 2 && angle >= 0) || (angle > PI + PI / 2 && angle <= RAD)))
				next.face = GRAY;
			else if (check_wall(ptr, nextx))
				next.face = GREEN;
			nextx.x += ax.x;
			nextx.y += ax.y;
		}
		else if (distance(ptr->player, nexty) < distance(ptr->player, nextx))
		{
			next = nexty;
			if (check_wall(ptr, nexty) && angle > PI && angle < RAD)
				next.face = WHITE;
			else if (check_wall(ptr, nexty))
				next.face = BLEU;
			nexty.x += ay.x;
			nexty.y += ay.y;
		}
		if (check_wall(ptr, next))	
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
	// double	a = function_(ptr->player.angle);
	double	a = function_(ptr->player.angle - d2rad(EYE_ANGLE / 2));
	size_t c = 0;
	t_player	p = ptr->player;
	t_point		next;
	double xx;

	// t_point	h;

	double	n;

	while (c < HEIGHT)
	{
		next = ray(ptr, a);
		if (DEBUG)
			x(ptr, &next, a);
		xx = ptr->player.angle - a;
		if (xx < 0)
			xx += RAD;
		if (xx > RAD)
			xx -= RAD;
		n = distance(p, next) * cos(xx);

		// printf("%ld, %f\n", (size_t)(next.x / SCALE * SCALE) / SCALE * SCALE  ,   next.y / SCALE * SCALE + MAGIC_NUMBER);

	
		// my_mlx_pixel_put(&ptr->win.img, (size_t)(next.x / SCALE * DEBUG_SCALE) / DEBUG_SCALE * DEBUG_SCALE, next.y / SCALE * DEBUG_SCALE + 1, yellow);
		// my_mlx_pixel_put(&ptr->win.img, (size_t)(next.x / SCALE * DEBUG_SCALE) / DEBUG_SCALE * DEBUG_SCALE, next.y / SCALE * DEBUG_SCALE - 1, yellow);
		// my_mlx_pixel_put(&ptr->win.img, (size_t)(next.x / SCALE * DEBUG_SCALE) / DEBUG_SCALE * DEBUG_SCALE - 1, next.y / SCALE * DEBUG_SCALE, yellow);
		// my_mlx_pixel_put(&ptr->win.img, (size_t)(next.x / SCALE * DEBUG_SCALE) / DEBUG_SCALE * DEBUG_SCALE + 1, next.y / SCALE * DEBUG_SCALE, yellow);
		create_square(ptr, n, c,next);
		c++;
		a = function_(a + calculate_incrementation());
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
	while (y < ptr->parse.y * DEBUG_SCALE)
	{
		x = 0;
		while (x < ptr->parse.x * DEBUG_SCALE)
		{
			if (x % DEBUG_SCALE != 0 && y % DEBUG_SCALE != 0)
				my_mlx_pixel_put(&ptr->win.img, x, y, color_unit_pixel(ptr->map2d[y / DEBUG_SCALE][x / DEBUG_SCALE]));
			else
				my_mlx_pixel_put(&ptr->win.img, x, y, GRAY);
			x++;
		}
		y++;
	}
}

void	put_player_to_image(t_img_data *img, t_player player)
{
	double x;
	double y;
	double n;
	double x_max;
	double y_max;


	y = ((double)player.y / SCALE * DEBUG_SCALE) - SCALE_P;
	x_max = ((double)player.x / SCALE * DEBUG_SCALE) + SCALE_P;
	y_max = ((double)player.y / SCALE * DEBUG_SCALE) + SCALE_P;
	while (y <= y_max)
	{
		x = ((double)player.x / SCALE * DEBUG_SCALE) - SCALE_P;
		while (x <= x_max)
		{
			my_mlx_pixel_put(img, x, y, RED);
			x++;
		}
		y++;
	}
	n = 1;
	while (n < 10)
	{
		my_mlx_pixel_put(img, ((double)player.x / SCALE * DEBUG_SCALE) + (cos((double)player.angle) * n), ((double)player.y / SCALE * DEBUG_SCALE) + (sin((double)player.angle) * n), RED);

		my_mlx_pixel_put(img, ((double)(player.x - 10) / SCALE * DEBUG_SCALE) + (cos((double)player.angle) * n), ((double)player.y / SCALE * DEBUG_SCALE) + (sin((double)player.angle) * n), RED);
		my_mlx_pixel_put(img, ((double)(player.x + 10) / SCALE * DEBUG_SCALE) + (cos((double)player.angle) * n), ((double)player.y / SCALE * DEBUG_SCALE) + (sin((double)player.angle) * n), RED);

		my_mlx_pixel_put(img, ((double)player.x / SCALE * DEBUG_SCALE) + (cos((double)player.angle) * n), ((double)(player.y - 10) / SCALE * DEBUG_SCALE) + (sin((double)player.angle) * n), RED);
		my_mlx_pixel_put(img, ((double)player.x / SCALE * DEBUG_SCALE) + (cos((double)player.angle) * n), ((double)(player.y + 10) / SCALE * DEBUG_SCALE) + (sin((double)player.angle) * n), RED);
		n++;
	}
}

void init_images(t_ptr *ptr)
{
	ptr->texture.no_img.img = mlx_xpm_file_to_image(ptr->win.mlx, ptr->parse.no, &ptr->texture.no_w, &ptr->texture.no_h);
	ptr->texture.so_img.img = mlx_xpm_file_to_image(ptr->win.mlx, ptr->parse.so, &ptr->texture.so_w, &ptr->texture.so_h);
	ptr->texture.ea_img.img = mlx_xpm_file_to_image(ptr->win.mlx, ptr->parse.ea, &ptr->texture.ea_w, &ptr->texture.ea_h);
	ptr->texture.we_img.img = mlx_xpm_file_to_image(ptr->win.mlx, ptr->parse.we, &ptr->texture.we_w, &ptr->texture.we_h);
	
	if (!ptr->texture.we_img.img || !ptr->texture.no_img.img || !ptr->texture.so_img.img || !ptr->texture.ea_img.img)
		exit(ft_error(ptr, "Error in images", 1));

	ptr->texture.no_img.addr = mlx_get_data_addr(ptr->texture.no_img.img, &ptr->texture.no_img.bits_per_pixel, &ptr->texture.no_img.line_length, &ptr->texture.no_img.endian);
	ptr->texture.so_img.addr = mlx_get_data_addr(ptr->texture.so_img.img, &ptr->texture.so_img.bits_per_pixel, &ptr->texture.so_img.line_length, &ptr->texture.so_img.endian);
	ptr->texture.we_img.addr = mlx_get_data_addr(ptr->texture.we_img.img, &ptr->texture.we_img.bits_per_pixel, &ptr->texture.we_img.line_length, &ptr->texture.we_img.endian);

	ptr->texture.ea_img.addr = mlx_get_data_addr(ptr->texture.ea_img.img, &ptr->texture.ea_img.bits_per_pixel, &ptr->texture.ea_img.line_length, &ptr->texture.ea_img.endian);
	if (!ptr->texture.ea_img.addr || !ptr->texture.no_img.addr || !ptr->texture.so_img.addr || !ptr->texture.we_img.addr)
		exit(ft_error(ptr, "Error in images2", 1));
}

void	init_mlx(t_ptr *ptr)
{
	ptr->win.mlx = mlx_init();



	init_images(ptr);




	// printf("W:%d\n", ptr->texture.no_w);
	// printf("H:%d\n", ptr->texture.no_h);

	if (DEBUG)
	{
		ptr->win.win = mlx_new_window(ptr->win.mlx, ptr->parse.x * DEBUG_SCALE, ptr->parse.y * DEBUG_SCALE, "Cub3D map2d");
		ptr->win.img.img = mlx_new_image(ptr->win.mlx, ptr->parse.x * DEBUG_SCALE, ptr->parse.y * DEBUG_SCALE);
		ptr->win.img.addr = mlx_get_data_addr(ptr->win.img.img, &ptr->win.img.bits_per_pixel, &ptr->win.img.line_length, &ptr->win.img.endian);
	}


	ptr->win3d = mlx_new_window(ptr->win.mlx, HEIGHT, WIDTH, "Cub3D map3D");

	ptr->img3d.img = mlx_new_image(ptr->win.mlx,HEIGHT ,WIDTH);
	ptr->img3d.addr = mlx_get_data_addr(ptr->img3d.img, &ptr->img3d.bits_per_pixel, &ptr->img3d.line_length,
				&ptr->img3d.endian);
}

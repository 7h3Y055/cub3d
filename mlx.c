#include "cub3d.h"

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





void init_obunga(t_ptr *ptr,t_point *next, double p_angle, int c)
{
	double o_angle = 0;

	if (ptr->obunga.x >= ptr->player.x && ptr->obunga.y >= ptr->player.y)
		o_angle = atan((ptr->obunga.y - ptr->player.y) / (ptr->obunga.x - ptr->player.x));
	else if (ptr->obunga.x <= ptr->player.x && ptr->obunga.y >= ptr->player.y)
		o_angle = PI - atan((ptr->obunga.y - ptr->player.y) / (ptr->player.x - ptr->obunga.x));
	else if (ptr->obunga.x <= ptr->player.x && ptr->obunga.y <= ptr->player.y)
		o_angle = PI + atan((ptr->player.y - ptr->obunga.y) / (ptr->player.x - ptr->obunga.x));
	else
		o_angle = RAD - atan((ptr->player.y - ptr->obunga.y) / (ptr->obunga.x - ptr->player.x));

	ptr->obunga.angle = o_angle;

	if (!btw_range(o_angle, fix_rad_overflow( ptr->player.angle - d2rad(EYE_ANGLE / 2)), fix_rad_overflow( ptr->player.angle + d2rad(EYE_ANGLE / 2))))
		ptr->obunga.dst = 0;
	if (btw_range(o_angle, fix_rad_overflow(p_angle - calculate_incrementation() / 2), fix_rad_overflow(p_angle + calculate_incrementation() / 2)))
	{
		if (distance(*ptr, ptr->flgas.tmp, 1) < distance(*ptr, *next, 0))
		{
			ptr->obunga.img_x = c;
			ptr->obunga.dst = distance(*ptr, ptr->flgas.tmp, 1);
		}
		else
		{
			ptr->obunga.dst = 0;
		}
	}


}


void	put_rays(t_ptr *ptr)
{
	size_t c;

	c = 0;
	while (c < HEIGHT)
	{
		if (distance(*ptr, ptr->rays[c].next, 0) > distance(*ptr, ptr->flgas.tmp, 1))
			create_square(ptr, ptr->rays[c].n, c, ptr->rays[c].next);
		c++;
	}

    put_obunga_to_img(ptr);

	c = 0;
	while (c < HEIGHT)
	{
		if (distance(*ptr, ptr->rays[c].next, 0) <= distance(*ptr, ptr->flgas.tmp, 1))
			create_square(ptr, ptr->rays[c].n, c, ptr->rays[c].next);
		c++;
	}
}


void	put_player_to_image(t_img_data *img, t_player player)
{
	double x;
	double y;
	double n;
	double x_max;
	double y_max;


	y = ((double)player.y / SCALE * MAP_SCALE) - SCALE_P;
	x_max = ((double)player.x / SCALE * MAP_SCALE) + SCALE_P;
	y_max = ((double)player.y / SCALE * MAP_SCALE) + SCALE_P;
	while (y < y_max)
	{
		x = ((double)player.x / SCALE * MAP_SCALE) - SCALE_P;
		while (x < x_max)
		{
			my_mlx_pixel_put(img, x, y, RED);
			x++;
		}
		y++;
	}
}

void init_images(t_ptr *ptr)
{
	ptr->texture.no_img.img = mlx_xpm_file_to_image(ptr->win.mlx, ptr->parse.no, &ptr->texture.no_w, &ptr->texture.no_h);
	ptr->texture.so_img.img = mlx_xpm_file_to_image(ptr->win.mlx, ptr->parse.so, &ptr->texture.so_w, &ptr->texture.so_h);
	ptr->texture.ea_img.img = mlx_xpm_file_to_image(ptr->win.mlx, ptr->parse.ea, &ptr->texture.ea_w, &ptr->texture.ea_h);
	ptr->texture.we_img.img = mlx_xpm_file_to_image(ptr->win.mlx, ptr->parse.we, &ptr->texture.we_w, &ptr->texture.we_h);
	ptr->obunga.img.img = mlx_xpm_file_to_image(ptr->win.mlx, ptr->obunga.path, &ptr->obunga.img_w, &ptr->obunga.img_h);


	ptr->texture.d_img.img = mlx_xpm_file_to_image(ptr->win.mlx, "./resources/doors/c.xpm", &ptr->texture.d_w, &ptr->texture.d_h);

	
	if (!ptr->texture.we_img.img || !ptr->texture.no_img.img || !ptr->texture.so_img.img || !ptr->texture.ea_img.img || !ptr->obunga.img.img || !ptr->texture.d_img.img)
		exit(ft_error(ptr, "Error in images", 1));

	ptr->texture.no_img.addr = mlx_get_data_addr(ptr->texture.no_img.img, &ptr->texture.no_img.bits_per_pixel, &ptr->texture.no_img.line_length, &ptr->texture.no_img.endian);
	ptr->texture.so_img.addr = mlx_get_data_addr(ptr->texture.so_img.img, &ptr->texture.so_img.bits_per_pixel, &ptr->texture.so_img.line_length, &ptr->texture.so_img.endian);
	ptr->texture.we_img.addr = mlx_get_data_addr(ptr->texture.we_img.img, &ptr->texture.we_img.bits_per_pixel, &ptr->texture.we_img.line_length, &ptr->texture.we_img.endian);
	ptr->texture.ea_img.addr = mlx_get_data_addr(ptr->texture.ea_img.img, &ptr->texture.ea_img.bits_per_pixel, &ptr->texture.ea_img.line_length, &ptr->texture.ea_img.endian);
	ptr->obunga.img.addr = mlx_get_data_addr(ptr->obunga.img.img, &ptr->obunga.img.bits_per_pixel, &ptr->obunga.img.line_length, &ptr->obunga.img.endian);

	ptr->texture.d_img.addr = mlx_get_data_addr(ptr->texture.d_img.img, &ptr->texture.d_img.bits_per_pixel, &ptr->texture.d_img.line_length, &ptr->texture.d_img.endian);


	if (!ptr->texture.ea_img.addr || !ptr->texture.no_img.addr || !ptr->texture.so_img.addr || !ptr->texture.we_img.addr ||  !ptr->obunga.img.addr || !ptr->texture.d_img.addr)
		exit(ft_error(ptr, "Error in images2", 1));
}

void	jump_init(t_ptr *ptr)
{
	ptr->jumps.jump_hight = 2000;
	ptr->jumps.jump_speeddown = 100;
	ptr->jumps.jump_speedup = 200;
	ptr->jumps.jump_stats = 0;
}

void	init_mlx(t_ptr *ptr)
{
	ptr->win.mlx = mlx_init();
	init_images(ptr);
	jump_init(ptr);
	ptr->rays = malloc(sizeof(t_rays)  * HEIGHT);
	ptr->win3d = mlx_new_window(ptr->win.mlx, HEIGHT, WIDTH, "Cub3D map3D");
	ptr->img3d.img = mlx_new_image(ptr->win.mlx,HEIGHT ,WIDTH);
	ptr->img3d.addr = mlx_get_data_addr(ptr->img3d.img, &ptr->img3d.bits_per_pixel, &ptr->img3d.line_length, &ptr->img3d.endian);
}

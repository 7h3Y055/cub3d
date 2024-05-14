#include "cub3d.h"

int	check_wall_obunga(t_ptr *ptr, size_t n)
{
	double	y;
	double	x;

	x = ptr->obunga.x + -cos(ptr->obunga.angle) * n;
	y = ptr->obunga.y + -sin(ptr->obunga.angle) * n;
	if (ptr->map2d[(long long)(y / SCALE)][(long long)(x / SCALE)] == '1')
		return (1);
	x = ptr->obunga.x + -cos(ptr->obunga.angle + 0.2) * n;
	y = ptr->obunga.y + -sin(ptr->obunga.angle + 0.2) * n;
	if (ptr->map2d[(long long)(y / SCALE)][(long long)(x / SCALE)] == '1')
		return (1);
	x = ptr->obunga.x + -cos(ptr->obunga.angle - 0.2) * n;
	y = ptr->obunga.y + -sin(ptr->obunga.angle - 0.2) * n;
	if (ptr->map2d[(long long)(y / SCALE)][(long long)(x / SCALE)] == '1')
		return (1);
	return (0);
}

void	obunga_move(t_ptr *ptr)
{
	long long	y;
	long long	x;

	y = -sin(ptr->obunga.angle) * ENEMY_SPEED;
	x = -cos(ptr->obunga.angle) * ENEMY_SPEED;
	if (ptr->map2d[((int)ptr->obunga.y + (y * ENEMY_SPACE))
		/ SCALE][((int)ptr->obunga.x) / SCALE] == '0'
		|| ptr->map2d[((int)ptr->obunga.y + (y * ENEMY_SPACE))
		/ SCALE][((int)ptr->obunga.x) / SCALE] == 'O')
		ptr->obunga.y += y;
	if (ptr->map2d[((int)ptr->obunga.y) / SCALE][((int)ptr->obunga.x + (x
				* ENEMY_SPACE)) / SCALE] == '0'
		|| ptr->map2d[((int)ptr->obunga.y) / SCALE][((int)ptr->obunga.x + (x
				* ENEMY_SPACE)) / SCALE] == 'O')
		ptr->obunga.x += x;
}

void	put_obunga_to_img(t_ptr *ptr)
{
	int	color;
	int	y;
	int	x;
	int	consts;
	int	dst;

	if (ptr->obunga.dst == 0)
		return ;
	consts = (SCALE * WIDTH) / ptr->obunga.dst;
	dst = (SCALE * HEIGHT) / ptr->obunga.dst;
	ptr->jumps.consts = scaleBetween(ptr->jumps.jump_stats * dst, 0, 200, 0,
			WIDTH * HEIGHT) + +ptr->updown;
	x = ptr->obunga.img_x - consts;
	while (x < (int)ptr->obunga.img_x + consts)
	{
		y = WIDTH / 2 + ptr->jumps.consts - dst / 2;
		while (y < (WIDTH / 2 + ptr->jumps.consts) + (dst) / 2 && y < WIDTH)
		{
			if (x < HEIGHT && x > 0 && y > 0 && y < WIDTH)
			{
				color = get_obunga_color(ptr, y - ptr->jumps.consts, x, WIDTH
						/ 2 - dst / 2, ptr->obunga.img_x - consts, (WIDTH / 2)
						+ (dst) / 2, ptr->obunga.img_x + consts);
				if (color >= 0)
					my_mlx_pixel_put(&ptr->img3d, x, y, color);
			}
			y++;
		}
		x++;
	}
}

int	get_obunga_color(t_ptr *ptr, size_t y, size_t x, size_t first_point_y,
		size_t first_point_x, size_t max_y, size_t max_x)
{
	char		*dst;
	int			img_y;
	int			img_x;
	static int	n;

	img_y = scaleBetween(y, 0, ptr->obunga.img_w, first_point_y, max_y);
	img_x = scaleBetween(x, 0, ptr->obunga.img_h, first_point_x, max_x);
	dst = ptr->obunga.img.addr + (img_y * ptr->obunga.img.line_length + img_x
			* (ptr->obunga.img.bits_per_pixel / 8));
	return (*(int *)dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obunga.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:48:05 by ybouchma          #+#    #+#             */
/*   Updated: 2024/05/18 10:40:48 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	put_obunga_to_img_helper(t_ptr *ptr, int y, int x, int dst)
{
	int	color;
	int	consts;

	consts = (SCALE * WIDTH) / ptr->obunga.dst;
	if (x < HEIGHT && x > 0 && y > 0 && y < WIDTH)
	{
		ptr->flgas.dst = dst;
		ptr->flgas.consts = consts;
		color = get_obunga_color(ptr, y - ptr->jumps.consts, x);
		if (ptr->flgas.img)
			return (-1);
		if (color >= 0)
			my_mlx_pixel_put(&ptr->win.img, x, y, color);
	}
	return (0);
}

void	put_obunga_to_img(t_ptr *ptr)
{
	int	y;
	int	x;
	int	consts;
	int	dst;

	if (ptr->obunga.dst == 0)
		return ;
	consts = (SCALE * WIDTH) / ptr->obunga.dst;
	dst = (SCALE * HEIGHT) / ptr->obunga.dst;
	ptr->jumps.consts = scalebetween(ptr->jumps.jump_stats * dst, 200, 0, WIDTH
			* HEIGHT) + +ptr->updown;
	x = ptr->obunga.img_x - consts;
	ptr->flgas.img = 0;
	while (x < (int)ptr->obunga.img_x + consts)
	{
		y = WIDTH / 2 + ptr->jumps.consts - dst / 2;
		while (y < (WIDTH / 2 + ptr->jumps.consts) + (dst) / 2 && y < WIDTH)
		{
			if (put_obunga_to_img_helper(ptr, y, x, dst) == -1)
				return ;
			y++;
		}
		x++;
	}
}

int	get_obunga_color(t_ptr *ptr, size_t y, size_t x)
{
	size_t	first_point_y;
	size_t	first_point_x;
	int		img_y;
	int		img_x;

	first_point_y = WIDTH / 2 - ptr->flgas.dst / 2;
	first_point_x = ptr->obunga.img_x - ptr->flgas.consts;
	img_y = scalebetween(y, ptr->obunga.img_w, first_point_y, (WIDTH / 2)
			+ (ptr->flgas.dst) / 2);
	img_x = scalebetween(x, ptr->obunga.img_h
			- 15, first_point_x, ptr->obunga.img_x
			+ ptr->flgas.consts);
	if (img_x > ptr->obunga.img_h)
	{
		ptr->flgas.img = 1;
		return (INT_MIN);
	}
	return (*(int *)(ptr->obunga.img.addr + (img_y * ptr->obunga.img.line_length
			+ img_x * (ptr->obunga.img.bits_per_pixel / 8))));
}

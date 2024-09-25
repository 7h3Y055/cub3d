/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:34:42 by ybouchma          #+#    #+#             */
/*   Updated: 2024/05/18 15:14:15 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_sky(t_ptr *ptr, double dy, double *y, size_t x)
{
	*y = 0;
	while (*y < dy)
	{
		if (*y >= 0 && *y <= WIDTH && x <= HEIGHT)
			my_mlx_pixel_put(&ptr->win.img, x, *y,
				rgb2int(ptr->parse.ceiling[0], ptr->parse.ceiling[1],
					ptr->parse.ceiling[2]));
		(*y)++;
	}
}

void	put_floor(t_ptr *ptr, double y, size_t x)
{
	while (y < WIDTH)
	{
		my_mlx_pixel_put(&ptr->win.img, x, y, rgb2int(ptr->parse.floor[0],
				ptr->parse.floor[1], ptr->parse.floor[2]));
		y++;
	}
}

void	create_square(t_ptr *ptr, double ray_l, size_t x, t_point next)
{
	double	y;
	double	dy;
	int		color;

	ray_l = (SCALE * HEIGHT) / ray_l;
	ptr->jumps.consts = scalebetween(ptr->jumps.jump_stats * ray_l, 200, 0,
			WIDTH * HEIGHT) + ptr->updown;
	dy = (WIDTH / 2 + ptr->jumps.consts) - (ray_l / 2);
	y = 0;
	put_sky(ptr, dy, &y, x);
	next.ray_l = ray_l;
	next.first_point_in_wall = dy;
	while (y < (WIDTH / 2 + ptr->jumps.consts) + (ray_l / 2) && y < WIDTH)
	{
		color = get_pixel_color(ptr, next, (size_t)y);
		if (!(color == -1 || x > HEIGHT || y < 0 || y > WIDTH))
			my_mlx_pixel_put(&ptr->win.img, x, y, color);
		y++;
	}
	put_floor(ptr, y, x);
}

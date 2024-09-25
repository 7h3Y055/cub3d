/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:47:14 by ybouchma          #+#    #+#             */
/*   Updated: 2024/05/18 15:38:06 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_param_y(t_ptr *ptr, t_point *next, t_point *a, double angle)
{
	if (angle > PI && angle < RAD)
		init_param_y_up(ptr, next, a, angle);
	else if (angle < PI && angle > 0)
		init_param_y_down(ptr, next, a, angle);
	else
	{
		next->x = ptr->parse.x * SCALE;
		next->y = ptr->parse.y * SCALE;
		a->x = ptr->parse.x * SCALE;
		a->y = ptr->parse.y * SCALE;
	}
}

void	init_param_x(t_ptr *ptr, t_point *next, t_point *a, double angle)
{
	if (angle > PI + PI / 2 || angle < PI / 2)
		init_param_x_right(ptr, next, a, angle);
	else if (angle > PI / 2 && angle < PI + PI / 2)
		init_param_x_left(ptr, next, a, angle);
	else
	{
		next->x = ptr->parse.x * SCALE;
		next->y = ptr->parse.y * SCALE;
		a->x = ptr->parse.x * SCALE;
		a->y = ptr->parse.y * SCALE;
	}
}

t_point	init_obunga(t_ptr *ptr, t_point *next, double p_angle, int c)
{
	if (c == HEIGHT / 2 && (next->face == DOOR_H || next->face == DOOR_W)
		&& ptr->keys[O] && distance(*ptr, *next, 0) < SCALE * 3)
	{
		ptr->keys[O] = 0;
		ptr->map2d[(long long)(next->y / SCALE)][(long long)(next->x
				/ SCALE)] = 'O';
	}
	init_obunga_angle(ptr);
	if (!btw_range(ptr->obunga.angle, fix_rad_overflow(ptr->player.angle
				- d2rad(EYE_ANGLE / 2)), fix_rad_overflow(ptr->player.angle
				+ d2rad(EYE_ANGLE / 2))))
		ptr->obunga.dst = 0;
	if (btw_range(ptr->obunga.angle, fix_rad_overflow(p_angle
				- calculate_incrementation() / 2), fix_rad_overflow(p_angle
				+ calculate_incrementation() / 2)))
	{
		if (distance(*ptr, ptr->flgas.tmp, 1) < distance(*ptr, *next, 0))
		{
			ptr->obunga.img_x = c;
			ptr->obunga.dst = distance(*ptr, ptr->flgas.tmp, 1);
		}
		else
			ptr->obunga.dst = 0;
	}
	return (*next);
}

void	put_rays(t_ptr *ptr)
{
	size_t	c;

	c = 0;
	while (c < HEIGHT)
	{
		if (distance(*ptr, ptr->rays[c].next, 0) > distance(*ptr,
				ptr->flgas.tmp, 1))
			create_square(ptr, ptr->rays[c].n, c, ptr->rays[c].next);
		c++;
	}
	put_obunga_to_img(ptr);
	c = 0;
	while (c < HEIGHT)
	{
		if (distance(*ptr, ptr->rays[c].next, 0) <= distance(*ptr,
				ptr->flgas.tmp, 1))
			create_square(ptr, ptr->rays[c].n, c, ptr->rays[c].next);
		c++;
	}
}

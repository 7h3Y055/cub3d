/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:44:40 by ybouchma          #+#    #+#             */
/*   Updated: 2024/05/16 16:31:32 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_param_y_up(t_ptr *ptr, t_point *next, t_point *a, double angle)
{
	if (angle > PI + PI / 2)
	{
		next->y = ptr->player.y / SCALE * SCALE - MAGIC_NUMBER;
		next->x = ptr->player.x + (ptr->player.y - next->y) / tan(RAD - angle);
		a->y = -SCALE;
		a->x = SCALE / tan(RAD - angle);
	}
	else if (angle < PI + PI / 2)
	{
		next->y = ptr->player.y / SCALE * SCALE - MAGIC_NUMBER;
		next->x = ptr->player.x + (ptr->player.y - next->y) / tan(RAD - angle);
		a->y = -SCALE;
		a->x = a->y / tan(angle - PI);
	}
	else
	{
		next->y = ptr->player.y / SCALE * SCALE - MAGIC_NUMBER;
		next->x = ptr->player.x;
		a->y = -SCALE;
		a->x = 0;
	}
}

void	init_param_y_down(t_ptr *ptr, t_point *next, t_point *a, double angle)
{
	if (angle < PI / 2)
	{
		next->y = ptr->player.y / SCALE * SCALE + SCALE;
		next->x = ptr->player.x + (next->y - ptr->player.y) / tan(angle);
		a->y = SCALE;
		a->x = a->y / tan(angle);
	}
	else if (angle > PI / 2)
	{
		next->y = ptr->player.y / SCALE * SCALE + SCALE;
		next->x = ptr->player.x + (next->y - ptr->player.y) / tan(angle);
		a->y = SCALE;
		a->x = -a->y / tan(PI - angle);
	}
	else
	{
		next->y = ptr->player.y / SCALE * SCALE + SCALE;
		next->x = ptr->player.x;
		a->y = SCALE;
		a->x = 0;
	}
}

void	init_param_x_right(t_ptr *ptr, t_point *next, t_point *a, double angle)
{
	if (angle > PI + PI / 2)
	{
		next->x = ptr->player.x / SCALE * SCALE + SCALE;
		next->y = ptr->player.y - (next->x - ptr->player.x) * tan(RAD - angle);
		a->x = SCALE;
		a->y = -SCALE * tan(RAD - angle);
	}
	else if (angle < PI / 2)
	{
		next->x = ptr->player.x / SCALE * SCALE + SCALE;
		next->y = ptr->player.y + (next->x - ptr->player.x) * tan(angle);
		a->x = SCALE;
		a->y = SCALE * tan(angle);
	}
}

void	init_param_x_left(t_ptr *ptr, t_point *next, t_point *a, double angle)
{
	if (angle > PI / 2 && angle <= PI)
	{
		next->x = ptr->player.x / SCALE * SCALE - MAGIC_NUMBER;
		next->y = ptr->player.y + tan(PI - angle) * (ptr->player.x - next->x);
		a->x = -SCALE;
		a->y = SCALE * tan(PI - angle);
	}
	else if (angle > PI && angle < PI + PI / 2)
	{
		next->x = ptr->player.x / SCALE * SCALE - MAGIC_NUMBER;
		next->y = ptr->player.y - (ptr->player.x - next->x) * tan(angle - PI);
		a->x = -SCALE;
		a->y = -SCALE * tan(angle - PI);
	}
}

void	init_obunga_angle(t_ptr *ptr)
{
	double	o_angle;

	o_angle = 0;
	if (ptr->obunga.x >= ptr->player.x && ptr->obunga.y >= ptr->player.y)
		o_angle = atan((ptr->obunga.y - ptr->player.y) / (ptr->obunga.x
					- ptr->player.x));
	else if (ptr->obunga.x <= ptr->player.x && ptr->obunga.y >= ptr->player.y)
		o_angle = PI - atan((ptr->obunga.y - ptr->player.y) / (ptr->player.x
					- ptr->obunga.x));
	else if (ptr->obunga.x <= ptr->player.x && ptr->obunga.y <= ptr->player.y)
		o_angle = PI + atan((ptr->player.y - ptr->obunga.y) / (ptr->player.x
					- ptr->obunga.x));
	else
		o_angle = RAD - atan((ptr->player.y - ptr->obunga.y) / (ptr->obunga.x
					- ptr->player.x));
	ptr->obunga.angle = o_angle;
}

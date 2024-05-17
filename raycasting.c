/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:24:23 by ybouchma          #+#    #+#             */
/*   Updated: 2024/05/17 15:06:41 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	ea_we(t_ptr *ptr, t_flags *nextx, double angle)
{
	t_point	next;

	next = nextx->next;
	if (ptr->map2d[(long long)next.y / SCALE][(long long)next.x / SCALE] == 'D')
		next.face = DOOR_W;
	else if (check_wall(ptr, next) && ((angle < PI / 2 && angle >= 0)
			|| (angle > PI + PI / 2 && angle <= RAD)))
		next.face = GRAY;
	else if (check_wall(ptr, next))
		next.face = GREEN;
	nextx->next.x += nextx->a.x;
	nextx->next.y += nextx->a.y;
	return (next);
}

t_point	no_so(t_ptr *ptr, t_flags *nexty, double angle)
{
	t_point	next;

	next = nexty->next;
	if (ptr->map2d[(long long)next.y / SCALE][(long long)next.x / SCALE] == 'D')
		next.face = DOOR_H;
	else if (check_wall(ptr, next) && angle > PI && angle < RAD)
		next.face = WHITE;
	else if (check_wall(ptr, next))
		next.face = BLEU;
	nexty->next.x += nexty->a.x;
	nexty->next.y += nexty->a.y;
	return (next);
}

t_point	distance_y_x(t_ptr *ptr, t_flags *nexty, t_flags *nextx, double angle)
{
	if (distance(*ptr, nexty->next, 0) > distance(*ptr, nextx->next, 0))
		return (ea_we(ptr, nextx, angle));
	else if (distance(*ptr, nexty->next, 0) < distance(*ptr, nextx->next, 0))
		return (no_so(ptr, nexty, angle));
	return (ptr->flgas.tmp);
}

t_point	ray(t_ptr *ptr, double angle, int c)
{
	t_point	next;
	t_flags	nexty;
	t_flags	nextx;

	init_param_y(ptr, &nexty.next, &nexty.a, angle);
	init_param_x(ptr, &nextx.next, &nextx.a, angle);
	while (1)
	{
		next = distance_y_x(ptr, &nexty, &nextx, angle);
		if (check_wall(ptr, next))
			break ;
		if (c == HEIGHT / 2 && ptr->map2d[(long long)next.y
				/ SCALE][(long long)next.x / SCALE] == 'O' && ptr->keys[O]
			&& distance(*ptr, next, 0) < SCALE * 3)
		{
			ptr->keys[O] = 0;
			if (!((long long)(ptr->obunga.y / SCALE) == (long long)(next.y
				/ SCALE) && (long long)(ptr->obunga.x
						/ SCALE) == (long long)(next.x / SCALE)))
				ptr->map2d[(long long)(next.y / SCALE)][(long long)(next.x
						/ SCALE)] = 'D';
		}
	}
	return (init_obunga(ptr, &next, angle, c));
}

void	raycasting(t_ptr *ptr)
{
	double	a;
	size_t	c;
	double	xx;

	a = fix_rad_overflow(ptr->player.angle - d2rad(EYE_ANGLE / 2));
	c = 0;
	while (c < HEIGHT)
	{
		ptr->rays[c].next = ray(ptr, a, c);
		xx = ptr->player.angle - a;
		if (xx < 0)
			xx += RAD;
		if (xx > RAD)
			xx -= RAD;
		ptr->rays[c].n = distance(*ptr, ptr->rays[c].next, 0) * cos(xx);
		c++;
		a = fix_rad_overflow(a + calculate_incrementation());
	}
}

#include "cub3d.h"

t_point	ray(t_ptr *ptr, double angle, int c)
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
		if (distance(*ptr, nexty, 0) > distance(*ptr, nextx, 0))
		{
			next = nextx;
			if (ptr->map2d[(int)next.y / SCALE][(int)next.x / SCALE] == 'D')
				next.face = DOOR_W;
			else if (check_wall(ptr, nextx) && ((angle < PI / 2 && angle >= 0)
					|| (angle > PI + PI / 2 && angle <= RAD)))
				next.face = GRAY;
			else if (check_wall(ptr, nextx))
				next.face = GREEN;
			nextx.x += ax.x;
			nextx.y += ax.y;
		}
		else if (distance(*ptr, nexty, 0) < distance(*ptr, nextx, 0))
		{
			next = nexty;
			if (ptr->map2d[(int)next.y / SCALE][(int)next.x / SCALE] == 'D')
				next.face = DOOR_H;
			else if (check_wall(ptr, nexty) && angle > PI && angle < RAD)
				next.face = WHITE;
			else if (check_wall(ptr, nexty))
				next.face = BLEU;
			nexty.x += ay.x;
			nexty.y += ay.y;
		}
		if (c == HEIGHT / 2 && ptr->map2d[(long long)next.y
			/ SCALE][(long long)next.x / SCALE] == 'O' && ptr->keys[O]
			&& distance(*ptr, next, 0) < SCALE * 3)
		{
			ptr->keys[O] = 0;
			if (ptr->obunga.y / SCALE != (long long)next.y / SCALE
				&& ptr->obunga.x / SCALE != (long long)next.x / SCALE)
				ptr->map2d[(long long)next.y / SCALE][(long long)next.x
					/ SCALE] = 'D';
		}
		if (check_wall(ptr, next))
			break ;
	}
	if (c == HEIGHT / 2 && (next.face == DOOR_H || next.face == DOOR_W)
		&& ptr->keys[O] && distance(*ptr, next, 0) < SCALE * 3)
	{
		ptr->keys[O] = 0;
		ptr->map2d[(int)next.y / SCALE][(int)next.x / SCALE] = 'O';
	}
	init_obunga(ptr, &next, angle, c);
	return (next);
}

void	raycasting(t_ptr *ptr)
{
	double	a;
	size_t	c;
	double	xx;
	double	n;

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

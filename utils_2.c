/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:35:13 by ybouchma          #+#    #+#             */
/*   Updated: 2024/05/15 12:36:16 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

double	d2rad(double d)
{
	return (d * PI / 180);
}

int	exeed_map(t_ptr *ptr, t_point p)
{
	if (p.x >= ptr->parse.x * SCALE || p.y >= ptr->parse.y * SCALE || p.x < 0
		|| p.y < 0)
		return (1);
	return (0);
}

double	distance(t_ptr ptr, t_point next, int flag)
{
	if (flag)
		return (sqrt((ptr.player.x - ptr.obunga.x) * (ptr.player.x
					- ptr.obunga.x) + (ptr.player.y - ptr.obunga.y)
				* (ptr.player.y - ptr.obunga.y)));
	else
		return (sqrt((ptr.player.x - next.x) * (ptr.player.x - next.x)
				+ (ptr.player.y - next.y) * (ptr.player.y - next.y)));
}

int	check_wall(t_ptr *ptr, t_point point)
{
	if (exeed_map(ptr, point) || ptr->map2d[(long long)(point.y
			/ SCALE)][(long long)(point.x / SCALE)] == '1'
		|| ptr->map2d[(long long)(point.y / SCALE)][(long long)(point.x
			/ SCALE)] == 'D')
		return (1);
	return (0);
}

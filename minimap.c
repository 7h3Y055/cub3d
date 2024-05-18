/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:30:36 by ybouchma          #+#    #+#             */
/*   Updated: 2024/05/18 10:43:48 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_palyer_to_minimap(t_ptr *ptr, int y_map, int x_map)
{
	double	x;
	double	y;
	double	x_max;
	double	y_max;

	y = (double)ptr->player.y / SCALE * ptr->map_scale - y_map - SCALE_P;
	x_max = (double)ptr->player.x / SCALE * ptr->map_scale - x_map + SCALE_P;
	y_max = (double)ptr->player.y / SCALE * ptr->map_scale - y_map + SCALE_P;
	while (y < y_max)
	{
		x = (double)ptr->player.x / SCALE * ptr->map_scale - x_map - SCALE_P;
		while (x < x_max)
		{
			my_mlx_pixel_put(&ptr->win.img, x, y, RED);
			x++;
		}
		y++;
	}
}

void	put_player_angle_to_minimap(t_ptr *ptr, int y_map, int x_map)
{
	int	n;

	n = 1;
	while (n < 20)
	{
		my_mlx_pixel_put(&ptr->win.img, ((double)ptr->player.x / SCALE
				* ptr->map_scale - x_map) + (cos((double)ptr->player.angle)
				* n), ((double)(double)ptr->player.y / SCALE * ptr->map_scale
				- y_map) + (sin((double)ptr->player.angle) * n), RED);
		n++;
	}
}

int	return_color_to_minimap(t_ptr *ptr, int y, int x)
{
	if ((x) % ptr->map_scale != 0 && (y) % ptr->map_scale != 0)
		return (color_unit_pixel(ptr->map2d[(y) / ptr->map_scale][(x)
				/ ptr->map_scale]));
	else
		return (GRAY);
}

void	put_minimap(t_ptr *ptr)
{
	int	x;
	int	y;
	int	x_map;
	int	y_map;

	x_map = ((double)ptr->player.x / SCALE) * ptr->map_scale - MAP_H / 2;
	y_map = ((double)ptr->player.y / SCALE) * ptr->map_scale - MAP_W / 2;
	y = 5;
	while (y < MAP_W)
	{
		x = 5;
		while (x < MAP_H)
		{
			if (x + x_map >= 0 && x + x_map < ptr->parse.x * ptr->map_scale && y
				+ y_map >= 0 && y + y_map < ptr->parse.y * ptr->map_scale)
				my_mlx_pixel_put(&ptr->win.img, x, y,
					return_color_to_minimap(ptr, y + y_map, x + x_map));
			else
				my_mlx_pixel_put(&ptr->win.img, x, y, BLACK);
			x++;
		}
		y++;
	}
	put_palyer_to_minimap(ptr, y_map, x_map);
	put_player_angle_to_minimap(ptr, y_map, x_map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d23d_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:43:14 by ybouchma          #+#    #+#             */
/*   Updated: 2024/05/16 16:35:25 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_wh(t_ptr *ptr, t_point next, int *w, int *h)
{
	if (next.face == WHITE)
	{
		*w = ptr->texture.no_w;
		*h = ptr->texture.no_h;
	}
	if (next.face == BLEU)
	{
		*w = ptr->texture.so_w;
		*h = ptr->texture.so_h;
	}
	if (next.face == GREEN)
	{
		*w = ptr->texture.we_w;
		*h = ptr->texture.we_h;
	}
	if (next.face == GRAY)
	{
		*w = ptr->texture.ea_w;
		*h = ptr->texture.ea_h;
	}
	if (next.face == DOOR_H || next.face == DOOR_W)
	{
		*w = ptr->texture.d_w;
		*h = ptr->texture.d_h;
	}
}

int	init_img_yx(t_ptr *ptr, t_point next, int *img_y, int *img_x)
{
	int	w;
	int	h;

	init_wh(ptr, next, &w, &h);
	if (next.face == GREEN || next.face == GRAY || next.face == DOOR_W)
		*img_x = (next.y - (long long)next.y / SCALE * SCALE) * w / SCALE;
	else
		*img_x = (next.x - (long long)next.x / SCALE * SCALE) * w / SCALE;
	*img_y = (ptr->flgas.y - next.first_point_in_wall) * (h / next.ray_l);
	if (*img_y < 0 || *img_y >= h || *img_x < 0 || *img_x >= w)
		return (-1);
	return (0);
}

char	*get_image_color(t_ptr *ptr, t_point next, int img_x, int img_y)
{
	char	*dst;

	if (next.face == WHITE)
		dst = ptr->texture.no_img.addr + (img_y
				* ptr->texture.no_img.line_length + img_x
				* (ptr->texture.no_img.bits_per_pixel / 8));
	if (next.face == BLEU)
		dst = ptr->texture.so_img.addr + (img_y
				* ptr->texture.so_img.line_length + img_x
				* (ptr->texture.so_img.bits_per_pixel / 8));
	if (next.face == GREEN)
		dst = ptr->texture.we_img.addr + (img_y
				* ptr->texture.we_img.line_length + img_x
				* (ptr->texture.we_img.bits_per_pixel / 8));
	if (next.face == GRAY)
		dst = ptr->texture.ea_img.addr + (img_y
				* ptr->texture.ea_img.line_length + img_x
				* (ptr->texture.ea_img.bits_per_pixel / 8));
	if (next.face == DOOR_H || next.face == DOOR_W)
		dst = ptr->texture.d_img.addr + (img_y * ptr->texture.d_img.line_length
				+ img_x * (ptr->texture.d_img.bits_per_pixel / 8));
	return (dst);
}

int	get_pixel_color(t_ptr *ptr, t_point next, size_t y)
{
	int	img_y;
	int	img_x;

	ptr->flgas.y = y;
	if (init_img_yx(ptr, next, &img_y, &img_x) == -1)
		return (rgb2int(ptr->parse.floor[0], ptr->parse.floor[1],
				ptr->parse.floor[2]));
	return (*(int *)get_image_color(ptr, next, img_x, img_y));
}

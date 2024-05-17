/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:36:47 by ybouchma          #+#    #+#             */
/*   Updated: 2024/05/17 16:59:03 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_mal(t_ptr *ptr)
{
	free(ptr->parse.ea);
	free(ptr->parse.no);
	free(ptr->parse.so);
	free(ptr->parse.we);
	free(ptr->obunga.path);
	free(ptr->rays);
	free_alloc(ptr->map2d, ptr->parse.y + 2);
	free(ptr->parse.ceiling);
	free(ptr->parse.floor);
}

void	free_all(t_ptr *ptr)
{
	free_mal(ptr);
	if (ptr->texture.d_img.img)
		mlx_destroy_image(ptr->win.mlx, ptr->texture.d_img.img);
	if (ptr->texture.we_img.img)
		mlx_destroy_image(ptr->win.mlx, ptr->texture.we_img.img);
	if (ptr->texture.no_img.img)
		mlx_destroy_image(ptr->win.mlx, ptr->texture.no_img.img);
	if (ptr->texture.so_img.img)
		mlx_destroy_image(ptr->win.mlx, ptr->texture.so_img.img);
	if (ptr->texture.ea_img.img)
		mlx_destroy_image(ptr->win.mlx, ptr->texture.ea_img.img);
	if (ptr->obunga.img.img)
		mlx_destroy_image(ptr->win.mlx, ptr->obunga.img.img);
	if (ptr->win.img.img)
		mlx_destroy_image(ptr->win.mlx, ptr->win.img.img);
	if (ptr->win.win)
		mlx_destroy_window(ptr->win.mlx, ptr->win.win);
	if (ptr->win.mlx)
		mlx_destroy_display(ptr->win.mlx);
	free(ptr->win.mlx);
}

void	valid_color(t_ptr *ptr, int *color)
{
	if (color[0] > 255 || color[1] > 255 || color[2] > 255)
	{
		free(color);
		exit(ft_error(ptr, "invalid color", 1));
	}
}

int	destroy_all(t_ptr *ptr)
{
	exit(ft_error(ptr, NULL, 0));
}

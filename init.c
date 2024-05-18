/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:46:17 by ybouchma          #+#    #+#             */
/*   Updated: 2024/05/18 10:44:41 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data_image(t_ptr *ptr)
{
	ptr->texture.no_img.addr = mlx_get_data_addr(ptr->texture.no_img.img,
			&ptr->texture.no_img.bits_per_pixel,
			&ptr->texture.no_img.line_length, &ptr->texture.no_img.endian);
	ptr->texture.so_img.addr = mlx_get_data_addr(ptr->texture.so_img.img,
			&ptr->texture.so_img.bits_per_pixel,
			&ptr->texture.so_img.line_length, &ptr->texture.so_img.endian);
	ptr->texture.we_img.addr = mlx_get_data_addr(ptr->texture.we_img.img,
			&ptr->texture.we_img.bits_per_pixel,
			&ptr->texture.we_img.line_length, &ptr->texture.we_img.endian);
	ptr->texture.ea_img.addr = mlx_get_data_addr(ptr->texture.ea_img.img,
			&ptr->texture.ea_img.bits_per_pixel,
			&ptr->texture.ea_img.line_length, &ptr->texture.ea_img.endian);
	ptr->obunga.img.addr = mlx_get_data_addr(ptr->obunga.img.img,
			&ptr->obunga.img.bits_per_pixel, &ptr->obunga.img.line_length,
			&ptr->obunga.img.endian);
	ptr->texture.d_img.addr = mlx_get_data_addr(ptr->texture.d_img.img,
			&ptr->texture.d_img.bits_per_pixel, &ptr->texture.d_img.line_length,
			&ptr->texture.d_img.endian);
	if (!ptr->texture.ea_img.addr || !ptr->texture.no_img.addr
		|| !ptr->texture.so_img.addr || !ptr->texture.we_img.addr
		|| !ptr->obunga.img.addr || !ptr->texture.d_img.addr)
		exit(ft_error(ptr, "images", 1));
}

void	init_images(t_ptr *ptr)
{
	ptr->texture.no_img.img = mlx_xpm_file_to_image(ptr->win.mlx, ptr->parse.no,
			&ptr->texture.no_w, &ptr->texture.no_h);
	ptr->texture.so_img.img = mlx_xpm_file_to_image(ptr->win.mlx, ptr->parse.so,
			&ptr->texture.so_w, &ptr->texture.so_h);
	ptr->texture.ea_img.img = mlx_xpm_file_to_image(ptr->win.mlx, ptr->parse.ea,
			&ptr->texture.ea_w, &ptr->texture.ea_h);
	ptr->texture.we_img.img = mlx_xpm_file_to_image(ptr->win.mlx, ptr->parse.we,
			&ptr->texture.we_w, &ptr->texture.we_h);
	ptr->obunga.img.img = mlx_xpm_file_to_image(ptr->win.mlx, ptr->obunga.path,
			&ptr->obunga.img_w, &ptr->obunga.img_h);
	ptr->texture.d_img.img = mlx_xpm_file_to_image(ptr->win.mlx,
			"./resources/doors/c.xpm", &ptr->texture.d_w, &ptr->texture.d_h);
	if (!ptr->texture.we_img.img || !ptr->texture.no_img.img
		|| !ptr->texture.so_img.img || !ptr->texture.ea_img.img
		|| !ptr->obunga.img.img || !ptr->texture.d_img.img)
		exit(ft_error(ptr, "images", 1));
	if (!(ptr->obunga.img_w == ptr->obunga.img_h))
		exit(ft_error(ptr, "image is not square!", 1));
	if (!(ptr->obunga.img_w >= 100))
		exit(ft_error(ptr, "image size less than 100x100!", 1));
	init_data_image(ptr);
}

void	jump_init(t_ptr *ptr)
{
	ptr->jumps.jump_hight = 2000;
	ptr->jumps.jump_speeddown = 100;
	ptr->jumps.jump_speedup = 200;
	ptr->jumps.jump_stats = 0;
}

void	init_mlx(t_ptr *ptr)
{
	ptr->win.mlx = mlx_init();
	if (!ptr->win.mlx)
		exit(ft_error(ptr, "mlx_init error", 1));
	if (ptr->parse.x + ptr->parse.y < 20)
		ptr->map_scale = 50;
	if (ptr->parse.x + ptr->parse.y < 60)
		ptr->map_scale = 25;
	else
		ptr->map_scale = 10;
	init_images(ptr);
	jump_init(ptr);
	ptr->rays = ft_calloc(sizeof(t_rays), HEIGHT);
	if (!ptr->rays)
		exit(ft_error(ptr, "malloc error", 1));
	ptr->win.win = mlx_new_window(ptr->win.mlx, HEIGHT, WIDTH, "Cub3D map3D");
	ptr->win.img.img = mlx_new_image(ptr->win.mlx, HEIGHT, WIDTH);
	ptr->win.img.addr = mlx_get_data_addr(ptr->win.img.img,
			&ptr->win.img.bits_per_pixel, &ptr->win.img.line_length,
			&ptr->win.img.endian);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:04:15 by ybouchma          #+#    #+#             */
/*   Updated: 2024/05/19 09:13:52 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	jump(t_ptr *ptr)
{
	if (ptr->keys[ES])
	{
		if (ptr->jumps.jump_stats < ptr->jumps.jump_hight)
		{
			ptr->jumps.jump_stats += ptr->jumps.jump_speedup;
			ptr->jumps.jump_speedup -= 10;
		}
		else
		{
			ptr->keys[ES] = 0;
			ptr->jumps.jump_speedup = 200;
		}
	}
	else
	{
		if (ptr->jumps.jump_stats > 0)
			ptr->jumps.jump_stats -= ptr->jumps.jump_speeddown;
		else
			jump_init(ptr);
	}
}

void	move_angle_with_mouse(t_ptr *ptr)
{
	int			y;
	int			x;
	static int	last_px = HEIGHT / 2;
	static int	last_py = WIDTH / 2;

	mlx_mouse_get_pos(ptr->win.mlx, ptr->win.win, &x, &y);
	if (x < 0)
		ptr->player.angle = fix_rad_overflow(ptr->player.angle - 0.05);
	if (x > HEIGHT)
		ptr->player.angle = fix_rad_overflow(ptr->player.angle + 0.05);
	if (x > last_px && x >= 0 && x <= HEIGHT)
		ptr->player.angle += PI * (abs(x - last_px) - 0) / (HEIGHT - 0) + 0;
	else if (x >= 0 && x <= HEIGHT)
		ptr->player.angle -= PI * (abs(x - last_px) - 0) / (HEIGHT - 0) + 0;
	if (y > last_py && ptr->updown + abs(y - last_py) > -300)
		ptr->updown -= abs(y - last_py);
	else if (ptr->updown - abs(y - last_py) <= 300)
		ptr->updown += abs(y - last_py);
	last_px = x;
	last_py = y;
}

int	render_loop(t_ptr *ptr)
{
	handle_input(ptr);
	raycasting(ptr);
	check_player_death(ptr);
	obunga_move(ptr);
	put_rays(ptr);
	move_angle_with_mouse(ptr);
	put_minimap(ptr);
	mlx_put_image_to_window(ptr->win.mlx, ptr->win.win, ptr->win.img.img, 0, 0);
	return (0);
}

int	main(int argc, char const **argv)
{
	t_ptr	ptr;

	ft_parse(&ptr, argc, argv);
	init_mlx(&ptr);
	mlx_loop_hook(ptr.win.mlx, render_loop, &ptr);
	mlx_hook(ptr.win.win, DestroyNotify, ButtonPressMask, destroy_all, &ptr);
	mlx_hook(ptr.win.win, KeyPress, KeyPressMask, key_pressed, &ptr);
	mlx_hook(ptr.win.win, KeyRelease, KeyReleaseMask, key_released, &ptr);
	mlx_loop(ptr.win.mlx);
	return (0);
}

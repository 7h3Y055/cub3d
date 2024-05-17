/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:37:20 by ybouchma          #+#    #+#             */
/*   Updated: 2024/05/17 15:08:44 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb2int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	ft_error(t_ptr *ptr, char *str, int n)
{
	free_all(ptr);
	if (n)
	{
		ft_putstr_fd("Error\n[cub3d]: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	return (n);
}

size_t	scalebetween(size_t unscaledNum, size_t maxAllowed, size_t min,
		size_t max)
{
	return ((maxAllowed) * (unscaledNum - min) / (max - min));
}

int	handle_input(t_ptr *ptr)
{
	if (ptr->keys[W])
		go_up(ptr);
	if (ptr->keys[A])
		go_left(ptr);
	if (ptr->keys[S])
		go_down(ptr);
	if (ptr->keys[D])
		go_right(ptr);
	if (ptr->keys[R])
		right_angle(ptr);
	if (ptr->keys[L])
		left_argle(ptr);
	if (ptr->keys[E])
		destroy_all(ptr);
	jump(ptr);
	if (ptr->keys[9] && ptr->updown < 300)
		ptr->updown += 10;
	if (ptr->keys[10] && ptr->updown >= -300)
		ptr->updown -= 10;
	return (0);
}

void	check_player_death(t_ptr *ptr)
{
	size_t	n;

	if (distance(*ptr, ptr->flgas.tmp, 1) < SCALE)
	{
		n = 0;
		while (n < distance(*ptr, ptr->flgas.tmp, 1))
		{
			if (check_wall_obunga(ptr, n))
				return ;
			n++;
		}
		ft_putstr_fd("\n[Cub3d] DEATH\n\n", 1);
		exit(ft_error(ptr, NULL, 0));
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:36:47 by ybouchma          #+#    #+#             */
/*   Updated: 2024/05/16 16:45:26 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	(void)ptr;
	exit(0);
}

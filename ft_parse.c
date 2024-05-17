/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:19:44 by ybouchma          #+#    #+#             */
/*   Updated: 2024/05/17 17:56:33 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_valid_map(t_ptr *ptr, int y, int x)
{
	if (!ptr->map2d[y + 1] || (ptr->map2d[y + 1][x] == '\0' || ptr->map2d[y
			+ 1][x] == ' '))
		return (1);
	else if ((y - 1 < 0 || !ptr->map2d[y - 1] || (ptr->map2d[y - 1][x] == '\0'
			|| ptr->map2d[y - 1][x] == ' ')))
		return (2);
	else if (ptr->map2d[y][x + 1] == '\0' || ptr->map2d[y][x + 1] == ' ')
		return (3);
	else if ((x - 1 < 0 || ptr->map2d[y][x - 1] == '\0' || ptr->map2d[y][x
		- 1] == ' '))
		return (4);
	return (0);
}

void	ft_init_obunga_position(t_ptr *ptr, int y, int x)
{
	ptr->obunga.y = y * SCALE + SCALE / 2;
	ptr->obunga.x = x * SCALE + SCALE / 2;
}

void	check_valide_map_helper(t_ptr *ptr, int y, int x, int *n)
{
	if ((ptr->map2d[y][x] == '0' || ptr->map2d[y][x] == 'X'
			|| ptr->map2d[y][x] == 'D') && check_valid_map(ptr, y, x))
		exit(ft_error(ptr, "Invalid map: map is not closed by wall (1)", 1));
	if (ptr->map2d[y][x] == 'X')
	{
		ft_init_obunga_position(ptr, y, x);
		ptr->map2d[y][x] = '0';
		(*n)++;
	}
	else if (ptr->map2d[y][x] == 'D')
	{
		if (!((ptr->map2d[y][x - 1] == '1' && ptr->map2d[y][x + 1] == '1')
				|| (ptr->map2d[y - 1][x] == '1' && ptr->map2d[y
					+ 1][x] == '1')))
			exit(ft_error(ptr, "Door", 1));
	}
	else if (ptr->map2d[y][x] && ptr->map2d[y][x] != '0'
		&& ptr->map2d[y][x] != '1' && ptr->map2d[y][x] != ' ')
	{
		exit(ft_error(ptr, "Invalid map: contain invalid character!", 1));
	}
}

void	check_valide_map(t_ptr *ptr)
{
	int	y;
	int	x;
	int	n;

	y = 0;
	n = 0;
	while (y < ptr->parse.y)
	{
		x = 0;
		while (x < ptr->parse.x)
		{
			check_valide_map_helper(ptr, y, x, &n);
			x++;
		}
		y++;
	}
	if (n > 1)
		exit(ft_error(ptr,
				"Invalid map: more than one enemy starting point (X)", 1));
}

void	ft_parse(t_ptr *ptr, int argc, char const **argv)
{
	int	fd;

	ft_bzero(ptr, sizeof(t_ptr));
	ft_bzero(&ptr->flgas, sizeof(t_flags));
	ptr->start = 1;
	if (argc != 2)
		exit(ft_error(ptr, "need one parameter have path of map", 1));
	check_extention(ptr, argv);
	fd = ft_open(ptr, argv[1]);
	ft_init(ptr, fd);
	check_valide_map(ptr);
}

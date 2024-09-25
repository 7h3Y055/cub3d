/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:12:36 by ybouchma          #+#    #+#             */
/*   Updated: 2024/05/18 15:18:12 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_player_position(t_ptr *ptr, int y, int x, char c)
{
	ptr->player.y = y * SCALE + SCALE / 2;
	ptr->player.x = x * SCALE + SCALE / 2;
	if (c == 'N')
		ptr->player.angle = PI + PI / 2;
	else if (c == 'S')
		ptr->player.angle = PI / 2;
	else if (c == 'E')
		ptr->player.angle = 0;
	else if (c == 'W')
		ptr->player.angle = PI;
}

int	ft_init_map2d_help(t_ptr *ptr, char c, int *y, int *x)
{
	if (!c || c == '\n')
	{
		while (*x < ptr->parse.x - 1)
			ptr->map2d[*y][(*x)++] = ' ';
		*x = 0;
		(*y)++;
		if (!c)
			return (1);
	}
	else if (c != 'N' && c != 'S' && c != 'W' && c != 'E')
		ptr->map2d[*y][(*x)++] = c;
	else
	{
		ptr->flgas.n_p++;
		ft_init_player_position(ptr, *y, *x, c);
		ptr->map2d[*y][(*x)++] = '0';
	}
	return (0);
}

void	ft_init_map2d(t_ptr *ptr, char *str)
{
	int	i;
	int	y;
	int	x;

	i = 0;
	y = 0;
	x = 0;
	ptr->map2d = allocate_memory_for_map2d(ptr, ptr->parse.y + 2, ptr->parse.x
			+ 1);
	while (ptr->map2d[y])
	{
		if (ft_init_map2d_help(ptr, str[i], &y, &x))
			break ;
		i++;
	}
	if (ptr->flgas.n_p == 0 || ptr->flgas.n_p > 1)
	{
		free(str);
		exit(ft_error(ptr,
				"Invalid map:\
less or more than one player starting point (N or E or S or W)",
				1));
	}
	free(ptr->map2d[ptr->parse.y]);
	ptr->map2d[ptr->parse.y] = NULL;
}

char	*ft_read_map(t_ptr *ptr, int fd)
{
	char	*buffer;
	char	*line;
	char	*tmp;

	ptr->parse.y = 0;
	ptr->parse.x = 0;
	buffer = ft_calloc(1, 1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!ft_just_whitespaces(line, 0))
		{
			if (ptr->parse.x < (int)ft_strlen(line) - 1)
				ptr->parse.x = (int)ft_strlen(line) - 1;
			tmp = ft_strjoin(buffer, line);
			free(buffer);
			buffer = tmp;
			ptr->parse.y++;
		}
		free(line);
	}
	return (buffer);
}

void	ft_init(t_ptr *ptr, int fd)
{
	char	*line;
	int		n;

	n = 0;
	while (n < 7)
	{
		line = get_next_line(fd);
		ptr->line = line;
		if (!line)
			break ;
		n += ft_init_texture(ptr, line);
		free(line);
	}
	line = ft_read_map(ptr, fd);
	ft_init_map2d(ptr, line);
	free(line);
}

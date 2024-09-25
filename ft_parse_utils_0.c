/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils_0.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:04:56 by ybouchma          #+#    #+#             */
/*   Updated: 2024/05/15 13:01:15 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_extention(t_ptr *ptr, char const **argv)
{
	if ((!ft_strchr(argv[1], '.') || ft_strrchr(argv[1], '.') == argv[1])
		|| ft_strcmp(ft_strrchr(argv[1], '.'), ".cub") != 0)
		exit(ft_error(ptr, "file name is not .cub extention!", 1));
}

int	ft_open(t_ptr *ptr, char const *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_error(ptr, "", 0);
		perror(path);
		exit(1);
	}
	return (fd);
}

char	*get_texture_path(t_ptr *ptr, char *str)
{
	int		i;
	int		n;
	int		tmp_i;
	char	*path;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	i += 2;
	while (str[i] && ft_isspace(str[i]))
		i++;
	tmp_i = i;
	while (str[i] && !ft_isspace(str[i]))
		i++;
	n = i;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (i == tmp_i || str[i])
	{
		free(str);
		exit(ft_error(ptr, "invalid texture path", 1));
	}
	path = ft_strndup(&str[tmp_i], n - tmp_i);
	return (path);
}

int	skip_comma(char *str, int i)
{
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == ',')
		i++;
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

int	skip_digit(t_ptr *ptr, char *str, int i, int *color)
{
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (ft_isdigit(str[i]))
	{
		while (str[i] && ft_isdigit(str[i]))
			i++;
	}
	else
	{
		free(ptr->line);
		free(color);
		exit(ft_error(ptr, "Invalid color", 1));
	}
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

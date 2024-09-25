/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:05:11 by ybouchma          #+#    #+#             */
/*   Updated: 2024/05/18 15:23:27 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_valide_color(t_ptr *ptr, char *str, int *color)
{
	int	i;

	i = 0;
	i = skip_digit(ptr, str, i, color);
	i = skip_comma(str, i);
	i = skip_digit(ptr, str, i, color);
	i = skip_comma(str, i);
	i = skip_digit(ptr, str, i, color);
	if (str[i])
		return (1);
	return (0);
}

int	*get_color(t_ptr *ptr, char *str)
{
	int		i;
	char	*tmp;
	int		*color;

	color = malloc(sizeof(int) * 3);
	if (!color)
		exit(ft_error(ptr, "malloc error", 1));
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	i += 1;
	while (ft_isspace(str[i]))
		i++;
	if (check_valide_color(ptr, &str[i], color))
		(free(color), free(str), exit(ft_error(ptr, "Invalide color", 1)));
	tmp = ft_strrchr(str, ',');
	tmp[ft_strlen(tmp) - 1] = 0;
	color[2] = ft_atoi(&tmp[1]);
	*tmp = 0;
	tmp = ft_strrchr(str, ',');
	color[1] = ft_atoi(&tmp[1]);
	*tmp = 0;
	color[0] = ft_atoi(&str[i]);
	valid_color(ptr, color);
	return (color);
}

int	ft_just_whitespaces(char *str, int i)
{
	if (!str[i])
		return (1);
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (!str[i])
		return (1);
	return (0);
}

int	ft_init_texture(t_ptr *ptr, char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (!ptr->parse.no && ft_strncmp(&str[i], "NO", 2) == 0)
		ptr->parse.no = get_texture_path(ptr, str);
	else if (!ptr->parse.so && ft_strncmp(&str[i], "SO", 2) == 0)
		ptr->parse.so = get_texture_path(ptr, str);
	else if (!ptr->parse.we && ft_strncmp(&str[i], "WE", 2) == 0)
		ptr->parse.we = get_texture_path(ptr, str);
	else if (!ptr->parse.ea && ft_strncmp(&str[i], "EA", 2) == 0)
		ptr->parse.ea = get_texture_path(ptr, str);
	else if (!ptr->parse.floor && ft_strncmp(&str[i], "F", 1) == 0)
		ptr->parse.floor = get_color(ptr, str);
	else if (!ptr->parse.ceiling && ft_strncmp(&str[i], "C", 1) == 0)
		ptr->parse.ceiling = get_color(ptr, str);
	else if (!ptr->parse.ceiling && ft_strncmp(&str[i], "EN", 2) == 0)
		ptr->obunga.path = get_texture_path(ptr, str);
	else if (ft_just_whitespaces(str, i))
		return (0);
	else if (str[i] && str[i] != '\n')
		(free(str), exit(ft_error(ptr, "Contain invalid character", 1)));
	return (1);
}

char	**allocate_memory_for_map2d(t_ptr *ptr, int y, int x)
{
	int		i;
	char	**map2d;

	i = 0;
	map2d = ft_calloc(sizeof(char *), (y + 1));
	if (!map2d)
		exit(ft_error(ptr, "malloc error", 1));
	while (i < y)
	{
		map2d[i] = ft_calloc(sizeof(char), (x + 1));
		if (!map2d[i])
			exit(ft_error(ptr, "malloc error", 1));
		i++;
	}
	return (map2d);
}

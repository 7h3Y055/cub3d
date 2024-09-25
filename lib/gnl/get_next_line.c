/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:15:45 by ybouchma          #+#    #+#             */
/*   Updated: 2023/11/22 12:15:54 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*next_line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = read_data(fd, buffer);
	if (!buffer)
		return (NULL);
	if (ft_strlen(buffer) == 0)
		return (free(buffer), NULL);
	next_line = get_nline(buffer);
	buffer = clean(buffer);
	free(buffer);
	buffer = NULL;
	return (next_line);
}

char	*clean(char *buffer)
{
	size_t	i;
	size_t	j;
	char	*buf;

	if (ft_strlen(buffer) <= 0 || !ft_strchr(buffer, '\n'))
		return (free(buffer), NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	buf = ft_calloc(sizeof(char), ft_strlen(buffer + i));
	if (!buf || !ft_strlen(buffer + i))
	{
		free(buf);
		return (NULL);
	}
	j = 0;
	while (buffer[++i])
		buf[j++] = buffer[i];
	free(buffer);
	return (buf);
}

char	*get_nline(char *buffer)
{
	size_t	i;
	char	*line;

	i = 0;
	if (ft_strlen(buffer) == 0)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(sizeof(char), i + 2);
	i = 0;
	while (buffer[i])
	{
		line[i] = buffer[i];
		if (buffer[i] == '\n')
			break ;
		i++;
	}
	return (line);
}

char	*read_data(int fd, char *buffer)
{
	char	*data;
	int		r;

	data = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!data)
		return (NULL);
	r = 1;
	while (r > 0)
	{
		if (read_data_helper(&buffer, data))
			break ;
		r = read(fd, data, BUFFER_SIZE);
		if (r == -1)
			return (free(buffer), free(data), NULL);
		if (r <= 0)
			break ;
		buffer = merge(buffer, data);
		if (!buffer)
			return (NULL);
	}
	return (free(data), buffer);
}

char	*merge(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1)
		return (ft_strdup(s2));
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (free(s1), free(s2), NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
		str[i++] = s2[j++];
	str[i] = 0;
	return (free(s1), str);
}

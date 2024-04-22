/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:16:01 by ybouchma          #+#    #+#             */
/*   Updated: 2023/11/22 12:16:04 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_data_helper(char **buffer, char *data)
{
	int	i;

	if (ft_strlen(*buffer) == 0)
	{
		free(*buffer);
		*buffer = NULL;
		return (0);
	}
	if (ft_strchr(*buffer, '\n'))
		return (1);
	i = 0;
	while (i < BUFFER_SIZE + 1)
		data[i++] = 0;
	return (0);
}

char	*ft_strdup(char *src)
{
	int		i;
	char	*dup;

	i = 0;
	dup = (char *)malloc(sizeof(char) * ft_strlen(src) + 1);
	if (dup == NULL)
		return (NULL);
	while (src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

// void	*ft_calloc(size_t n, size_t size)
// {
// 	size_t	i;
// 	void	*ptr;

// 	if (size && SIZE_MAX / size <= n)
// 		return (NULL);
// 	ptr = malloc(size * n);
// 	if (!ptr)
// 		return (NULL);
// 	i = 0;
// 	while (i < (n * size))
// 		((unsigned char *)ptr)[i++] = 0;
// 	return (ptr);
// }

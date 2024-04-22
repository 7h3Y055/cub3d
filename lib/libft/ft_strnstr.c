/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:58:46 by ybouchma          #+#    #+#             */
/*   Updated: 2024/03/31 22:00:48 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;

	i = 0;
	if (!ft_strlen(to_find))
		return ((char *)str);
	if (!len)
		return (NULL);
	while (str && str[i] && i + ft_strlen(to_find) <= len)
	{
		if (ft_strncmp(&str[i], to_find, ft_strlen(to_find)) == 0)
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:12:31 by ybouchma          #+#    #+#             */
/*   Updated: 2024/03/31 20:21:42 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s && s[i])
	{
		if (s && (s[i] == (char)c))
			return ((char *)&s[i]);
		i++;
	}
	if (s && (s[i] == (char)c))
		return ((char *)&s[i]);
	return (NULL);
}

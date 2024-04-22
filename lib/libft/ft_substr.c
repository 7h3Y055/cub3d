/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:59:11 by ybouchma          #+#    #+#             */
/*   Updated: 2023/11/02 17:33:29 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	malloc_len(const char *s, unsigned int start, size_t len);

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	m_len;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	m_len = malloc_len(s, start, len);
	str = malloc(sizeof(char) * m_len);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, m_len);
	return (str);
}

static size_t	malloc_len(const char *s, unsigned int start, size_t len)
{
	size_t	m_len;

	if (len + start > ft_strlen(s))
		m_len = ft_strlen(s) - start;
	else
		m_len = len;
	return (m_len + 1);
}

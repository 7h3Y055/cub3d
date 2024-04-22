/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:59:04 by ybouchma          #+#    #+#             */
/*   Updated: 2024/03/31 22:01:25 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char const *set, char c);
static int	string_len(char const *s1, char const *set);
static void	strtrim_h(char *str, const char *s1, const char *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;

	if (!s1 || !set)
		return (NULL);
	if (string_len(s1, set) < 0)
		return (ft_strdup(""));
	str = (char *)malloc(sizeof(char) * string_len(s1, set) + 2);
	if (!str)
		return (NULL);
	strtrim_h(str, s1, set);
	return (str);
}

static void	strtrim_h(char *str, const char *s1, const char *set)
{
	int	i;
	int	j;
	int	u;

	i = 0;
	j = 0;
	u = 0;
	while (s1 && s1[i] && is_in_set(set, s1[i]))
		i++;
	j = ft_strlen(s1) - 1;
	while (s1 && s1[j] && is_in_set(set, s1[j]))
		j--;
	while (i <= j)
		str[u++] = s1[i++];
	str[u] = 0;
}

static int	string_len(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1 && s1[i] && is_in_set(set, s1[i]))
		i++;
	j = ft_strlen(s1) - 1;
	while (s1 && s1[j] && is_in_set(set, s1[j]))
		j--;
	return (j - i);
}

static int	is_in_set(char const *set, char c)
{
	int	i;

	i = 0;
	while (set && set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

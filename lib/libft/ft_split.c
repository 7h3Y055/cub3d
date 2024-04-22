/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:57:09 by ybouchma          #+#    #+#             */
/*   Updated: 2024/03/31 22:16:17 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	splits_len(char const *s, char c);
static int		ft_split_helper(char **strs, char const *s, char c);
static size_t	world_len(char const *s, char c);
static void		free_alloc(char **strs, int u);

char	**ft_split(char const *s, char c)
{
	int		sp_len;
	char	**strs;
	int		d;

	if (!s || !splits_len(s, c))
	{
		strs = malloc(sizeof(char *));
		if (!strs)
			return (NULL);
		strs[0] = NULL;
		return (strs);
	}
	d = 0;
	sp_len = splits_len(s, c);
	strs = malloc(sizeof(char *) * (sp_len + 1));
	if (!strs)
		return (NULL);
	d = ft_split_helper(strs, s, c);
	if (d)
		return (NULL);
	strs[sp_len] = NULL;
	return (strs);
}

static int	ft_split_helper(char **strs, char const *s, char c)
{
	int	i;
	int	j;
	int	u;

	i = 0;
	u = 0;
	while (s && s[i])
	{
		j = 0;
		while (s && s[i] && s[i] == c)
			i++;
		strs[u] = malloc(sizeof(char) * (world_len(&s[i], c) + 1));
		if (strs && !strs[u])
		{
			free_alloc(strs, u);
			return (1);
		}
		while (s && s[i] && s[i] != c)
			strs[u][j++] = s[i++];
		strs[u][j] = 0;
		while (s && s[i] && s[i] && s[i] == c)
			i++;
		u++;
	}
	return (0);
}

static void	free_alloc(char **strs, int u)
{
	while (u >= 0)
	{
		free(strs[u]);
		u--;
	}
	free(strs);
	strs = NULL;
}

static size_t	world_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != c)
		i++;
	return (i);
}

static size_t	splits_len(char const *s, char c)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (s && s[i])
	{
		while (s && s[i] && s[i] == c)
			i++;
		if (s && !s[i])
			return (0);
		while (s && s[i] && s[i] != c)
			i++;
		while (s && s[i] && s[i] == c)
			i++;
		len++;
	}
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 11:50:15 by ybouchma          #+#    #+#             */
/*   Updated: 2023/11/05 11:51:05 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		num_len(int n);
static void		itoa_z_m(char *str, int *n);
static void		itoa_h(char *str, int n, int *i);
static size_t	division_len(int n);

char	*ft_itoa(int n)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * num_len(n));
	if (!str)
		return (NULL);
	str[0] = 0;
	if (n <= 0)
	{
		itoa_z_m(str, &n);
		if (n == 0 || n == INT_MIN)
			return (str);
		i++;
	}
	itoa_h(str, n, &i);
	return (str);
}

static void	itoa_h(char *str, int n, int *i)
{
	size_t	div;

	div = division_len(n);
	while (div > 0)
	{
		str[*i] = ((n / div) % 10) + '0';
		(*i)++;
		div /= 10;
	}
	str[*i] = 0;
}

static size_t	division_len(int n)
{
	size_t	div;

	div = 1;
	while (n / div > 0)
		div *= 10;
	div /= 10;
	return (div);
}

static void	itoa_z_m(char *str, int *n)
{
	if (*n == 0)
		ft_strlcat(str, "0", 2);
	else if (*n == INT_MIN)
		ft_strlcat(str, "-2147483648", 12);
	else
	{
		ft_strlcat(str, "-", 2);
		*n = -(*n);
	}
}

static int	num_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (2);
	if (n == INT_MIN)
		return (12);
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len + 1);
}

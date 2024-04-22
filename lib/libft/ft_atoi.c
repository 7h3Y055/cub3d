/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:42:51 by ybouchma          #+#    #+#             */
/*   Updated: 2024/03/31 20:16:31 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	ft_atoi_helper(char const *str, int *i, int *is_negative,
				int *sign);

int	ft_atoi(const char *str)
{
	int	i;
	int	integer;
	int	sign;
	int	is_negative;

	i = 0;
	integer = 0;
	sign = 0;
	is_negative = 0;
	ft_atoi_helper(str, &i, &is_negative, &sign);
	if (sign > 1)
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		integer = (integer * 10) + (str[i] - 48);
		i++;
	}
	if (is_negative == 1)
		return (-integer);
	return (integer);
}

static void	ft_atoi_helper(char const *str, int *i, int *is_negative, int *sign)
{
	while ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == ' ')
		*i += 1;
	while (str && (str[*i] == '-' || str[*i] == '+'))
	{
		if (str[*i] == '-')
			*is_negative += 1;
		*sign += 1;
		*i += 1;
	}
}

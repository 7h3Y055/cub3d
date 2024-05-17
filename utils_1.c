/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:33:54 by ybouchma          #+#    #+#             */
/*   Updated: 2024/05/16 16:45:14 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	calculate_incrementation(void)
{
	return (d2rad(1. / ((double)HEIGHT / EYE_ANGLE)));
}

int	btw_range(double a, double min, double max)
{
	if (max > min)
	{
		if (a >= min && a <= max)
			return (1);
	}
	else
	{
		if ((a >= min && a <= RAD) || (a >= 0 && a <= max))
			return (1);
	}
	return (0);
}

double	fix_rad_overflow(double a)
{
	a = a - (int)(a / RAD) *RAD;
	if (a < 0)
		a = RAD + a;
	return (a);
}

int	color_unit_pixel(char map_unit)
{
	if (map_unit == '1')
		return (0x002177);
	else if (map_unit == '0')
		return (0xffffff);
	else if (map_unit == 'D')
		return (RED);
	else if (map_unit == 'O')
		return (BLEU);
	return (0);
}

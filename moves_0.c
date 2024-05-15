/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:31:10 by ybouchma          #+#    #+#             */
/*   Updated: 2024/05/15 12:31:30 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	go_up(t_ptr *ptr)
{
	long long	y;
	long long	x;

	y = sin(ptr->player.angle) * PLAYER_SPEED;
	x = cos(ptr->player.angle) * PLAYER_SPEED;
	check_player_move(ptr, y, x);
}

void	go_right(t_ptr *ptr)
{
	long long	y;
	long long	x;

	y = sin(ptr->player.angle + NINETY_DEGREE) * PLAYER_SPEED;
	x = cos(ptr->player.angle + NINETY_DEGREE) * PLAYER_SPEED;
	check_player_move(ptr, y, x);
}

void	go_down(t_ptr *ptr)
{
	long long	y;
	long long	x;

	y = -sin(ptr->player.angle) * PLAYER_SPEED;
	x = -cos(ptr->player.angle) * PLAYER_SPEED;
	check_player_move(ptr, y, x);
}

void	go_left(t_ptr *ptr)
{
	long long	y;
	long long	x;

	y = -sin(ptr->player.angle + NINETY_DEGREE) * PLAYER_SPEED;
	x = -cos(ptr->player.angle + NINETY_DEGREE) * PLAYER_SPEED;
	check_player_move(ptr, y, x);
}

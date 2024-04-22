/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:51:17 by ybouchma          #+#    #+#             */
/*   Updated: 2023/10/30 17:51:19 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*g_ptr;

	if (size && SIZE_MAX / size <= n)
		return (NULL);
	g_ptr = malloc(size * n);
	if (!g_ptr)
		return (NULL);
	ft_bzero(g_ptr, size * n);
	return (g_ptr);
}

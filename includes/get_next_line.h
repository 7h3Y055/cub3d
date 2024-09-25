/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:37:15 by ybouchma          #+#    #+#             */
/*   Updated: 2023/11/22 12:16:55 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	1
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

char	*get_next_line(int fd);
char	*read_data(int fd, char *buffer);
int		read_data_helper(char **buffer, char *data);
char	*get_nline(char *buffer);
char	*clean(char *buffer);
void	*ft_calloc(size_t n, size_t size);
char	*merge(char *s1, char *s2);
size_t	ft_strlen(const char *str);
char	*ft_strdup(char *src);
// void	*ft_bzero(void *s, size_t n);
char	*ft_strchr(const char *s, int c);
#endif

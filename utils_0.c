#include "cub3d.h"

int	rgb2int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	ft_error(t_ptr *ptr, char *str, int n)
{
	(void)ptr;
	ft_putstr_fd("[cub3d]: ", 2);
	ft_putstr_fd(str, 2);
	return (n);
}

int	destroy_all(t_ptr *ptr)
{
	exit(0);
}

size_t	scaleBetween(size_t unscaledNum, size_t minAllowed, size_t maxAllowed, size_t min, size_t max)
{
	return ((maxAllowed - minAllowed) * (unscaledNum - min) / (max - min)
		+ minAllowed);
}

int	handle_input(t_ptr *ptr)
{
	if (ptr->keys[W])
		go_up(ptr);
	if (ptr->keys[A])
		go_left(ptr);
	if (ptr->keys[S])
		go_down(ptr);
	if (ptr->keys[D])
		go_right(ptr);
	if (ptr->keys[R])
		right_angle(ptr);
	if (ptr->keys[L])
		left_argle(ptr);
	if (ptr->keys[E])
		destroy_all(ptr);
	jump(ptr);
	if (ptr->keys[9] && ptr->updown < 300)
		ptr->updown += 10;
	if (ptr->keys[10] && ptr->updown >= -300)
		ptr->updown -= 10;
	return (0);
}

void	check_player_death(t_ptr *ptr)
{
	size_t	n;

	if (distance(*ptr, ptr->flgas.tmp, 1) < SCALE)
	{
		n = 0;
		while (n < distance(*ptr, ptr->flgas.tmp, 1))
		{
			if (check_wall_obunga(ptr, n))
				return ;
			n++;
		}
		exit(ft_error(ptr, "DEATH!\n", 0));
	}
}

#include "cub3d.h"

void	valid_color(t_ptr *ptr, int *color)
{
	if (color[0] > 255 || color[1] > 255 || color[2] > 255)
	{
		free(color);
		exit(ft_error(ptr, "Error5\n", 1));
	}
}
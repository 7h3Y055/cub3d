#include "cub3d.h"

// void	my_mlx_pixe(t_img_data *img, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

int get_pixel_color(t_ptr *ptr, int face, size_t y, size_t x)
{
    if (x % 100 == 0)
        return (yellow);
    return(BLACK);
    // char	*dst;

	// dst = ptr->texture.no_img.addr + (y * ptr->texture.no_img.line_length + x * (ptr->texture.no_img.bits_per_pixel / 8));

    // return (*(int*)dst);
}

void    create_square(t_ptr *ptr, double ray_l, size_t x, int face)
{
    double  y;
    double  dy;
    ray_l =  (SCALE * HEIGHT) / ray_l;
    if (ray_l > WIDTH)
        ray_l = WIDTH;
    dy =  (WIDTH / 2) - (ray_l / 2);
    y = 0;

    while (y < dy)
    {
        my_mlx_pixel_put(&ptr->img3d, x, y, rgb2int(ptr->parse.ceiling[0], ptr->parse.floor[1], ptr->parse.floor[2]));
        y++;
    }

    while (dy < (WIDTH / 2) + (ray_l / 2))
    {
        my_mlx_pixel_put(&ptr->img3d, x, dy, get_pixel_color(ptr, face, (size_t)dy, x));//HERE
        dy++;
    }

    while (dy < WIDTH)
    {
        my_mlx_pixel_put(&ptr->img3d, x, dy, rgb2int(ptr->parse.floor[0], ptr->parse.ceiling[1], ptr->parse.ceiling[2]));
        dy++;
    }
}

void midle_line(t_ptr *ptr)
{
    t_img_data img = ptr->img3d;
    size_t      x;
    size_t      y;

    y = WIDTH / 2;
    x = 0;
    while (x < HEIGHT)
    {
        my_mlx_pixel_put(&img, x, y, 0xFF0000);
        x++;
    }
}

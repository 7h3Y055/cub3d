#include "cub3d.h"

void    create_square(t_ptr *ptr, double ray_l, size_t x, int color)
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
        my_mlx_pixel_put(&ptr->img3d, x, y, rgb2int(ptr->parse.floor[0], ptr->parse.floor[1], ptr->parse.floor[2]));
        y++;
    }

    while (dy < (WIDTH / 2) + (ray_l / 2))
    {
        my_mlx_pixel_put(&ptr->img3d, x, dy, color);
        dy++;
    }

    while (dy < WIDTH)
    {
        my_mlx_pixel_put(&ptr->img3d, x, dy, rgb2int(ptr->parse.ceiling[0], ptr->parse.ceiling[1], ptr->parse.ceiling[2]));
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
